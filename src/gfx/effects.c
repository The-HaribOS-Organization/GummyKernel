#include <stdint.h>
#include "gfx/effects.h"
#include "gfx/framebuffer.h"
#include "gfx/utils.h"
#include "gfx/shapes.h"


Vec2 compute_bezier_curve(Vec2 first_point, Vec2 second_point, Vec2 reference_point, float t, uint32_t radius) {

    return (Vec2){
        ((1 - t) * (1 - t) * reference_point.x + 2 * (1 - t) * (second_point.x - radius) * t + t * t * (first_point.x - radius)),
        ((1 - t) * (1 - t) * reference_point.y + 2 * (1 - t) * (second_point.y - radius) * t + t * t * (first_point.y - radius))};
}


void linear_interpolate(Vec2 dimension, Vec2 lenght, Vec3 start_color, Vec3 end_color) {

	for (float i = dimension.y; i < dimension.y + lenght.y + 1; i++) {

		drawLine(
			(Vec2){dimension.x, i},
			(Vec3){
				(1 - (i / (dimension.y + lenght.y))) * (float)start_color.red + (float)end_color.red * i / (dimension.y + lenght.y),
                (1 - (i / (dimension.y + lenght.y))) * (float)start_color.green + (float)end_color.green * i / (dimension.y + lenght.y),
                (1 - (i / (dimension.y + lenght.y))) * (float)start_color.blue + (float)end_color.blue * i / (dimension.y + lenght.y), 0},
            (Vec2){(dimension.x + lenght.x), i});
	}
}


Vec3 alpha_blend(Vec3 current_color, Vec3 color_read) {

    return (Vec3){((color_read.red * current_color.alpha + current_color.red * (255 - current_color.alpha)) / 255),
    ((color_read.green * current_color.alpha + current_color.green * (255 - current_color.alpha)) / 255),
    ((color_read.blue * current_color.alpha + current_color.blue * (255 - current_color.alpha)) / 255), 0};
}
