#include <stdint.h>
#include <stdbool.h>
#include "gfx/utils.h"
#include "gfx/text.h"
#include "gfx/framebuffer.h"
#include "libc/stdio.h"
#include "libc/string.h"
#include "libc/mem.h"
#include "gfx/shapes.h"


static uint16_t row = 0;
static uint16_t column = 0;


void printf(const char *string, const Vec3 color) {

    if (row == WIDTH) {
        row = 0;
    } else if (column == HEIGHT) {
        row = 0;
        column = 0;
        memset(framebuffer, 0, WIDTH * HEIGHT * 4);
        fillScreen((Vec3){35, 38, 39, 0});
    }

    for (uint16_t i = 0; string[i] != '\0'; i++)
        putchar(string[i], color);
}

void putchar(const char character, const Vec3 color) {

    if (character == '\n') {

        row = 0;
        column += 18;
    } else {

        drawChar(character, (Vec2){row, column}, ((color.red << 16) | (color.green << 8) | (color.blue)));
        row += 8;
    }
}

int atoi(const char *string) {

    int result = 0, sum = 0;
    for (uint16_t i = 0; string[i] != '\0'; i++) {

        result = string[i] - 0x30;
        sum = (sum * 10) + result;
    }

    return sum;
}

char *itoa(int_fast32_t number, const uint8_t base) {

    int_fast32_t i = 0;
    bool isNeg = false;
    static char source[20], dest[20];

    memset(source, 0, sizeof(source));
    memset(dest, 0, sizeof(dest));

    if (number == 0) {
        source[i++] = '0';
        source[i] = '\0';
        return dest;
    }

    if (number < 0 && base == 10) {
        isNeg = true;
        number = -number;
    }

    do {
        int result = number % base;
        source[i++] = (result > 9) ? (result - 10) + 'a' : result + '0';
        number /= base;
    } while (number != 0);

    if (isNeg) {
        dest[i++] = '-';
    }

    source[i++] = '\0';
    reverse(source, dest);
    
    return dest;
}
