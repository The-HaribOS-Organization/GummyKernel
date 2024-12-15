#include <stdint.h>
#include <stddef.h>
#include "klibc/string.h"


/*char *strcat(char *restrict destination, const char *restrict source) {}
int strcoll(const char *first, const char *second) {}
size_t strcspn(const char *string, const char *rejectedCharacters) {}
char *strdup(const char *source) {}
char *strerror(int errCode) {}
char *strncat(char *restrict destination, const char *restrict source, size_t size) {}
char *strndup(const char *source, size_t size) {}
const char *strpbrk(const char * string, const char *searchedCharacters) {}
size_t strspn(const char *string, const char *acceptedCharacters) {}
char *strstr(char *fullString, char *substring) {}
char *strtok(char *restrict string, const char *restrict delimiters) {}
size_t strxfrm(char *restrict destination, const char *restrict source, size_t size) {}*/

size_t strlen(const char *string) {

    size_t len = 0;
    while (string[len]) len++;

    return len;
}

void *memcpy(void *restrict destination, const void *restrict source, size_t size) {

    uint8_t *dest = (uint8_t *)destination;
    uint8_t *src = (uint8_t *)source;
    
    for (size_t i = 0; i < size; i++) dest[i] = src[i];

    return destination;
}

void *memset(void *pointer, int value, size_t count) {

    uint8_t *bufferPtr = (uint8_t *)pointer;
    for (size_t i = 0; i < count; i++) bufferPtr[i] = (uint8_t)value;

    return bufferPtr;
}

int memcmp(const void *pointer1, const void *pointer2, size_t size) {

    const uint8_t *a = (const uint8_t *)pointer1;
    const uint8_t *b = (const uint8_t *)pointer2;

    for (size_t i = 0; i < size; i++) {
        
        if (a[i] < b[i]) return -1;
        else if (b[i] < a[i]) return 1;
    }

    return 0;
}

char *strcpy(char *restrict destination, const char *restrict source) {

    for (uint16_t i = 0; source[i] != '\0'; i++) *(destination + i) = *(source + i);
    return destination;
}

char *strncpy(char *restrict destination, const char *restrict source, size_t length) {

    for (size_t i = 0; i < length; i++) *(destination + i) = *(source + i);
    return destination;
}

int strcmp(const char *first, const char *second) {

    while (*first && *first == *second) {
        first++;
        second++;
    }

    return (*(int *)first - *(int *)second);
}

int strncmp(const char *first, const char *second, size_t length) {

    while (length > 0 && *first && *first == *second) {
            
            first++;
            second++;
            length--;
    }

    if (length == 0) return 0;
    else return (*(int *)first - *(int *)second);
}

void *memmove(void *destination, const void *source, size_t size) {

    uint8_t *dest = (uint8_t *)destination;
    uint8_t *src = (uint8_t *)source;
    
    for (size_t i = 0; i < size; i++) dest[i] = src[i];

    return destination;
}

void *memccpy(void *restrict destination, const void *restrict source, int ch, size_t maxSize) {

    uint8_t *dest = (uint8_t *)destination;
    uint8_t *src = (uint8_t *)source;
    size_t i = 0, flag = 0;
    
    while (i < maxSize) {
        
        dest[i] = src[i];
        if (*(src) == (uint8_t)ch) {
            flag = 1;
            break;
        }
    }

    return ((flag == 1) ? destination : NULL);
}

void *memchr(const void *memoryBlock, int searchedChar, size_t size) {

    uint8_t *mem_block = (uint8_t *)memoryBlock;
    for (size_t i = 0; i < size; i++) {

        if (*(mem_block + i) == (uint8_t)searchedChar) return (mem_block+i);
    }

    return NULL;
}

char *strchr(char *string, int searchedChar) {

    for (size_t i = 0; string[i] != '\0'; i++) {

        if (string[i] == (char)searchedChar) return (string + i);
    }

    return NULL;
}

char *strrchr(char *string, int searchedChar) {

    for (size_t i = strlen(string) - 1;  i != '\0'; i--) {

        if (string[i] == (char)searchedChar) return (string + i);
    }

    return NULL;
}
