#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include "gfx/utils.h"
#include "gfx/text.h"
#include "gfx/framebuffer.h"
#include "libc/stdio.h"
#include "libc/string.h"
#include "libc/mem.h"
#include "gfx/shapes.h"


static uint16_t row = 0;
static uint16_t column = 0;
Vec3 _color = (Vec3){255, 255, 255, 255};

int isdigit(char c){
    return (c >= '0' && c <= '9');
}

int isAlpha(char c){
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int isAlphaNum(char c){
    return isdigit(c) || isAlpha(c);
}

void set_color(Vec3 color){
    _color = color;
}

void print_num(long val, int base, bool is_signed, bool zero_padded, int width) {
    char buf[32];
    char *p = buf + sizeof(buf) - 1;
    unsigned long abs_val = is_signed && val < 0 ? -val : val;
    bool neg = is_signed && val < 0;

    *p = '\0';
    do {
        unsigned long digit = abs_val % base;
        *--p = "0123456789abcdef"[digit];
        abs_val /= base;
    } while (abs_val > 0);

    while ((buf + sizeof(buf) - 1 - p) < width) {
        *--p = zero_padded ? '0' : ' ';
    }

    if (neg) {
        *--p = '-';
    }

    // équivalent a putstring
    while(*p){
        putchar(*p);
        p++;
    }
}

void handle_format(char **s, va_list *va_lst, bool zero_padded, size_t width) {
    switch (**s) {
        case 'd': {
            int val = va_arg(*va_lst, int);
            print_num(val, 10, true, zero_padded, width);
            break;
        }
        case 'u': {
            unsigned int val = va_arg(*va_lst, unsigned int);
            print_num(val, 10, true, zero_padded, width);
            break;
        }
        case 'x': {
            unsigned long val = va_arg(*va_lst, unsigned long);
            print_num(val, 16, true, zero_padded, width);
            break;
        }
        case 's': {
            char *val = va_arg(*va_lst, char *);
            while(*val){
                putchar(*val);
                val++;
            }
            break;
        }
        default: {
            putchar('%');
            putchar(**s);
            break;
        }
    }
    (*s)++; // Avancer le pointeur après avoir traité le spécificateur de format
}

void printf(char *string, ...) {
    va_list va_lst;
    va_start(va_lst, string);

    if (row == WIDTH) {
        row = 0;
    } else if (column == HEIGHT) {
        row = 0;
        column = 0;
        memset(framebuffer, 0, WIDTH * HEIGHT * 4);
        fillScreen((Vec3){35, 38, 39, 0});
    }
    while(*string){
        if (*string == '\x1b') { // Détection du caractère ESC (0x1b)
            if (*(string + 1) == '[') { // Détection de l'ouverture de la séquence '['
                string += 2; // Avancez le pointeur pour traiter les caractères après '['
                if (*string == '2' && *(string + 1) == 'J') {
                    // Gérer l'effacement de l'écran
                    row = 0;
                    column = 0;
                    memset(framebuffer, 0, WIDTH * HEIGHT * 4);
                    fillScreen((Vec3){35, 38, 39, 0});
                    string += 3; // Skip '2J'
                } else if (*string == 'H') {
                    // Repositionnez le curseur
                    row = 0;
                    column = 0;
                    string += 2; // Skip 'H'
                } else if (isdigit(*string) && isdigit(*(string + 1)) && isdigit(*(string + 2)) &&
                           *(string + 3) == ';' &&
                           isdigit(*(string + 4)) && isdigit(*(string + 5)) && isdigit(*(string + 6)) &&
                           *(string + 7) == ';' &&
                           isdigit(*(string + 8)) && isdigit(*(string + 9)) && isdigit(*(string + 10))) {
                    // Traiter la séquence de couleur 'xxx;xxx;xxxm'
                    uint8_t R = (*string - '0') << 4 | (*(string + 1) - '0') << 2 | (*(string + 2) - '0');
                    uint8_t G = (*(string + 4) - '0') << 4 | (*(string + 5) - '0') << 2 | (*(string + 6) - '0');
                    uint8_t B = (*(string + 8) - '0') << 4 | (*(string + 9) - '0') << 2 | (*(string + 10) - '0');
                    uint8_t A = 255;
                    if(*(string + 11) == ';' && isdigit(*(string + 12)) && isdigit(*(string + 13)) && isdigit(*(string + 14))){
                        A = (*(string + 12) - '0') << 4 | (*(string + 13) - '0') << 2 | (*(string + 14) - '0');
                        string += 3;
                    }
                    set_color((Vec3){R, G, B, A});
                    string += 12; // Skip 'xxx;xxx;xxx'
                } else {
                    // Si une autre séquence n'est pas reconnue, avancez pour ignorer la séquence
                    while (*string && *string != 'm') {
                        string++;
                    }
                    if (*string == 'm') {
                        string++; // Skip 'm'
                    }
                }
            }
        } else if (*string == '%') {
            bool zero_padded = false;
            int width = 0;
            string++;
            if (*string == '0') {
                zero_padded = true;
                string++;
            }
            while (isdigit(*string)) {
                width = width * 10 + (*string - '0');
                string++;
            }
            handle_format(&string, &va_lst, zero_padded, width);
        } else {
            putchar(*string);
            string++;
        }
    }
    va_end(va_lst);
    set_color((Vec3){255, 255, 255, 255});
}


void putchar(const char character) {
    if (character == '\n') {
        row = 0;
        column += 18;
    } else {
        drawChar(character, (Vec2){row, column}, ((_color.red << 16) | (_color.green << 8) | (_color.blue)));
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
