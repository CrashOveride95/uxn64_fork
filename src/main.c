#include <ultra64.h>

#include "types.h"

// Screen size.
#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH  320

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

u16 framebuffers[2][SCREEN_WIDTH * SCREEN_HEIGHT];
u16 rsp_framebuffer[SCREEN_WIDTH * SCREEN_HEIGHT];
static int current_fb = 0;

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

    // Main loop.
    int i = 0;
    int increment = 4;
    int direction = increment;
    while (true) {
        if (i >= 255 - increment) {
            direction = -increment;
        } else if (i <= 0) {
            direction = +increment;
        }
        i += direction;

        // Graphics command list.
        // TODO: Check out of bounds when adding elements to the list.
        Gfx glist[2048];
        Gfx *glistp = glist;

        // Tell RCP where each segment is.
        gSPSegment(glistp++, 0, 0x0);    // Physical address segment
        gSPSegment(glistp++, 2, OS_K0_TO_PHYSICAL(framebuffers[current_fb]));

        // Clear color framebuffer.
        Gfx clearcfb_dl[] = {
            gsDPSetCycleType(G_CYC_FILL),
            gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, rsp_framebuffer),
            gsDPSetFillColor(GPACK_RGBA5551(64, 64, 255, 1) << 16 | GPACK_RGBA5551(i, i, i, 1)),
            gsDPFillRectangle(0, 0, SCREEN_WIDTH-1, SCREEN_HEIGHT-1),
            gsSPEndDisplayList(),
        };
        gSPDisplayList(glistp++, clearcfb_dl);
        gDPFullSync(glistp++);
        gSPEndDisplayList(glistp++);

        // Start up the RSP task list.
        OSTask tlist = (OSTask){
            {
                .type = M_GFXTASK,
                .flags = OS_TASK_DP_WAIT,
                .ucode_boot = (u64*) rspbootTextStart,
                .ucode_boot_size = (u32)rspbootTextEnd - (u32)rspbootTextStart,
                .ucode = (u64*)gspF3DEX2_xbusTextStart,
                .ucode_size = SP_UCODE_SIZE,
                .ucode_data = (u64*)gspF3DEX2_xbusDataStart,
                .ucode_data_size = SP_UCODE_DATA_SIZE,
                .data_ptr = (u64*) glist,
                .data_size = (u32)((glistp - glist) * sizeof(Gfx)),
                .dram_stack = dram_stack,
                .dram_stack_size = SP_DRAM_STACK_SIZE8,
            },
        };
        osSpTaskStart(&tlist);

        // Wait for RDP completion.
        osRecvMesg(&rdp_msg_queue, NULL, OS_MESG_BLOCK);

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
