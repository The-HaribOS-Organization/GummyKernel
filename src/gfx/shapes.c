#include <stdint.h>
#include <stdbool.h>
#include "io.h"
#include "gfx/framebuffer.h"
#include "gfx/shapes.h"
#include "gfx/utils.h"
#include "gfx/effects.h"
#include "klibc/math.h"


void bresenhamAlgorithm(Vec2 position, Vec3 color, uint16_t x, uint16_t y) {

	drawPoint((Vec2){position.x+x, position.y+y}, color);
    drawPoint((Vec2){position.x-x, position.y+y}, color);
    drawPoint((Vec2){position.x+x, position.y-y}, color);
    drawPoint((Vec2){position.x-x, position.y-y}, color);
    drawPoint((Vec2){position.x+y, position.y+x}, color);
    drawPoint((Vec2){position.x-y, position.y+x}, color);
    drawPoint((Vec2){position.x+y, position.y-x}, color);
    drawPoint((Vec2){position.x-y, position.y-x}, color);

    return;
}

void drawLine(Vec2 position, Vec3 color, Vec2 lenght) {

    uint_fast32_t dx = (lenght.x - position.x),
    dy = (lenght.y - position.y), y = 0;

    for (uint_fast32_t i = position.x; i < position.x + lenght.x; i++) {

        y = position.y + ((dy / dx) * (i - position.x));
        drawPoint(
            (Vec2){i, y}, color);
    }

    return;
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

    return;
}

void drawRectangle(Vec2 position, Vec3 color, Vec2 dimension, bool filled) {

    if (filled == false) {
        uint_fast32_t dx = dimension.x - position.x, dy = dimension.y - position.y;

        drawLine((Vec2){position.x, position.y}, color, (Vec2){position.x + dx, position.y});
        drawLine((Vec2){position.x, position.y + dy}, color, (Vec2){position.x + dx, position.y + dy});
        drawLine((Vec2){position.x, position.y}, color, (Vec2){position.x, position.y + dy});
        drawLine((Vec2){position.x + dx, position.y}, color, (Vec2){position.x + dx, position.y + dy});

    } else {

        for (uint_fast32_t y = position.y; y < dimension.y; ++y) {
            for (uint_fast32_t x = position.x; x < dimension.x; ++x) {

                drawPoint((Vec2){x, y}, color);
            }
        }
    }

    //swap_buffer();

    return;
}

void drawEllipse(Vec2 center_position, Vec2 radius, Vec3 color) {

    int32_t x = 0, y = radius.y, d1 = ((radius.y * radius.y) + 0.25 * radius.x * radius.x - radius.x * radius.x * radius.y);
    int32_t dx = 2 * radius.y * radius.y * center_position.x, dy = 2 * radius.x * radius.x * center_position.y;

    while (dx < dy) {

        drawPoint((Vec2){x + center_position.x, y + center_position.y}, color);
        drawPoint((Vec2){-x + center_position.x, y + center_position.y}, color);
        drawPoint((Vec2){x + center_position.x, -y + center_position.y}, color);
        drawPoint((Vec2){-x + center_position.x, -y + center_position.y}, color);
        
        if (d1 < 0) {
            
            x++;
            dx += 2 * radius.y * radius.y;
            d1 += dx + (radius.y * radius.y);
        } else {

            x++;
            y--;
            dx += 2 * radius.y * radius.y;
            dy -= 2 * radius.x * radius.x;
            d1 += dx - dy + (radius.y * radius.y);
        }
    }

    int32_t d2 = (((radius.y * radius.y) * ((x + 0.5) * (x + 0.5))) + ((radius.x * radius.x) * ((y - 1) * (y - 1))) - (radius.x * radius.x * radius.y * radius.y));
    while (y >= 0) {

        drawPoint((Vec2){x + center_position.x, y + center_position.y}, color);
        drawPoint((Vec2){-x + center_position.x, y + center_position.y}, color);
        drawPoint((Vec2){x + center_position.x, -y + center_position.y}, color);
        drawPoint((Vec2){-x + center_position.x, -y + center_position.y}, color);

        if (d2 > 0) {

            y--;
            dy += -2 * radius.x * radius.x;
            d2 += (radius.x * radius.x) - dy;
        } else {

            y--;
            x++;
            dx += 2 * radius.y * radius.y;
            dy += -2 * radius.x * radius.x;
            d2 += dx - dy + (radius.x * radius.x);
        }
    }

    
    return;
}

void fillScreen(Vec3 color) {

    for (uint_fast32_t i = 0; i < WIDTH; i++) {
        for (uint_fast32_t j = 0; j < HEIGHT; j++) {

            drawPoint((Vec2){i, j}, color);
        }
    }

    return;
}
