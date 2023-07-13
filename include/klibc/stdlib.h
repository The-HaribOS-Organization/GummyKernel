/*
    File          : stdlib.h
    Creation date : 13/07/2023
 */

#ifndef KLIBC_STDLIB_H_INCLUDED
#define KLIBC_STDLIB_H_INCLUDED

#include <assert.h>
#include <stdbool.h>
#include <string.h>

/////////////////////////
//  Constants & types  //
/////////////////////////

#define HEAP_CAPACITY (256 << 10)
#define HEAP_ALLOCATED_CHUNKS_CAPACITY (2 << 10)

/////////////////
//  Functions  //
/////////////////

void *malloc(size_t memorySize);
void *calloc(size_t elementCount, size_t elementSize);
void *realloc(void *ptr, size_t memorySize);

void free(void *ptr);

/////////////////////////////
//  Non standard fucntion  //
/////////////////////////////

char *itoa(int num, char *str, int base);

#endif // KLIBC_STDLIB_H_INCLUDED