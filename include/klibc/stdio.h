/*
    File          : stdio.h
    Creation date : 13/07/2023
    Utility       : The stdio but treat with the terminal and not with stdin/stdout/stderr
 */

#ifndef KLIBC_STDIO_H_INCLUDED
#define KLIBC_STDIO_H_INCLUDED

#include "driver/serial_port.h"

/////////////////////////
//  Constants & types  //
/////////////////////////

/////////////////
//  Functions  //
/////////////////

int putchar(int character);
int puts(const char *string);

#endif // KLIBC_STDIO_H_INCLUDED