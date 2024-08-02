#ifndef _EFFECT_H
#define _EFFECT_H


#include <stdint.h>
#include <math.h>
#include "gfx/utils.h"


void compute_bezier_curve(Vec2 first_point, Vec2 second_point, Vec2 control_point, Vec3 color);

#endif
