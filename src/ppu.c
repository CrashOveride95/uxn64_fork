// Screen size.
#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

static OSMesg rdp_msg_buf, retrace_msg_buf;
static OSMesgQueue pi_msg_queue;
static OSMesgQueue rdp_msg_queue;
static OSMesgQueue retrace_msg_queue;

//
// Framebuffers.
//

u16 framebuffers[2][SCREEN_WIDTH * SCREEN_HEIGHT] __attribute__((aligned(16)));

//
// Statics.
//

static u64 dram_stack[SP_DRAM_STACK_SIZE64] __attribute__((aligned(16)));
static u16 pixels[SCREEN_WIDTH * SCREEN_HEIGHT] __attribute__((aligned(16)));
static int current_fb = 0;
static Gfx glist[2048 * 8];

static size_t screen_width = SCREEN_WIDTH;
static size_t screen_height = SCREEN_HEIGHT;
static u16 palette[16];

static u8 pixels_fg[SCREEN_WIDTH * SCREEN_HEIGHT] __attribute__((aligned(16)));
static u8 pixels_bg[SCREEN_WIDTH * SCREEN_HEIGHT] __attribute__((aligned(16)));
static u8 dirty_lines[SCREEN_HEIGHT];
static u8 reqdraw = 0;

static u8 blending[5][16] = {
    {0, 0, 0, 0, 1, 0, 1, 1, 2, 2, 0, 2, 3, 3, 3, 0},
    {0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3},
    {1, 2, 3, 1, 1, 2, 3, 1, 1, 2, 3, 1, 1, 2, 3, 1},
    {2, 3, 1, 2, 2, 3, 1, 2, 2, 3, 1, 2, 2, 3, 1, 2},
    {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0}};

u16
rgb565(u32 rgba) {
    u16 r = (rgba >> 16  & 0xFF);
    u16 g = (rgba >> 8   & 0xFF);
    u16 b = (rgba >> 0   & 0xFF);
    r = r >> 3;
    g = g >> 2;
    b = b >> 3;
    return (r << 11) | (g << 5) | b;
}

void
redraw_screen(void) {
    for (size_t j = 0; j < screen_height; j++) {
        dirty_lines[j] = 1;
    }
}

void
ppu_pixel(u8 *layer, u16 x, u16 y, u8 color) {
    if (x >= screen_width || y >= screen_height) {
        return;
    }
    u32 i = x + y *screen_width;
    if(color != layer[i]) {
        layer[i] = color;
    }
    dirty_lines[y] |= 1;
}

void
ppu_1bpp(u8 *layer, u16 x, u16 y, u8 *sprite, u8 color, u8 flipx, u8 flipy) {
    u16 v, h;
    for(v = 0; v < 8; v++)
        for(h = 0; h < 8; h++) {
            u8 ch1 = (sprite[v] >> (7 - h)) & 0x1;
            if(ch1 || blending[4][color])
                ppu_pixel(layer,
                        x + (flipx ? 7 - h : h),
                        y + (flipy ? 7 - v : v),
                        blending[ch1][color]);
        }
}

void
ppu_2bpp(u8 *layer, u16 x, u16 y, u8 *sprite, u8 color, u8 flipx, u8 flipy) {
    u16 v, h;
    for(v = 0; v < 8; v++)
        for(h = 0; h < 8; h++) {
            u8 ch1 = ((sprite[v] >> (7 - h)) & 0x1);
            u8 ch2 = ((sprite[v + 8] >> (7 - h)) & 0x1);
            u8 ch = ch1 + ch2 * 2;
            if(ch || blending[4][color])
                ppu_pixel(layer,
                        x + (flipx ? 7 - h : h),
                        y + (flipy ? 7 - v : v),
                        blending[ch][color]);
        }
}

void
fb_write_test(void) {
    for (size_t j = 0; j < SCREEN_HEIGHT; j++) {
        for (size_t i = 0; i < SCREEN_WIDTH; i++) {
            u16 shade_x = (float)i / (float)SCREEN_WIDTH * 255;
            u16 shade_y = (float)j / (float)SCREEN_HEIGHT * 255;
            u16 color = GPACK_RGBA5551(shade_x, 0, shade_y, 1);
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
	// gSPSegment(glistp++, 0, 0x0);	/* Physical address segment */
	// gSPSegment(glistp++, 1, OS_K0_TO_PHYSICAL(framebuffers[current_fb]));

    Gfx dl[] = {
        gsDPSetColorImage(
            G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, framebuffers[current_fb]),
        gsDPSetFillColor(0),
        gsDPFillRectangle(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
        gsDPPipeSync(),
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
	osWritebackDCache(&glist, sizeof(glist));

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
init_ppu(void) {
    // NOTE: Test image.
    for (size_t j = 0; j < SCREEN_HEIGHT; j++) {
        for (size_t i = 0; i < SCREEN_WIDTH; i++) {
            u16 shade_x = (float)i / (float)SCREEN_WIDTH * 255;
            u16 shade_y = (float)j / (float)SCREEN_HEIGHT * 255;
            u16 color = GPACK_RGBA5551(shade_x, 0, shade_y, 1);
            pixels[i + j * SCREEN_WIDTH] = color;
        }
    }
    // TODO: clear pixel buffers and dirty lines

    // Setup the message queues
    osCreateMesgQueue(&rdp_msg_queue, &rdp_msg_buf, 1);
    osSetEventMesg(OS_EVENT_DP, &rdp_msg_queue, NULL);
    osCreateMesgQueue(&retrace_msg_queue, &retrace_msg_buf, 1);
    osViSetEvent(&retrace_msg_queue, NULL, 1);
}

void
swap_buffers(void) {
    osViSwapBuffer(framebuffers[current_fb]);

    // Wait for Vertical retrace to finish swap buffers.
    if (MQ_IS_FULL(&retrace_msg_queue)) {
        osRecvMesg(&retrace_msg_queue, NULL, OS_MESG_BLOCK);
    }
    osRecvMesg(&retrace_msg_queue, NULL, OS_MESG_BLOCK);

    current_fb ^= 1;
}

void
blit_framebuffer(void) {
    if (reqdraw == 0) {
        return;
    }

    for (size_t j = 0; j < screen_height; j++) {
        if (dirty_lines[j] != 0) {
            for (size_t i = 0; i < screen_width; i++) {
                size_t idx = i + j * screen_width;
                pixels[idx] = palette[pixels_fg[idx] << 2 | pixels_bg[idx]];
            }
        }
        dirty_lines[j] = 0;
    }

    // TODO: Find out how to properly draw to the framebuffer using either the
    // RDP or DMA. Maybe just drawing directly with the CPU is fine for our
    // purposes though.
    // rdp_clearfb(t, t, t);
    // fb_write_test();
    fb_copy_test(); // CPU blit
    // rdp_texture_copy(); // RDP texture blit
    reqdraw = 0;
}
