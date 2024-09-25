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
static Vec3 _color = (Vec3){86, 66, 49, 0}, _stat_color = (Vec3){255, 91, 91, 0}, _end_color = (Vec3){255, 164, 91, 0};


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

// Fonction pour extraire un nombre entier de la chaîne de caractères
int parse_number(char **s) {

    int num = 0;
    while (isdigit(**s)) {
        num = num * 10 + (**s - '0');
        (*s)++;
    }
    return num;
}


void handle_format(char c, va_list *va_lst, bool zero_padded, int width) {

    switch (c) {
    
        case 'd': {
            int val = va_arg(*va_lst, int);
            print_num(val, 10, true, zero_padded, width);
            break;
        }
    
        case 'u': {
            unsigned int val = va_arg(*va_lst, unsigned int);
            print_num(val, 10, false, zero_padded, width);
            break;
        }
    
        case 'x':
        case 'X': {
            unsigned long val = va_arg(*va_lst, unsigned long long);
            print_num(val, 16, false, zero_padded, width);
            break;
        }
    
        case 'p': {
            unsigned long val = va_arg(*va_lst, unsigned long);
            print_num(val, 16, false, true, 8);
            break;
        }
    
        case 's': {
            char *str = va_arg(*va_lst, char *);
            printf(str);
            break;
        }
    
        case 'c': {
            char val = (char) va_arg(*va_lst, int);
            putchar(val);
            break;
        }
    
        default: {
            putchar('%');
            putchar(c);
            break;
        }
    }
}

void handle_color(char **s) {
    
    (*s)++;
    if (**s == '[') {
    
        (*s)++;
        uint8_t R = 0, G = 0, B = 0, A = 255; // Valeurs par défaut
        bool color_set = false;
        int color = parse_number(s);
        

        // Traitement des codes de couleur
        if (color >= 30 && color <= 37) {
            // Couleurs de texte standard
            switch (color) {

                case 30: R = 0; G = 0; B = 0; break;       // Noir
                case 31: R = 255; G = 0; B = 0; break;       // Rouge
                case 32: R = 0; G = 255; B = 0; break;       // Vert
                case 33: R = 255; G = 255; B = 0; break;     // Jaune
                case 34: R = 0; G = 0; B = 255; break;       // Bleu
                case 35: R = 255; G = 0; B = 255; break;     // Magenta
                case 36: R = 0; G = 255; B = 255; break;     // Cyan
                case 37: R = 255; G = 255; B = 255; break;   // Blanc
            }
            color_set = true;
        } else if (color >= 90 && color <= 97) {
    
            // Couleurs de texte claires
            switch (color) {
                case 90: R = 169; G = 169; B = 169; break;   // Gris clair
                case 91: R = 255; G = 69; B = 0; break;       // Orange
                case 92: R = 50; G = 205; B = 50; break;      // Vert clair
                case 93: R = 255; G = 255; B = 102; break;    // Jaune clair
                case 94: R = 135; G = 206; B = 235; break;    // Bleu clair
                case 95: R = 255; G = 105; B = 180; break;    // Rose
                case 96: R = 0; G = 206; B = 209; break;      // Turquoise
                case 97: R = 211; G = 211; B = 211; break;    // Gris très clair
            }
            color_set = true;
        } else if((color >= 0 && color <= 255) && !color_set){
    
            R = color;
            if (**s == ';') {
                (*s)++;
                G = parse_number(s);
                if (**s == ';') {
                    (*s)++;
                    B = parse_number(s);
                    if (**s == ';') {
                        (*s)++;
                        A = parse_number(s);
                    }
                }
            }
            color_set = true;
        }

        if (**s == 'm') (*s)++;
        if (color_set) set_color((Vec3) {R, G, B, A});
    }
}

void printf(char *s, ...) {
    
    va_list va_lst;
    va_start(va_lst, s);

    if (row == WIDTH) {
        column++;
    } else if (column == HEIGHT) {
        memset((void *)framebuffer, 0, WIDTH * HEIGHT * 4);
        linear_interpolate((Vec2){0, 0}, (Vec2){WIDTH, HEIGHT}, _stat_color, _end_color);
        drawRectangle((Vec2){0, 0}, (Vec3){255, 255, 255, 200}, (Vec2){WIDTH, HEIGHT}, true);
    }

    while(*s) {

        if (*s == '\x1b') {

            if (*(s + 1) == '[') {
            
                if (*(s + 2) == '2' && *(s + 3) == 'J') {
                    // Gérer l'effacement de l'écran
                    row = 0;
                    column = 0;
                    memset((void *)framebuffer, 0, WIDTH * HEIGHT * 4);
                    linear_interpolate((Vec2){0, 0}, (Vec2){WIDTH, HEIGHT}, _stat_color, _end_color);
                    s += 4; // Skip '2J'
                } else if (*(s + 2) == 'H') {
                    // Repositionnez le curseur
                    row = 0;
                    column = 0;
                    s += 3; // Skip 'H'
                } else {
                    // Traitez les séquences de couleur ici
                    handle_color(&s);
                }
            
            } else {
                // Traitez d'autres séquences d'échva_lstpement ici si nécessaire
                s++;
            }

        } else if (*s == '%') {

            bool zero_padded = false;
            int width = 0;
            s++;

            if (*s == '0') {
                zero_padded = true;
                s++;
            }

            while (isdigit(*s)) {
                width = width * 10 + (*s - '0');
                s++;
            }

            handle_format(*s, &va_lst, zero_padded, width);
            s++;

        } else {

            putchar(*s++);
        }
    }

    va_end(va_lst);
    set_color((Vec3){0, 0, 0, 0});
}


void putchar(const char character) {

    if (character == '\n') {
        row = 0;
        column += 18;
    } else {

        drawChar(character, (Vec2){row, column}, _color);
        row += 8;
    }
}

int atoi(const char *s) {

    int result = 0, sum = 0;
    for (uint16_t i = 0; s[i] != '\0'; i++) {

        result = s[i] - 0x30;
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
