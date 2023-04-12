#include <ultra64.h>

#include "types.h"

//
// Threads and stacks.
//

static OSThread idle_thread;
static OSThread main_thread;
static OSThread audio_thread;
extern u8 _idle_thread_stack[];
extern u8 _main_thread_stack[];
extern u8 _audio_thread_stack[];

//
// Message buffers, queues and devices.
//

#define NUM_PI_MSGS 8
static OSMesg pi_msg[NUM_PI_MSGS];
static OSMesgQueue pi_msg_queue;

#define NUM_CONTROLLERS 4
static OSMesg ctrl_msg[1];
static OSMesgQueue ctrl_msg_queue;
static OSContStatus ctrl_status[NUM_CONTROLLERS];
static OSContPad ctrl_pad[NUM_CONTROLLERS];
static u8 ctrl_bitpattern;

// Handle for rom memory.
OSPiHandle *rom_handle;

//
// UXN.
//

#include "uxn/src/uxn.c"
#include "uxn/src/devices/audio.c"
#include "ppu.c"

#include "rom.c"

#define N_AUDIO_BUF 4
#define AUDIO_RATE 44100
#define AUDIO_BUF_SIZE (KB(2) * 2)
static s16 audio_buffers[N_AUDIO_BUF][AUDIO_BUF_SIZE] __attribute__((aligned(64)));
static s32 active_audio = 0;
static s32 pause_audio = 0;
static OSMesg audio_msg_buf;
static OSMesgQueue audio_msg_queue;

#define CLAMP(X, MIN, MAX) ((X) <= (MIN) ? (MIN) : (X) > (MAX) ? (MAX): (X))

static u8 uxn_ram[0x80000];
static Uxn u;
u16 deo_mask[] = {0xff08, 0x0300, 0xc028, 0x8000, 0x8000, 0x8000, 0x8000, 0x0000, 0x0000, 0x0000, 0xa260, 0xa260, 0x0000, 0x0000, 0x0000, 0x0000};
u16 dei_mask[] = {0x0000, 0x0000, 0x003c, 0x0014, 0x0014, 0x0014, 0x0014, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x07ff, 0x0000, 0x0000, 0x0000};

#define MOUSE_DELTA 1
typedef struct Mouse {
    s32 x;
    s32 y;
    u8 buttons;
    // TODO: mouse timeout?
} Mouse;

static Mouse mouse = {0};
static size_t seconds = 0;

int
uxn_halt(Uxn *u, u8 instr, u8 err, u16 addr) {
    (void)u;
    (void)instr;
    (void)err;
    (void)addr;
    for (;;) {}
}

int
uxn_interrupt(void) {
    return 1;
}

u8
datetime_dei(Uxn *u, u8 addr) {
    (void)u;
    (void)addr;
    // size_t minutes = seconds / 60;
    // size_t hours = minutes / 60;
    // POKE2(d + 0x0, 0);
    // d[0x2] = 0;
    // d[0x3] = 0;
    // d[0x4] = hours;
    // d[0x5] = minutes;
    // d[0x6] = seconds % 60;
    // d[0x7] = 0;
    // // POKE2(d + 0x08, 0);
    // d[0xa] = 0;
	// switch(addr) {
	// case 0xc0: return 0;
	// case 0xc1: return 0;
	// case 0xc2: return 0;
	// case 0xc3: return 0;
	// case 0xc4: return hours;
	// case 0xc5: return minutes;
	// case 0xc6: return seconds % 60;
	// case 0xc7: return 0;
	// case 0xc8: return 0;
	// case 0xc9: return 0;
	// case 0xca: return 0;
	// default: return u->dev[addr];
	// }
	// return 0;
}

static void
screen_palette(u8 *d) {
    for(size_t i = 0; i < 4; ++i) {
        u8 r = ((*(d +     i / 2) >> (!(i % 2) << 2)) & 0x0f) * 0x11;
        u8 g = ((*(d + 2 + i / 2) >> (!(i % 2) << 2)) & 0x0f) * 0x11;
        u8 b = ((*(d + 4 + i / 2) >> (!(i % 2) << 2)) & 0x0f) * 0x11;

        palette[i] = GPACK_RGBA5551(r, g, b, 1);
    }
    for(size_t i = 4; i < 16; ++i) {
        palette[i] = palette[i / 4];
    }

    // Redraw the screen if we change the color palette.
    reqdraw = 1;
    redraw_screen();
}

#define RAM_PAGES 0x10

static void
system_cmd(Uint8 *ram, Uint16 addr) {
    if(ram[addr] == 0x01) {
        Uint16 i, length = PEEK2(ram + addr + 1);
        Uint16 a_page = PEEK2(ram + addr + 1 + 2), a_addr = PEEK2(ram + addr + 1 + 4);
        Uint16 b_page = PEEK2(ram + addr + 1 + 6), b_addr = PEEK2(ram + addr + 1 + 8);
        int src = (a_page % RAM_PAGES) * 0x10000, dst = (b_page % RAM_PAGES) * 0x10000;
        for(i = 0; i < length; i++)
            ram[dst + (Uint16)(b_addr + i)] = ram[src + (Uint16)(a_addr + i)];
    }
}

void
system_deo(Uxn *u, u8 *d, u8 port) {
    switch(port) {
        case 0x3:
            system_cmd(u->ram, PEEK2(d + 2));
            break;
            // case 0xe:
            // 	system_inspect(u);
            // 	break;
    }
}

static void
console_deo(u8 *d, u8 port) {
    (void)d;
    (void)port;
}

u8
screen_dei(u8 *d, u8 port) {
    switch(port) {
        case 0x2: return screen_width >> 8;
        case 0x3: return screen_width;
        case 0x4: return screen_height >> 8;
        case 0x5: return screen_height;
        default: return d[port];
    }
}

void
screen_deo(u8 *ram, u8 *d, u8 port) {
    switch(port) {
        case 0xe: {
            u16 x, y;
            u8 layer = d[0xe] & 0x40;
            x = PEEK2(d + 0x8);
            y = PEEK2(d + 0xa);
            ppu_pixel(layer ? pixels_fg : pixels_bg, x, y, d[0xe] & 0x3);
            if(d[0x6] & 0x01) POKE2(d + 0x8, x + 1); /* auto x+1 */
            if(d[0x6] & 0x02) POKE2(d + 0xa, y + 1); /* auto y+1 */
            break;
        }
        case 0xf: {
            u16 x, y, dx, dy, addr;
            u8 n, twobpp = !!(d[0xf] & 0x80);
            x    = PEEK2(d + 0x8);
            y    = PEEK2(d + 0xa);
            addr = PEEK2(d + 0xc);
            n = d[0x6] >> 4;
            dx = (d[0x6] & 0x01) << 3;
            dy = (d[0x6] & 0x02) << 2;
            if(addr > 0x10000 - ((n + 1) << (3 + twobpp))) {
                return;
            }
            u8 *layer = (d[0xf] & 0x40) ? pixels_fg : pixels_bg;
            u8 color = d[0xf] & 0xf;
            u8 flipx = d[0xf] & 0x10;
            u8 flipy = d[0xf] & 0x20;
            for(size_t i = 0; i <= n; i++) {
                u8 *sprite = &ram[addr];
                if (twobpp) {
                    ppu_2bpp(layer, x + dy * i, y + dx * i, sprite, color, flipx, flipy);
                } else {
                    ppu_1bpp(layer, x + dy * i, y + dx * i, sprite, color, flipx, flipy);
                }
                addr += (d[0x6] & 0x04) << (1 + twobpp);
            }
            POKE2(d + 0xc, addr);   /* auto addr+length */
            POKE2(d + 0x8, x + dx); /* auto x+8 */
            POKE2(d + 0xa, y + dy); /* auto y+8 */
            break;
        }
    }
    reqdraw = 1;
}

static u8
audio_dei(int instance, u8 *d, u8 port) {
    switch(port) {
        case 0x4: return audio_get_vu(instance);
        case 0x2: POKE2(d + 0x2, audio_get_position(instance)); /* fall through */
        default: return d[port];
    }
}

static void
audio_deo(int instance, u8 *d, u8 port, Uxn *u) {
    if(port == 0xf) {
        // TODO: stop the audio before audio_start
        audio_start(instance, d, u);
        pause_audio = 0;
    }
}

void
init_ctrl(void) {
    osCreateMesgQueue(&ctrl_msg_queue, ctrl_msg, 1);
    osSetEventMesg(OS_EVENT_SI, &ctrl_msg_queue, NULL);
    osContInit(&ctrl_msg_queue, &ctrl_bitpattern, &ctrl_status[0]);
}

void
handle_input(int i) {
    // RESET?
    // devctrl->dat[2] = 0;
    // uxn_eval(&u, GETVECTOR(devctrl));
    // devctrl->dat[3] = 0;
    // NOTE:
    // - Analog can act as a mouse and/or dissapear if it was not moved in
    // X seconds. L/R buttons act as the mouse buttons.
    // - DPAD + A/B are the regular controller. (Start/select?)
    // - MAYBE: The C buttons can control the keyboard somehow? A virtual
    // keyboard that is? With Z to confirm keypresses?
    // - Start can just pause the application if no other use is in place.
    OSContPad prev_pad = ctrl_pad[i];
    osContGetReadData(&ctrl_pad[i]);
    OSContPad current_pad = ctrl_pad[i];
    if (current_pad.errno != 0) {
        return;
    }
    bool update_ctrl = false;
    bool update_mouse = false;

    // Check for controller changes.
        u8 *devctrl = &u.dev[0x80];
    if (prev_pad.button != current_pad.button) {
        u8 *uxn_ctrl = &devctrl[2];
        if (current_pad.button & U_JPAD || current_pad.button & U_CBUTTONS) {
            *uxn_ctrl |= 0x10;
            update_ctrl = true;
        } else {
            *uxn_ctrl &= ~0x10;
            update_ctrl = true;
        }
        if (current_pad.button & D_JPAD || current_pad.button & D_CBUTTONS) {
            *uxn_ctrl |= 0x20;
            update_ctrl = true;
        } else {
            *uxn_ctrl &= ~0x20;
            update_ctrl = true;
        }
        if (current_pad.button & L_JPAD || current_pad.button & L_CBUTTONS) {
            *uxn_ctrl |= 0x40;
            update_ctrl = true;
        } else {
            *uxn_ctrl &= ~0x40;
            update_ctrl = true;
        }
        if (current_pad.button & R_JPAD || current_pad.button & R_CBUTTONS) {
            *uxn_ctrl |= 0x80;
            update_ctrl = true;
        } else {
            *uxn_ctrl &= ~0x80;
            update_ctrl = true;
        }
        if (current_pad.button & A_BUTTON) {
            *uxn_ctrl |= 0x01;
            update_ctrl = true;
        } else {
            *uxn_ctrl &= ~0x01;
            update_ctrl = true;
        }
        if (current_pad.button & B_BUTTON) {
            *uxn_ctrl |= 0x02;
            update_ctrl = true;
        } else {
            *uxn_ctrl &= ~0x02;
            update_ctrl = true;
        }
        if (current_pad.button & START_BUTTON) {
            *uxn_ctrl |= 0x08;
            update_ctrl = true;
        } else {
            *uxn_ctrl &= ~0x08;
            update_ctrl = true;
        }
        if (current_pad.button & Z_TRIG) {
            *uxn_ctrl |= 0x04;
            update_ctrl = true;
        } else {
            *uxn_ctrl &= ~0x04;
            update_ctrl = true;
        }

        // Check for mouse button changes (L/R on the pad).
        if (current_pad.button & L_TRIG) {
            mouse.buttons |= 0x01;
            update_mouse = true;
        } else {
            mouse.buttons &= ~0x01;
            update_mouse = true;
        }
        if (current_pad.button & R_TRIG) {
            mouse.buttons |= 0x10;
            update_mouse = true;
        } else {
            mouse.buttons &= ~0x10;
            update_mouse = true;
        }
    }

    // Check for "mouse" x/y changes.
    u8 *devmouse = &u.dev[0x90];
    if (current_pad.stick_x != 0 || current_pad.stick_y != 0) {
        mouse.x = CLAMP(mouse.x + prev_pad.stick_x / 8, 0, (s32)screen_width);
        mouse.y = CLAMP(mouse.y - prev_pad.stick_y / 8, 0, (s32)screen_height);
        POKE2(devmouse + 0x2, mouse.x);
        POKE2(devmouse + 0x4, mouse.y);
        update_mouse = true;
    }

    if (update_ctrl) {
        uxn_eval(&u, PEEK2(devctrl));
        devctrl[3] = 0;
    }
    if (update_mouse) {
        devmouse[6] = mouse.buttons;
        if(mouse.buttons == 0x10 && (devmouse[6] & 0x01)) {
            devmouse[7] = 0x01;
        }
        if(mouse.buttons == 0x01 && (devmouse[6] & 0x10)) {
            devmouse[7] = 0x10;
        }
        uxn_eval(&u, PEEK2(devmouse));
    }
}

void
poll_input() {
    // Get current ctrl status.
    osContStartQuery(&ctrl_msg_queue);
    osRecvMesg(&ctrl_msg_queue, NULL, OS_MESG_BLOCK);

    // Reads the data from the first active controller.
    for(int i = 0; i < NUM_CONTROLLERS; i++){
        osContGetQuery(&ctrl_status[i]);
        if(((ctrl_bitpattern >> i) & 1) && (ctrl_status[i].errno == 0)){
            if((ctrl_status[i].type & CONT_TYPE_MASK) == CONT_TYPE_NORMAL){
                osContStartReadData(&ctrl_msg_queue);
                osRecvMesg(&ctrl_msg_queue, NULL, OS_MESG_BLOCK);
                handle_input(i);
                break;
            }
        }
    }
}

u8
uxn_dei(Uxn *u, u8 addr) {
    u8 p = addr & 0x0f, d = addr & 0xf0;
    switch(d) {
        case 0x20: return screen_dei(&u->dev[d], p);
        case 0x30: return audio_dei(0, &u->dev[d], p);
        case 0x40: return audio_dei(1, &u->dev[d], p);
        case 0x50: return audio_dei(2, &u->dev[d], p);
        case 0x60: return audio_dei(3, &u->dev[d], p);
        case 0xc0: return datetime_dei(u, p);
    }
    return u->dev[addr];
}

void
uxn_deo(Uxn *u, u8 addr) {
	u8 p = addr & 0x0f, d = addr & 0xf0;
	switch(d) {
	case 0x00:
		system_deo(u, &u->dev[d], p);
        if(p > 0x7 && p < 0xe)
            screen_palette(&u->dev[0x8]);
		break;
	case 0x10: console_deo(&u->dev[d], p); break;
	case 0x20: screen_deo(u->ram, &u->dev[d], p); break;
	case 0x30: audio_deo(0, &u->dev[d], p, u); break;
	case 0x40: audio_deo(1, &u->dev[d], p, u); break;
	case 0x50: audio_deo(2, &u->dev[d], p, u); break;
	case 0x60: audio_deo(3, &u->dev[d], p, u); break;
	// case 0xa0: file_deo_2(0, u->ram, &u->dev[d], p); break;
	// case 0xb0: file_deo_2(1, u->ram, &u->dev[d], p); break;
	}
}

void
init_uxn(Uxn *u) {
    // Setup UXN memory.
    for (size_t i = 0; i < sizeof(uxn_ram); i++) {
        uxn_ram[i] = 0;
    }
    uxn_boot(u, uxn_ram);

    // Copy rom to VM.
    u8 *dst = u->ram + PAGE_PROGRAM;
    u8 *src = (u8*)uxn_rom;
    for (size_t i = 0; i < sizeof(uxn_rom); i++) {
        dst[i] = src[i];
    }

    // Prepare devices.
    uxn_eval(u, PAGE_PROGRAM);
}

void
init_audio(void) {
    osAiSetFrequency(AUDIO_RATE);
    osWritebackDCache(audio_buffers, sizeof(audio_buffers));
}

void
sound_mix(void) {
    s16 *samples = (s16*)&audio_buffers[active_audio];
    for (size_t i = 0; i < AUDIO_BUF_SIZE; i++) {
        samples[i] = 0;
    }
    if (!pause_audio) {
        int running = 0;
        for(int channel = 0; channel < POLYPHONY; channel++) {
            running += audio_render(channel, samples, samples + AUDIO_BUF_SIZE / 2);
        }
        if(!running) {
            pause_audio = 1;
        }
    }
}

static void
main_proc(void *arg) {
    (void)arg;
    init_ppu();
    init_ctrl();
    init_uxn(&u);

    // Main loop.
    u8 frame_counter = 0;
    while (true) {
        poll_input();
        uxn_eval(&u, PEEK2(&u.dev[0x20]));
        blit_framebuffer();
        swap_buffers();
        osYieldThread();
        if (frame_counter == 60) {
            seconds++;
            frame_counter = 0;
        }
    }
}

static void
audio_proc(void *arg) {
    (void)arg;
    osCreateMesgQueue(&audio_msg_queue, &audio_msg_buf, 1);
    osSetEventMesg(OS_EVENT_AI, &audio_msg_queue, &audio_msg_buf);
    init_audio();
    while (true) {
        sound_mix();
        osAiSetNextBuffer(audio_buffers[active_audio], AUDIO_BUF_SIZE);
        active_audio++;
        if (active_audio == N_AUDIO_BUF) {
            active_audio = 0;
        }
        u32 status = osAiGetStatus();
        if ((status & AI_STATUS_FIFO_FULL) > 0) {
            osRecvMesg(&audio_msg_queue, NULL, OS_MESG_BLOCK);
        } else {
            osYieldThread();
        }
    }
}

void
audio_finished_handler(int instance) {
    (void)instance;
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
    osCreateThread(&main_thread, 2, main_proc, NULL, _main_thread_stack, 10);
    osStartThread(&main_thread);

    // Create audio thread.
    osCreateThread(&audio_thread, 3, audio_proc, NULL, _audio_thread_stack, 10);
    osStartThread(&audio_thread);

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
