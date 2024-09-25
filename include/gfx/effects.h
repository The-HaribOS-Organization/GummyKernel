#ifndef _EFFECT_H
#define _EFFECT_H


#include <stdint.h>
#include "gfx/utils.h"


Vec2 compute_bezier_curve(Vec2 first_point, Vec2 second_point, Vec2 reference_point, float t, uint32_t radius);
void linear_interpolate(Vec2 dimension, Vec2 lenght, Vec3 start_color, Vec3 end_color);
Vec3 alpha_blend(Vec3 current_color, Vec3 color_read);

#endif
