#include <stdint.h>
#include <stddef.h>
#include "gfx/text.h"
#include "gfx/framebuffer.h"
#include "gfx/font.h"
#include "files_format/psf.h"


void drawChar(char character, Vec2 position, Vec3 foregroundColor) {

	Vec3 Colors;
	int_fast32_t mask[8] = {128, 64, 32, 16, 8, 4, 2, 1};
#ifdef USE_PSF1_FORMAT
	uint8_t *glyph = zap_ext_light18_psf + sizeof(psf1_header) + (int32_t)character * 18;
#endif
	for (int32_t cy = 0; cy < 18; cy++) {

		for (int32_t cx = 0; cx < 8; cx++) {
			Colors = getPixelValue((Vec2){position.x + cx, position.y + cy});
			drawPoint((Vec2){(position.x + cx), ((position.y + cy))}, glyph[cy]&mask[cx]?foregroundColor:Colors);
		}
	}
}

void drawString(char *string, Vec2 position, Vec3 color) {

    uint_fast32_t dx = 0;

    for (int i = 0; string[i] != '\0'; i++) {

        drawChar(string[i], (Vec2){position.x + dx, position.y}, color);
        dx += 8;
    } 
}
