#include "klibc/stdio.h"

int putchar(int character)
{
    serial_putchar(character, SERIAL_COM1_PORT); // TODO : Change to terminal
}

int puts(const char *string)
{
    while(*string != '\0')
    {
        putchar(*string);
        ++string;
    }

    return 1;
}