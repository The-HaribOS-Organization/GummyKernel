#include <stdint.h>
#include <stdbool.h>
#include "io.h"
#include "gfx/framebuffer.h"
#include "gfx/shapes.h"
#include "gfx/utils.h"
#include "gfx/effects.h"


void bresenhamAlgorithm(Vec2 position, Vec3 color, uint16_t x, uint16_t y) {

	drawPoint((Vec2){position.x+x, position.y+y}, color);
    drawPoint((Vec2){position.x-x, position.y+y}, color);
    drawPoint((Vec2){position.x+x, position.y-y}, color);
    drawPoint((Vec2){position.x-x, position.y-y}, color);
    drawPoint((Vec2){position.x+y, position.y+x}, color);
    drawPoint((Vec2){position.x-y, position.y+x}, color);
    drawPoint((Vec2){position.x+y, position.y-x}, color);
    drawPoint((Vec2){position.x-y, position.y-x}, color);
}

void drawLine(Vec2 position, Vec3 color, Vec2 lenght) {

    uint_fast32_t dx = (lenght.x - position.x),
    dy = (lenght.y - position.y), y = 0;

    for (uint_fast32_t i = position.x; i < position.x + lenght.x; i++) {

        y = position.y + ((dy / dx) * (i - position.x));
        drawPoint(
            (Vec2){i, y}, color);
    }
}

void drawCircle(Vec2 position, Vec3 color, uint16_t radius, bool filled) {

	uint16_t d = 3 - 2 * radius, x = 0, y = radius;

	if (filled == true) {

		bresenhamAlgorithm(position, color, x, y);
		while (x <= y) {

            x++;
            if (d <= 0) {
                d += 4 * x + 6;
            } else {

                d += 4 * (x - y) + 10;
                y--;
            }

            bresenhamAlgorithm(position, color, x, y);
        }
	} else {

		for (uint16_t i = 0; i < radius; i++) {

			d = 3 - 2 * i;
    	    x = 0;
	        y = i;

			bresenhamAlgorithm(position, color, x, y);
			while (x <= y) {

            	x++;
        	    if (d <= 0) {

    	            d += 4 * x + 6;
	            } else {

	                d += 4 * (x - y) + 10;
                	y--;
            	}

				bresenhamAlgorithm(position, color, x, y);
        	}
		}
	}
}

void drawRectangle(Vec2 position, Vec3 color, Vec2 dimension, bool filled) {

    uint_fast32_t dx = (dimension.x + position.x) - position.x;
    uint_fast32_t dy = (dimension.y + position.y) - position.y;

    if (filled == true) {

        for (uint_fast16_t y = position.y; y < position.y + dimension.y; y++) {
            for (uint_fast16_t x = position.x; x < position.x + dimension.x; x++) {

                drawPoint((Vec2){x, y}, color);
            }
        }
    } else {
        
        drawLine((Vec2){position.x, position.y}, color, (Vec2){position.x + dx, position.y});
        drawLine((Vec2){position.x, position.y + dy}, color, (Vec2){position.x + dx, position.y + dy});
        drawLine((Vec2){position.x, position.y}, color, (Vec2){position.x, position.y + dy});
        drawLine((Vec2){position.x + dx, position.y}, color, (Vec2){position.x + dx, position.y + dy});
    }
}


void fillScreen(Vec3 color) {

    for (uint_fast32_t i = 0; i < WIDTH; i++) {
        for (uint_fast32_t j = 0; j < HEIGHT; j++) {

            drawPoint((Vec2){i, j}, color);
        }
    }
}
