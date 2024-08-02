#ifndef _IO_
#define _IO_


#include <stdint.h>

inline void outb(uint16_t comPort, uint8_t value) {

    __asm__ volatile (
        "outb %0, %1"
        :: "a"(value),
        "Nd"(comPort) : "memory");
}

inline uint8_t inb(uint16_t comPort) {

    uint8_t result;

    __asm__ volatile (
        "inb %1, %0"
        : "=a"(result) : "Nd"(comPort) : "memory");

    return result;
}

#endif
