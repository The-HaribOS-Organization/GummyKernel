#ifndef _SHAPES_
#define _SHAPES_

#include <stdint.h>
#include <stdbool.h>
#include "gfx/utils.h"


void drawLine(Vec2 position, Vec3 color, Vec2 lenght);
void drawCircle(Vec2 position, Vec3 color, uint16_t radius, bool filled);
void drawRectangle(Vec2 position, Vec3 color, Vec2 dimension, bool filled);
void fillScreen(Vec3 color);
void bresenhamAlgorithm(Vec2 position, Vec3 color, uint16_t x, uint16_t y);

#endif
