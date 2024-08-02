#ifndef _FRAMEBUFFER_
#define _FRAMEBUFFER_

#include <stdint.h>
#include "utils.h"


extern volatile void *framebuffer;
extern uint_fast32_t pitch;

static inline void set_framebuffer(void *buffer, uint_fast32_t pitchs) {

    framebuffer = buffer;
    pitch = pitchs;
}


static inline void drawPoint(Vec2 position, uint_fast32_t color) {

    *((uint32_t *)(framebuffer + pitch * position.y + 4 * position.x)) = color;
}

static inline Vec3 getPixelValue(Vec2 position) {

    uint32_t color = *((uint32_t *)(framebuffer + pitch * position.y + 4 * position.x));
    return (Vec3){(color << 16), (color << 8), color, 0};
}

#endif
