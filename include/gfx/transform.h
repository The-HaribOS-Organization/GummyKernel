#ifndef _TRANSFORM_H
#define _TRANSFORM_H


#include <stdint.h>
#include "gfx/utils.h"


double dot_product(Vec2 a, Vec2 b);
Vec2 scaling(Vec2 point, double a);
Vec2 rotate(Vec2 point, double angle);

#endif