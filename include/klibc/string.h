/*
    File          : string.h
    Creation date : 11/07/2023
 */

#ifndef KLIBC_STRING_H_INCLUDED
#define KLIBC_STRING_H_INCLUDED

#include <stddef.h>
#include <stdint.h>

/////////////////////////
//  Constants & types  //
/////////////////////////

#define NULL (void*)0

typedef unsigned long long size_t;

/////////////////
//  Functions  //
/////////////////

void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
void *memchr(const void *str, int c, size_t n);
int memcmp(const void *ptr1, const void *ptr2, size_t n);
void *memset(void *ptr, int value, size_t count);
// char *strcat(char *dest, const char *src);
// char *strncat(char *dest, const char * src, size_t n);
// char *strchr(const char *str, int c);
// char *strrchr(const char *, int);
// int strcmp(const char *str1, const char *str2);
// int strncmp(const char *str1, const char *str2, size_t n);
// int strcoll(const char *str1, const char *str2);
// char *strcpy(char *dest, const char *src);
// char *strncpy(char *dest, const char *src, size_t n);
// char *strerror(int errnum);
size_t strlen(const char *str);
// size_t strspn(const char *str, const char *accept);
// size_t strcspn(const char *str, const char *reject);
// char *strpbrk(const char *str1, const char *str2);
// char *strstr(const char *str, const char *c);
// char *strtok(char *str, const char *delim);
// size_t strxfrm(char *dest, const char *src, size_t n);

/////////////////////////////
//  Non standard fucntion  //
/////////////////////////////

char *strrev(char *str);

#endif // KLIBC_STRING_H_INCLUDED