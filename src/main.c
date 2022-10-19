#include <ultra64.h>

#include "types.h"

//
// Threads and stacks.
//

static OSThread idle_thread;
static OSThread main_thread;
extern u8 _idle_thread_stack[];
extern u8 _main_thread_stack[];

//
// Message buffers and queues.
//

#define NUM_PI_MSGS 8
static OSMesg pi_msg[NUM_PI_MSGS];
static OSMesgQueue pi_msg_queue;

// Handle for rom memory.
OSPiHandle *rom_handle;

//
// UXN.
//

#include "ppu.c"
#include "uxn/src/uxn.c"

#include "uxn_controller_rom.c"

#define CLAMP(X, MIN, MAX) ((X) <= (MIN) ? (MIN) : (X) > (MAX) ? (MAX): (X))

static Uxn u;
static Device *devscreen;
static Device *devctrl;
static Device *devmouse;

int
uxn_halt(Uxn *u, Uint8 error, Uint16 addr) {
    (void)u;
    (void)error;
    (void)addr;
    for (;;) {}
}

int
uxn_interrupt(void) {
    return 1;
}

static u8
nil_dei(Device *d, u8 port) {
    return d->dat[port];
}

static void
nil_deo(Device *d, u8 port) {
    (void)d;
    (void)port;
}

static void
screen_palette(Device *d) {
    for(size_t i = 0; i < 4; ++i) {
        u8 r = ((d->dat[0x8 + i / 2] >> (!(i % 2) << 2)) & 0x0f) * 0x11;
        u8 g = ((d->dat[0xa + i / 2] >> (!(i % 2) << 2)) & 0x0f) * 0x11;
        u8 b = ((d->dat[0xc + i / 2] >> (!(i % 2) << 2)) & 0x0f) * 0x11;

        palette[i] = GPACK_RGBA5551(r, g, b, 1);
    }
    for(size_t i = 4; i < 16; ++i) {
        palette[i] = palette[i / 4];
    }

    // Redraw the screen if we change the color palette.
    reqdraw = 1;
    redraw_screen();
}

u8
system_dei(Device *d, u8 port) {
	switch(port) {
	case 0x2: return d->u->wst.ptr;
	case 0x3: return d->u->rst.ptr;
	default: return d->dat[port];
	}
}

void
system_deo(Device *d, u8 port) {
	switch(port) {
        case 0x2: d->u->wst.ptr = d->dat[port]; break;
        case 0x3: d->u->rst.ptr = d->dat[port]; break;
        case 0xe: break;
        default: {
            if(port > 0x7 && port < 0xe) {
                screen_palette(d);
            }
        } break;
	}
}

static void
console_deo(Device *d, u8 port) {
    (void)d;
    (void)port;
}

u8
screen_dei(Device *d, u8 port) {
    switch(port) {
        case 0x2: return screen_width >> 8;
        case 0x3: return screen_width;
        case 0x4: return screen_height >> 8;
        case 0x5: return screen_height;
        default: return d->dat[port];
    }
}

void
screen_deo(Device *d, u8 port) {
    switch(port) {
        // case 0x3:
        //     if(!FIXED_SIZE) {
        //         Uint16 w;
        //         DEVPEEK16(w, 0x2);
        //         screen_resize(&uxn_screen, clamp(w, 1, 1024), uxn_screen.height);
        //     }
        //     break;
        // case 0x5:
        //     if(!FIXED_SIZE) {
        //         Uint16 h;
        //         DEVPEEK16(h, 0x4);
        //         screen_resize(&uxn_screen, uxn_screen.width, clamp(h, 1, 1024));
        //     }
        //     break;
        case 0xe: {
            u16 x, y;
            u8 layer = d->dat[0xe] & 0x40;
            DEVPEEK16(x, 0x8);
            DEVPEEK16(y, 0xa);
            ppu_pixel(layer ? pixels_fg : pixels_bg, x, y, d->dat[0xe] & 0x3);
            if(d->dat[0x6] & 0x01) DEVPOKE16(0x8, x + 1); /* auto x+1 */
            if(d->dat[0x6] & 0x02) DEVPOKE16(0xa, y + 1); /* auto y+1 */
        } break;
        case 0xf: {
            u16 x, y, dx, dy, addr;
            u8 twobpp = !!(d->dat[0xf] & 0x80);
            DEVPEEK16(x, 0x8);
            DEVPEEK16(y, 0xa);
            DEVPEEK16(addr, 0xc);
            u8 n = d->dat[0x6] >> 4;
            dx = (d->dat[0x6] & 0x01) << 3;
            dy = (d->dat[0x6] & 0x02) << 2;
            if(addr > 0x10000 - ((n + 1) << (3 + twobpp))) {
                return;
            }
            u8 *layer = (d->dat[0xf] & 0x40) ? pixels_fg : pixels_bg;
            u8 color = d->dat[0xf] & 0xf;
            u8 flipx = d->dat[0xf] & 0x10;
            u8 flipy = d->dat[0xf] & 0x20;
            for(size_t i = 0; i <= n; i++) {
                u8 *sprite = &d->u->ram[addr];
                if (twobpp) {
                    ppu_2bpp(layer, x + dy * i, y + dx * i, sprite, color, flipx, flipy);
                } else {
                    ppu_1bpp(layer, x + dy * i, y + dx * i, sprite, color, flipx, flipy);
                }
                addr += (d->dat[0x6] & 0x04) << (1 + twobpp);
            }
            DEVPOKE16(0xc, addr);   /* auto addr+length */
            DEVPOKE16(0x8, x + dx); /* auto x+8 */
            DEVPOKE16(0xa, y + dy); /* auto y+8 */
        } break;
	}
    reqdraw = 1;
}

void
poll_input() {
    // NOTE:
    // - Analog can act as a mouse and/or dissapear if it was not moved in
    // X seconds. L/R buttons act as the mouse buttons.
    // - DPAD + A/B are the regular controller. (Start/select?)
    // - MAYBE: The C buttons can control the keyboard somehow? A virtual
    // keyboard that is? With Z to confirm keypresses?
    // - Start can just pause the application if no other use is in place.
    // STUB...
}

void
handle_input() {
    // STUB...
}

static u8 uxn_ram[0x10000];

void
init_uxn(Uxn *u) {
    // Setup UXN memory.
	for (size_t i = 0; i < sizeof(uxn_ram); i++) {
	    uxn_ram[i] = 0;
	}
	uxn_boot(u, uxn_ram);

    // Copy rom to VM.
    // memcpy(u->ram + PAGE_PROGRAM, uxn_rom, sizeof(uxn_rom));
    u8 *dst = u->ram + PAGE_PROGRAM;
    u8 *src = (u8*)uxn_rom;
    for (size_t i = 0; i < sizeof(uxn_rom); i++) {
        dst[i] = src[i];
    }

    // Prepare devices.
    /* system   */ uxn_port(u, 0x0, system_dei, system_deo);
    /* console  */ uxn_port(u, 0x1, nil_dei, console_deo);
    /* screen   */ devscreen = uxn_port(u, 0x2, screen_dei, screen_deo);
    /* audio0   */ uxn_port(u, 0x3, nil_dei, nil_deo);
    /* audio1   */ uxn_port(u, 0x4, nil_dei, nil_deo);
    /* audio2   */ uxn_port(u, 0x5, nil_dei, nil_deo);
    /* audio3   */ uxn_port(u, 0x6, nil_dei, nil_deo);
    /* unused   */ uxn_port(u, 0x7, nil_dei, nil_deo);
    /* control  */ devctrl = uxn_port(u, 0x8, nil_dei, nil_deo);
    /* mouse    */ devmouse = uxn_port(u, 0x9, nil_dei, nil_deo);
    /* file0    */ uxn_port(u, 0xa, nil_dei, nil_deo);
    /* file1    */ uxn_port(u, 0xb, nil_dei, nil_deo);
    /* datetime */ uxn_port(u, 0xc, nil_dei, nil_deo);
    /* unused   */ uxn_port(u, 0xd, nil_dei, nil_deo);
    /* unused   */ uxn_port(u, 0xe, nil_dei, nil_deo);
    /* unused   */ uxn_port(u, 0xf, nil_dei, nil_deo);
    uxn_eval(u, PAGE_PROGRAM);
}

static void
main_proc(void *arg) {
    (void)arg;

    init_ppu();

    init_uxn(&u);

    // Main loop.
    while (true) {
        poll_input();
        handle_input();
        uxn_eval(&u, GETVECTOR(devscreen));
        blit_framebuffer();
        swap_buffers();
    }
}

static void
idle_proc(void *arg) {
    (void)arg;
    // Initialize video.
    osCreateViManager(OS_PRIORITY_VIMGR);
    osViSetMode(&osViModeTable[OS_VI_NTSC_LAN1]);

    // Start PI Mgr for access to cartridge.
    osCreatePiManager((OSPri)OS_PRIORITY_PIMGR, &pi_msg_queue, pi_msg, NUM_PI_MSGS);

    // Create main thread.
    osCreateThread(&main_thread, 3, main_proc, NULL, _main_thread_stack, 10);
    osStartThread(&main_thread);

    // Become the idle thread.
    osSetThreadPri(0, 0);
    for (;;);
}


void
boot(void) {
    osInitialize();
    rom_handle = osCartRomInit();
    osCreateThread(&idle_thread, 1, idle_proc, NULL, _idle_thread_stack, 10);
    osStartThread(&idle_thread);
}
