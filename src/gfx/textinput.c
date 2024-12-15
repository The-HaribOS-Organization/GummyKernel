#include <stdint.h>
#include "gfx/shapes.h"
#include "gfx/textinput.h"
#include "gfx/effects.h"
#include "gfx/framebuffer.h"


void draw_text_input(text_input_t text_input) {

	Vec2 pos_upper_left = {text_input.position.x + text_input.radius + text_input.margin.left, text_input.position.y + text_input.margin.top}, pos_down_right = {text_input.position.x + (text_input.size.x - text_input.radius - text_input.margin.right), text_input.position.y + text_input.size.y - text_input.margin.bottom}, point_to_draw = {0};
	Vec3 ColorsArray[sizeof(Vec3) * text_input.radius * 1001];

	drawRectangle(
		(Vec2){pos_upper_left.x, pos_upper_left.y}, text_input.color,
        (Vec2){pos_down_right.x, pos_down_right.y},
		true);

	for (uint_fast32_t i = 0; i < text_input.radius; i++) {
		for (float t = 0; t < 1.001; t+=0.001) {

    	    point_to_draw = (Vec2){((1 - t) * (1 - t) * pos_upper_left.x + 2 * (1 - t) * (pos_upper_left.x - text_input.radius - i) * t + t * t * (pos_upper_left.x - text_input.radius + i)),
			((1 - t) * (1 - t) * (pos_upper_left.y + i) + 2 * (1 - t) * (pos_upper_left.y + i) * t + t * t * (pos_upper_left.y + text_input.radius - 1))};
			ColorsArray[i] = getPixelValue(point_to_draw);
        }
    }

    for (uint_fast32_t i = 0; i < text_input.radius; i++) {
		for (float t = 0; t < 1.001; t+=0.001) {

    	    point_to_draw = (Vec2){((1 - t) * (1 - t) * pos_upper_left.x + 2 * (1 - t) * (pos_upper_left.x - text_input.radius - i) * t + t * t * (pos_upper_left.x - text_input.radius + i)),
			((1 - t) * (1 - t) * (pos_upper_left.y + i) + 2 * (1 - t) * (pos_upper_left.y + i) * t + t * t * (pos_upper_left.y + text_input.radius - 1))};

			drawPoint(point_to_draw, alpha_blend(text_input.color, ColorsArray[i]));
        }
    }

	for (uint_fast32_t i = 0; i < text_input.radius; i++) {
		for (float t = 0; t < 1.001; t+=0.001) {

    	    point_to_draw = (Vec2){((1 - t) * (1 - t) * pos_upper_left.x + 2 * (1 - t) * (pos_upper_left.x - text_input.radius + i) * t + t * t * (pos_upper_left.x - text_input.radius + i)),
			((1 - t) * (1 - t) * (pos_down_right.y - i) + 2 * (1 - t) * (pos_down_right.y - i) * t + t * t * (pos_down_right.y - text_input.radius + 1))};

			ColorsArray[i] = getPixelValue(point_to_draw);
        }
    }

	for (uint_fast32_t i = 0; i < text_input.radius; i++) {
		for (float t = 0; t < 1.001; t+=0.001) {

    	    point_to_draw = (Vec2){((1 - t) * (1 - t) * pos_upper_left.x + 2 * (1 - t) * (pos_upper_left.x - text_input.radius + i) * t + t * t * (pos_upper_left.x - text_input.radius + i)),
			((1 - t) * (1 - t) * (pos_down_right.y - i) + 2 * (1 - t) * (pos_down_right.y - i) * t + t * t * (pos_down_right.y - text_input.radius + 1))};

			drawPoint(point_to_draw, alpha_blend(text_input.color, ColorsArray[i]));
        }
    }

	drawRectangle(
		(Vec2){pos_upper_left.x - text_input.radius, pos_upper_left.y + text_input.radius}, text_input.color,
        (Vec2){pos_upper_left.x, pos_down_right.y - text_input.radius},
		true);

    for (uint_fast32_t i = 0; i < text_input.radius; i++) {
        for (float t = 0; t < 1.001; t+=0.001) {

            point_to_draw = (Vec2){
                ((1 - t) * (1 - t) * pos_down_right.x + 2 * (1 - t) * (pos_down_right.x + text_input.radius - i) * t + t * t * (pos_down_right.x + text_input.radius - i)),
			    ((1 - t) * (1 - t) * (pos_upper_left.y + i) + 2 * (1 - t) * (pos_upper_left.y + i) * t + t * t * (pos_upper_left.y + text_input.radius - 0.5))};
			ColorsArray[i] = getPixelValue(point_to_draw);
        }
    }

	for (uint_fast32_t i = 0; i < text_input.radius; i++) {

        for (float t = 0; t < 1.001; t+=0.001) {

            point_to_draw = (Vec2){
                ((1 - t) * (1 - t) * pos_down_right.x + 2 * (1 - t) * (pos_down_right.x + text_input.radius - i) * t + t * t * (pos_down_right.x + text_input.radius - i)),
			    ((1 - t) * (1 - t) * (pos_upper_left.y + i) + 2 * (1 - t) * (pos_upper_left.y + i) * t + t * t * (pos_upper_left.y + text_input.radius - 0.5))};
			drawPoint(point_to_draw, alpha_blend(text_input.color, ColorsArray[i]));
        }
    }

	for (uint_fast32_t i = 0; i < text_input.radius; i++) {
        for (float t = 0; t < 1.001; t+=0.001) {

			ColorsArray[i] = getPixelValue(
                (Vec2){((1 - t) * (1 - t) * pos_down_right.x + 2 * (1 - t) * (pos_down_right.x + text_input.radius - i) * t + t * t * (pos_down_right.x + text_input.radius - i)),
			    ((1 - t) * (1 - t) * (pos_down_right.y - i) + 2 * (1 - t) * (pos_down_right.y - i) * t + t * t * (pos_down_right.y - text_input.radius + 1))});
        }
    }

    for (uint_fast32_t i = 0; i < text_input.radius; i++) {
        for (float t = 0; t < 1.001; t+=0.001) {
            
			drawPoint(
                (Vec2){((1 - t) * (1 - t) * pos_down_right.x + 2 * (1 - t) * (pos_down_right.x + text_input.radius - i) * t + t * t * (pos_down_right.x + text_input.radius - i)),
			    ((1 - t) * (1 - t) * (pos_down_right.y - i) + 2 * (1 - t) * (pos_down_right.y - i) * t + t * t * (pos_down_right.y - text_input.radius + 1))},
                alpha_blend(text_input.color, ColorsArray[i]));
        }
    }

	drawRectangle(
		(Vec2){pos_down_right.x, pos_upper_left.y + text_input.radius}, text_input.color,
        (Vec2){pos_down_right.x + text_input.radius, pos_down_right.y - text_input.radius},
		true);

    return;
}