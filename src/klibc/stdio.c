#include "klibc/stdio.h"

int putchar(int character)
{
    serial_putchar(character, SERIAL_COM1_PORT); // TODO : Change to terminal
    return character;
}

int puts(const char *string)
{
    while(*string != '\0')
    {
        putchar(*string);
        ++string;
    }
    putchar('\n');

    return 1;
}