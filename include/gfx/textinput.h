#ifndef _TEXTINPUT_H
#define _TEXTINPUT_H


#include "gfx/utils.h"


typedef struct {
    Vec2 size;
    Vec2 position;
    Vec3 color;
    Padding padding;
    Margin margin;
    uint16_t radius;
    Vec3 text_color;
    char placeholder[20];
} text_input_t;


void draw_text_input(text_input_t text_input);


#endif
