#ifndef _FRAMEBUFFER_
#define _FRAMEBUFFER_

#include <stdint.h>
#include "gfx/utils.h"
#include "gfx/effects.h"


#define WIDTH 1280
#define HEIGHT 720


extern volatile void *framebuffer;
extern uint_fast32_t pitch;
extern Vec3 background_color;

static inline void set_framebuffer(void *buffer, uint_fast32_t pitchs) {

    framebuffer = buffer;
    pitch = pitchs;
}

static inline Vec3 getPixelValue(Vec2 position) {

    uint32_t color = *((uint32_t *)(framebuffer + (pitch * position.y) + (4 * position.x)));
    return (Vec3){((color >> 16) & 0xFF), ((color >> 8) & 0xFF), (color & 0xFF), 0};
}

static inline void drawPoint(Vec2 position, Vec3 color) {

    Vec3 color_read, new_color;
    color_read = getPixelValue(position);
    new_color = alpha_blend(color, color_read);

    *((uint32_t *)(framebuffer + (pitch * position.y) + (4 * position.x))) = ((new_color.red << 16) | (new_color.green << 8) | (new_color.blue));
}

#endif
