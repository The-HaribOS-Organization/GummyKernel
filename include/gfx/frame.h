#ifndef _FRAME_H
#define _FRAME_H


#include <stdint.h>
#include "gfx/utils.h"


typedef struct {
    Vec2 size;
    Vec2 position;
    Margin margin;
    Padding padding;
    Border border;
    Vec3 color;
    Vec3 color_border;
    uint16_t radius;
} frame_t;


void draw_frame(frame_t frame);

#endif
