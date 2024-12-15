#include <stdint.h>
#include "gfx/utils.h"
#include "gfx/shapes.h"
#include "gfx/effects.h"
#include "gfx/frame.h"
#include "gfx/framebuffer.h"


void draw_frame(frame_t frame) {

    Vec2 pos_upper_left = {frame.position.x + frame.radius + frame.margin.left, frame.position.y + frame.margin.top}, pos_down_right = {frame.position.x + (frame.size.x - frame.radius - frame.margin.right), frame.position.y + frame.size.y - frame.margin.bottom}, point_to_draw = {0};
	Vec3 ColorsArray[sizeof(Vec3) * frame.radius * 1001];


    drawRectangle(
	  	(Vec2){pos_upper_left.x, pos_upper_left.y}, frame.color,
        (Vec2){pos_down_right.x, pos_down_right.y},
  		true);

	for (uint_fast32_t i = 0; i < frame.radius; i++) {
		for (float t = 0; t < 1.001; t+=0.001) {

    	    point_to_draw = (Vec2){((1 - t) * (1 - t) * pos_upper_left.x + 2 * (1 - t) * (pos_upper_left.x - frame.radius - i) * t + t * t * (pos_upper_left.x - frame.radius + i)),
			((1 - t) * (1 - t) * (pos_upper_left.y + i) + 2 * (1 - t) * (pos_upper_left.y + i) * t + t * t * (pos_upper_left.y + frame.radius - 1))};
			ColorsArray[i] = getPixelValue(point_to_draw);
        }
    }

    for (uint_fast32_t i = 0; i < frame.radius; i++) {
		for (float t = 0; t < 1.001; t+=0.001) {

    	    point_to_draw = (Vec2){((1 - t) * (1 - t) * pos_upper_left.x + 2 * (1 - t) * (pos_upper_left.x - frame.radius - i) * t + t * t * (pos_upper_left.x - frame.radius + i)),
			((1 - t) * (1 - t) * (pos_upper_left.y + i) + 2 * (1 - t) * (pos_upper_left.y + i) * t + t * t * (pos_upper_left.y + frame.radius - 1))};

			drawPoint(point_to_draw, alpha_blend(frame.color, ColorsArray[i]));
        }
    }

	for (uint_fast32_t i = 0; i < frame.radius; i++) {
		for (float t = 0; t < 1.001; t+=0.001) {

    	    point_to_draw = (Vec2){((1 - t) * (1 - t) * pos_upper_left.x + 2 * (1 - t) * (pos_upper_left.x - frame.radius + i) * t + t * t * (pos_upper_left.x - frame.radius + i)),
			((1 - t) * (1 - t) * (pos_down_right.y - i) + 2 * (1 - t) * (pos_down_right.y - i) * t + t * t * (pos_down_right.y - frame.radius + 1))};

			ColorsArray[i] = getPixelValue(point_to_draw);
        }
    }

	for (uint_fast32_t i = 0; i < frame.radius; i++) {
		for (float t = 0; t < 1.001; t+=0.001) {

    	    point_to_draw = (Vec2){((1 - t) * (1 - t) * pos_upper_left.x + 2 * (1 - t) * (pos_upper_left.x - frame.radius + i) * t + t * t * (pos_upper_left.x - frame.radius + i)),
			((1 - t) * (1 - t) * (pos_down_right.y - i) + 2 * (1 - t) * (pos_down_right.y - i) * t + t * t * (pos_down_right.y - frame.radius + 1))};

			drawPoint(point_to_draw, alpha_blend(frame.color, ColorsArray[i]));
        }
    }

	drawRectangle(
		(Vec2){pos_upper_left.x - frame.radius, pos_upper_left.y + frame.radius}, frame.color,
        (Vec2){pos_upper_left.x, pos_down_right.y - frame.radius},
		true);

    for (uint_fast32_t i = 0; i < frame.radius; i++) {
        for (float t = 0; t < 1.001; t+=0.001) {

            point_to_draw = (Vec2){
                ((1 - t) * (1 - t) * pos_down_right.x + 2 * (1 - t) * (pos_down_right.x + frame.radius - i) * t + t * t * (pos_down_right.x + frame.radius - i)),
			    ((1 - t) * (1 - t) * (pos_upper_left.y + i) + 2 * (1 - t) * (pos_upper_left.y + i) * t + t * t * (pos_upper_left.y + frame.radius - 0.5))};
			ColorsArray[i] = getPixelValue(point_to_draw);
        }
    }

	for (uint_fast32_t i = 0; i < frame.radius; i++) {

        for (float t = 0; t < 1.001; t+=0.001) {

            point_to_draw = (Vec2){
                ((1 - t) * (1 - t) * pos_down_right.x + 2 * (1 - t) * (pos_down_right.x + frame.radius - i) * t + t * t * (pos_down_right.x + frame.radius - i)),
			    ((1 - t) * (1 - t) * (pos_upper_left.y + i) + 2 * (1 - t) * (pos_upper_left.y + i) * t + t * t * (pos_upper_left.y + frame.radius - 0.5))};
			drawPoint(point_to_draw, alpha_blend(frame.color, ColorsArray[i]));
        }
    }

	for (uint_fast32_t i = 0; i < frame.radius; i++) {
        for (float t = 0; t < 1.001; t+=0.001) {

			ColorsArray[i] = getPixelValue(
                (Vec2){((1 - t) * (1 - t) * pos_down_right.x + 2 * (1 - t) * (pos_down_right.x + frame.radius - i) * t + t * t * (pos_down_right.x + frame.radius - i)),
			    ((1 - t) * (1 - t) * (pos_down_right.y - i) + 2 * (1 - t) * (pos_down_right.y - i) * t + t * t * (pos_down_right.y - frame.radius + 1))});
        }
    }

    for (uint_fast32_t i = 0; i < frame.radius; i++) {
        for (float t = 0; t < 1.001; t+=0.001) {
            
			drawPoint(
                (Vec2){((1 - t) * (1 - t) * pos_down_right.x + 2 * (1 - t) * (pos_down_right.x + frame.radius - i) * t + t * t * (pos_down_right.x + frame.radius - i)),
			    ((1 - t) * (1 - t) * (pos_down_right.y - i) + 2 * (1 - t) * (pos_down_right.y - i) * t + t * t * (pos_down_right.y - frame.radius + 1))},
                alpha_blend(frame.color, ColorsArray[i]));
        }
    }

	drawRectangle(
		(Vec2){pos_down_right.x, pos_upper_left.y + frame.radius}, frame.color,
        (Vec2){pos_down_right.x + frame.radius, pos_down_right.y - frame.radius},
		true);

    return;
}