#ifndef _FRAMEBUFFER_
#define _FRAMEBUFFER_

#include <stdint.h>
#include "gfx/utils.h"
#include "gfx/effects.h"
#include "gfx/font.h"
#include "files_format/psf.h"
#include "pmm.h"
#include "klibc/string.h"


#define WIDTH 1280
#define HEIGHT 720
#define VIRTUAL_FRAMEBUFFER_ADDRESS 0xC0000000


extern volatile void *framebuffer, *backbuffer, *virtual_framebuffer;
extern uint_fast32_t pitch;
extern Vec3 background_color;
extern psf_glyphs glyphs;


static inline void init_backbuffer(uint16_t width, uint16_t height, uint8_t bpp) {

    backbuffer = k_malloc(&kheap, (width * height * bpp));
}

static inline void swap_buffer(void) {
    memcpy((void *)framebuffer, (void *)backbuffer, WIDTH * HEIGHT * 4);
}

static inline void set_framebuffer(void *buffer, uint_fast32_t pitchs) {

    framebuffer = buffer;
    virtual_framebuffer = (void *)VIRTUAL_FRAMEBUFFER_ADDRESS;
    pitch = pitchs;
    init_backbuffer(WIDTH, HEIGHT, 32);
    glyphs = init_psf_font(zap_ext_light18_psf);
    //virtual_framebuffer = (void *)VIRTUAL_FRAMEBUFFER_ADDRESS;
}

static inline Vec3 getPixelValue(Vec2 position) {

    //volatile void *buffer = (paging_enabled == 0) ? framebuffer : virtual_framebuffer;
    uint32_t color = *((uint32_t *)(framebuffer + (pitch * position.y) + (4 * position.x)));
    return (Vec3){((color >> 16) & 0xFF), ((color >> 8) & 0xFF), (color & 0xFF), 0};
}

static inline void drawPoint(Vec2 position, Vec3 color) {

    //volatile void *buffer = (paging_enabled == 0) ? framebuffer : virtual_framebuffer;
    Vec3 new_color;
    new_color = alpha_blend(color, getPixelValue(position));

    *((uint32_t *)(framebuffer + (pitch * position.y) + (4 * position.x))) = ((new_color.red << 16) | (new_color.green << 8) | (new_color.blue));
}

void scroll_windows(void);

#endif
