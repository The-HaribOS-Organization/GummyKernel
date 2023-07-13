/*
    File          : stdlib.h
    Creation date : 13/07/2023
    Utility       : The stdio but treat with the terminal and not with stdin/stdout/stderr
 */

#ifndef KLIBC_STDLIB_H_INCLUDED
#define KLIBC_STDLIB_H_INCLUDED

#include <stdbool.h>
#include <string.h>

/////////////////////////
//  Constants & types  //
/////////////////////////

/////////////////
//  Functions  //
/////////////////

/////////////////////////////
//  Non standard fucntion  //
/////////////////////////////

char *itoa(int num, char *str, int base);

#endif // KLIBC_STDLIB_H_INCLUDED