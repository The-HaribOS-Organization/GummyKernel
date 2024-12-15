#ifndef _STRING_
#define _STRING_


#include <stdint.h>
#include <stddef.h>


void *memccpy(void *restrict destination, const void *restrict source, int ch, size_t maxSize);
void *memchr(const void *memoryBlock, int searchedChar, size_t size);
int memcmp(const void *pointer1, const void *pointer2, size_t size);
void *memcpy(void *restrict destination, const void *restrict source, size_t size);
void *memmove(void *destination, const void *source, size_t size);
void *memset(void *pointer, int value, size_t count);
char *strcat(char *restrict destination, const char *restrict source);
char *strchr(char *string, int searchedChar);
int strcmp(const char *first, const char *second);
int strcoll(const char *first, const char *second);
char *strcpy(char *restrict destination, const char *restrict source);
size_t strcspn(const char *string, const char *rejectedCharacters);
char *strdup(const char *source);
char *strerror(int errCode);
size_t strlen(const char *string);
char *strncat(char *restrict destination, const char *restrict source, size_t size);
int strncmp(const char *first, const char *second, size_t length);
char *strncpy(char *restrict destination, const char *restrict source, size_t length);
char *strndup(const char *source, size_t size);
const char *strpbrk(const char * string, const char *searchedCharacters);
char *strrchr(char *string, int searchedChar);
size_t strspn(const char *string, const char *acceptedCharacters);
char *strstr(char *fullString, char *substring);
char *strtok(char *restrict string, const char *restrict delimiters);
size_t strxfrm(char *restrict destination, const char *restrict source, size_t size);

#endif
