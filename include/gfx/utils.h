#ifndef _UTILS_
#define _UTILS_

#include <stdint.h>

#define RGB2GRAY(r, g, b) (0.299 * r + 0.587 * g + 0.114 * b)
#define BGR2RGB(b, g, r) ((r >> 24) | (g >> 16) | (b >> 8))
#define RGB2BGR(r, g, b) ((b >> 24) | (g >> 16) | (r >> 8))
#define RGBA2VEC3(rgba) ((Vec3){.red = (uint8_t)((rgba) >> 24), .green = (uint8_t)((rgba) >> 16), .blue = (uint8_t)((rgba) >> 8), .alpha = 0 })

typedef struct {

    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
} Vec3;

typedef struct {

    uint_fast32_t x;
    uint_fast32_t y;
} Vec2;

#endif
