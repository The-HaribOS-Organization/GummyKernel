#include <stdint.h>
#include "gfx/text.h"
#include "gfx/framebuffer.h"
#include "gfx/font.h"


void drawChar(char character, Vec2 position, int_fast32_t foregroundColor) {

	Vec3 Colors;
	int_fast32_t mask[8] = {128, 64, 32, 16, 8, 4, 2, 1};
	uint8_t *glyph = g_8x16_font + (int_fast32_t)character * 16;

	for (uint8_t cy = 0; cy < 16; cy++) {
		for (uint8_t cx = 0; cx < 8; cx++) {
			
			Colors = getPixelValue((Vec2){position.x + cx, position.y + cy});
			drawPoint((Vec2){(position.x + cx), ((position.y + cy))}, glyph[cy]&mask[cx]?foregroundColor:((Colors.red << 16) | (Colors.green << 8) | Colors.blue));
		}
	}
}

void drawString(char *string, Vec2 position, Vec3 color) {

    uint_fast32_t dx = 0;

    for (int i = 0; string[i] != '\0'; i++) {

        drawChar(string[i], (Vec2){position.x + dx, position.y}, ((color.red << 16) | (color.green << 8) | color.blue));
        dx += 8;
    } 
}
