#include <ultra64.h>

#include "types.h"

// Screen size.
#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

// Get a pointer to the start (top) of a stack.
#define STACK_START(stack) ((stack) + sizeof((stack)))

//
// Threads and stacks.
//

#define STACK_SIZE 8 * 1024
static OSThread idle_thread;
static OSThread main_thread;
static u8 idle_thread_stack[STACK_SIZE]     __attribute__((aligned(8)));
static u8 main_thread_stack[STACK_SIZE]     __attribute__((aligned(8)));
static u64 dram_stack[SP_DRAM_STACK_SIZE64] __attribute__((aligned(16)));
u64 boot_stack[STACK_SIZE / sizeof(u64)]    __attribute__((aligned(8)));

//
// Framebuffers.
//

u16 framebuffers[2][SCREEN_WIDTH * SCREEN_HEIGHT] __attribute__((aligned(16)));

//
// Statics.
//

static int current_fb = 0;
static u16 pixels[SCREEN_WIDTH * SCREEN_HEIGHT] __attribute__((aligned(16)));
static Gfx glist[2048 * 8];

//
// Message buffers and queues.
//

#define NUM_PI_MSGS 8
static OSMesg pi_msg[NUM_PI_MSGS];
static OSMesg rdp_msg_buf, retrace_msg_buf;
static OSMesgQueue pi_msg_queue;
static OSMesgQueue rdp_msg_queue;
static OSMesgQueue retrace_msg_queue;

// Handle for rom memory.
OSPiHandle *rom_handle;

// DEBUG: animations
static int t = 0;

void
fb_write_test(void) {
    for (size_t j = 0; j < SCREEN_HEIGHT; j++) {
        for (size_t i = 0; i < SCREEN_WIDTH; i++) {
            // u16 shade_x = (float)i / (float)SCREEN_WIDTH * 32;
            // u16 shade_y = (float)j / (float)SCREEN_HEIGHT * 32;
            // u16 color = shade_x << 11 | shade_y << 1;
            u16 shade_x = (float)i / (float)SCREEN_WIDTH * 255;
            u16 shade_y = (float)j / (float)SCREEN_HEIGHT * 255;
            u16 color = GPACK_RGBA5551(shade_x, t, shade_y, 1);
            // u16 color = t;
            framebuffers[current_fb][i + j * SCREEN_WIDTH] = color;
        }
    }
}

void
fb_copy_test(void) {
    for (size_t i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++) {
        framebuffers[current_fb][i] = pixels[i];
    }
}

void
rdp_init(void) {
    Gfx *glistp = glist;

    static const Vp viewport = {{
        .vscale = {SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, G_MAXZ / 2, 0},
        .vtrans = {SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, G_MAXZ / 2, 0},
    }};

    // Initialize the RSP.
    Gfx rspinit_dl[] = {
        gsSPViewport(&viewport),
        gsSPClearGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_CULL_BOTH |
                G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                G_TEXTURE_GEN_LINEAR | G_LOD),
        gsSPTexture(0, 0, 0, 0, G_OFF),
    };

    // Initialize the RDP.
    Gfx rdpinit_dl[] = {
        gsDPSetCycleType(G_CYC_1CYCLE),
        gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT),
        gsDPSetCombineKey(G_CK_NONE),
        gsDPSetAlphaCompare(G_AC_NONE),
        gsDPSetRenderMode(G_RM_NOOP, G_RM_NOOP2),
        gsDPSetColorDither(G_CD_DISABLE),
        gsDPPipeSync(),
    };

    gSPDisplayList(glistp++, rspinit_dl);
    gSPDisplayList(glistp++, rdpinit_dl);
    gDPFullSync(glistp++);
    gSPEndDisplayList(glistp++);

    // Start up the  task list.
    OSTask tlist = (OSTask){
        {
            .type            = M_GFXTASK,
            .flags           = OS_TASK_DP_WAIT,
            .ucode_boot      = (u64*)rspbootTextStart,
            .ucode_boot_size = (u32)rspbootTextEnd - (u32)rspbootTextStart,
            .ucode           = (u64*)gspF3DEX2_xbusTextStart,
            .ucode_size      = SP_UCODE_SIZE,
            .ucode_data      = (u64*)gspF3DEX2_xbusDataStart,
            .ucode_data_size = SP_UCODE_DATA_SIZE,
            .data_ptr        = (u64*)glist,
            .data_size       = (u32)((glistp - glist) * sizeof(Gfx)),
            .dram_stack      = dram_stack,
            .dram_stack_size = SP_DRAM_STACK_SIZE8,
        },
    };
    osSpTaskStart(&tlist);

    // Wait for RDP completion.
    osRecvMesg(&rdp_msg_queue, NULL, OS_MESG_BLOCK);
}

void
rdp_clearfb(u8 r, u8 g, u8 b) {
    Gfx *glistp = glist;
    Gfx clearcfb_dl[] = {
        gsDPSetCycleType(G_CYC_FILL),
        gsDPSetColorImage(
            G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, framebuffers[current_fb]),
        gsDPSetFillColor(
            GPACK_RGBA5551(r, g, b, 1) << 16 | GPACK_RGBA5551(r, g, b, 1)),
        gsDPFillRectangle(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
        gsDPPipeSync(),
    };
    gSPDisplayList(glistp++, clearcfb_dl);
    gDPFullSync(glistp++);
    gSPEndDisplayList(glistp++);

    // Start up the  task list.
    OSTask tlist = (OSTask){
        {
            .type            = M_GFXTASK,
            .flags           = OS_TASK_DP_WAIT,
            .ucode_boot      = (u64*)rspbootTextStart,
            .ucode_boot_size = (u32)rspbootTextEnd - (u32)rspbootTextStart,
            .ucode           = (u64*)gspF3DEX2_xbusTextStart,
            .ucode_size      = SP_UCODE_SIZE,
            .ucode_data      = (u64*)gspF3DEX2_xbusDataStart,
            .ucode_data_size = SP_UCODE_DATA_SIZE,
            .data_ptr        = (u64*)glist,
            .data_size       = (u32)((glistp - glist) * sizeof(Gfx)),
            .dram_stack      = dram_stack,
            .dram_stack_size = SP_DRAM_STACK_SIZE8,
        },
    };
    osSpTaskStart(&tlist);

    // Wait for RDP completion.
    osRecvMesg(&rdp_msg_queue, NULL, OS_MESG_BLOCK);
}

void
rdp_texture_copy(void) {
    Gfx *glistp = glist;
    Gfx dl[] = {
        gsDPSetTexturePersp(G_TP_NONE),
        gsDPSetCycleType(G_CYC_COPY),
        gsDPSetRenderMode(G_RM_NOOP, G_RM_NOOP2),
        gsSPClearGeometryMode(G_SHADE | G_SHADING_SMOOTH),
        gsSPTexture(0x2000, 0x2000, 0, G_TX_RENDERTILE, G_ON),
        gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
        gsDPSetTexturePersp(G_TP_NONE),
        gsDPSetTextureFilter(G_TF_POINT),
    };
    gSPDisplayList(glistp++, dl);
    for (size_t i = 0; i < 240; i++) {
        gDPLoadTextureBlock(
                glistp++,
                &pixels[320 * 1 * i],        // Texture data.
                G_IM_FMT_RGBA,               // Image format.
                G_IM_SIZ_16b,                // Pixel component size.
                320,                         // Width.
                1,                           // Height.
                0,                           // Palette location.
                G_TX_CLAMP,                  // S-axis mirror/wrap/clamp.
                G_TX_CLAMP,                  // T-axis mirror/wrap/clamp.
                0,                           // S-axis mask.
                0,                           // T-axis mask.
                G_TX_NOLOD,                  // S-axis shift.
                G_TX_NOLOD);                 // T-axis shift.
        gSPTextureRectangle(
                glistp++,
                0,                    // ulx
                (1 * i) << 2,         // uly
                (320 * (i + 1)) << 2, // lrx
                (1 *   (i + 1)) << 2, // lry
                0,
                0,
                0,
                4 << 10,
                1 << 10);
    }
    gDPFullSync(glistp++);
    gSPEndDisplayList(glistp++);

    // Start up the  task list.
    OSTask tlist = (OSTask){
        {
            .type            = M_GFXTASK,
            .flags           = OS_TASK_DP_WAIT,
            .ucode_boot      = (u64*)rspbootTextStart,
            .ucode_boot_size = (u32)rspbootTextEnd - (u32)rspbootTextStart,
            .ucode           = (u64*)gspF3DEX2_xbusTextStart,
            .ucode_size      = SP_UCODE_SIZE,
            .ucode_data      = (u64*)gspF3DEX2_xbusDataStart,
            .ucode_data_size = SP_UCODE_DATA_SIZE,
            .data_ptr        = (u64*)glist,
            .data_size       = (u32)((glistp - glist) * sizeof(Gfx)),
            .dram_stack      = dram_stack,
            .dram_stack_size = SP_DRAM_STACK_SIZE8,
        },
    };
    osSpTaskStart(&tlist);

    // Wait for RDP completion.
    osRecvMesg(&rdp_msg_queue, NULL, OS_MESG_BLOCK);
}

static void
main_proc(void *arg) {
    (void)arg;

    // Setup the message queues
    osCreateMesgQueue(&rdp_msg_queue, &rdp_msg_buf, 1);
    osSetEventMesg(OS_EVENT_DP, &rdp_msg_queue, NULL);
    osCreateMesgQueue(&retrace_msg_queue, &retrace_msg_buf, 1);
    osViSetEvent(&retrace_msg_queue, NULL, 1);

    // NOTE: Graphics drawing pipeline:
    // 1. Transfer gfx data from ROM to RDRAM (CPU -- N64 OS)
    // 2. Create display list in RDRAM from img data (CPU -- Game application)
    // 3. Transfer display list and graphics microcode to the RSP (CPU -- N64 OS)
    // 4. Conversion process (RSP -- GFX microcode)
    // 5. Transfer converted data to RDP (RSP -- GFX microcode)
    // 6. Manipulation process (RDP)
    // 7. Transfer manipulated data to framebuffer (RDP)
    // 8. Transfer manipulated data to the video interface (CPU -- N64 OS)
    // 9. Trasfer digital data to DAC (Video Interface)
    // 10. Video signal is produced.

    // NOTE: Test image.
    for (size_t j = 0; j < SCREEN_HEIGHT; j++) {
        for (size_t i = 0; i < SCREEN_WIDTH; i++) {
            u16 shade_x = (float)i / (float)SCREEN_WIDTH * 255;
            u16 shade_y = (float)j / (float)SCREEN_HEIGHT * 255;
            u16 color = GPACK_RGBA5551(shade_x, 0, shade_y, 1);
            pixels[i + j * SCREEN_WIDTH] = color;
        }
    }

    // Clear the framebuffer with rdp.
    rdp_init();

    // Main loop.
    int increment = 4;
    int direction = increment;
    while (true) {
        if (t >= 255 - increment) {
            direction = -increment;
        } if (t <= 0 + increment) {
            direction = +increment;
        }
        t += direction;

        // A
        // rdp_clearfb(t, t, t);
        // osWritebackDCacheAll();
        // B
        // fb_write_test();
        // osWritebackDCacheAll();
        // C
        for (size_t j = 0; j < SCREEN_HEIGHT; j++) {
            for (size_t i = 0; i < SCREEN_WIDTH; i++) {
                u16 shade_x = (float)i / (float)SCREEN_WIDTH * 255;
                u16 shade_y = (float)j / (float)SCREEN_HEIGHT * 255;
                u16 color = GPACK_RGBA5551(shade_x, t, shade_y, 1);
                pixels[i + j * SCREEN_WIDTH] = color;
            }
        }
        // osWritebackDCacheAll();
        // fb_copy_test();
        // D
        rdp_texture_copy();
        // osWritebackDCacheAll();
        // osWritebackDCacheAll();

        // Swap buffers.
        osViSwapBuffer(framebuffers[current_fb]);

        // Make sure there isn't an old retrace in queue
        // (assumes queue has a depth of 1).
        if (MQ_IS_FULL(&retrace_msg_queue)) {
            osRecvMesg(&retrace_msg_queue, NULL, OS_MESG_BLOCK);
        }

        // Wait for Vertical retrace to finish swap buffers.
        osRecvMesg(&retrace_msg_queue, NULL, OS_MESG_BLOCK);
        current_fb ^= 1;
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
    osCreateThread(&main_thread, 3, main_proc, NULL, STACK_START(main_thread_stack), 10);
    osStartThread(&main_thread);

    // Become the idle thread.
    osSetThreadPri(0, 0);
    for (;;);
}


void
boot(void) {
    osInitialize();
    rom_handle = osCartRomInit();
    osCreateThread(&idle_thread, 1, idle_proc, NULL, STACK_START(idle_thread_stack), 10);
    osStartThread(&idle_thread);
}
