#include <stdint.h>
#include <stddef.h>
#include "libc/mem.h"


void *memcpy(void *srcPtr, void *destPtr, size_t size) {

    uint8_t *dest = (uint8_t *)destPtr;
    uint8_t *src = (uint8_t *)srcPtr;
    for (size_t i = 0; i < size; i++) {
        dest[i] = src[i];
    }

    return destPtr;
}

void *memset(void *buffer, uint32_t value, size_t size) {

    uint8_t *bufferPtr = (uint8_t *)buffer;
    for (size_t i = 0; i < size; i++) {
        bufferPtr[i] = (uint8_t)value;
    }

    return buffer;
}

uint32_t memcmp(const void *ptra, const void *ptrb, size_t size) {

    const uint8_t *a = (const uint8_t *)ptra;
    const uint8_t *b = (const uint8_t *)ptrb;
    for (size_t i = 0; i < size; i++) {
        if (a[i] < b[i]) {
            return -1;
        } else if (b[i] < a[i]) {
            return 1;
        }
    }

    return 0;
}