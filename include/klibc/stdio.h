#ifndef _STDIO_
#define _STDIO_


#include <stdint.h>
#include "gfx/utils.h"
#include "klibc/string.h"


extern uint16_t row, column;
extern Vec3 _color, _stat_color, _end_color;
// Affichage de chaînes de caractères.
void printf(char *s, ...);
void putchar(const char character);

// Fonctions permettant la conversion de chaînes en entiers.
char *itoa(int_fast32_t number, const uint8_t base);
int atoi(const char *string);


inline void reverse(char *source, char *dest) {
    
    uint16_t len = strlen(source), j = 0;
    
    for (int16_t i = len - 1; i > -1; i--) {
        dest[j] = source[i];
        j++;
    }
}

#endif
