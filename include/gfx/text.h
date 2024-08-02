#ifndef _TEXT_
#define _TEXT_

#include <stdint.h>
#include "utils.h"


void drawChar(char character, Vec2 position, int_fast32_t foregroundColor);
void drawString(char *string, Vec2 position, Vec3 color);

#endif