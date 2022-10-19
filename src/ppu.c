// Screen size.
#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

static OSMesg retrace_msg_buf;
static OSMesgQueue retrace_msg_queue;

//
// Framebuffers.
//

u16 framebuffers[2][SCREEN_WIDTH * SCREEN_HEIGHT] __attribute__((aligned(16)));

//
// Statics.
//

static u16 pixels[SCREEN_WIDTH * SCREEN_HEIGHT] __attribute__((aligned(16)));
static int current_fb = 0;

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
fb_copy_test(void) {
    for (size_t i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++) {
        framebuffers[current_fb][i] = pixels[i];
    }
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
    current_fb ^= 1;
    fb_copy_test();
    reqdraw = 0;
}
