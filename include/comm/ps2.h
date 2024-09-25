#ifndef _PS2_H
#define _PS2_H


#include <stdint.h>
#include "io.h"


#define READ_INTERNAL_RAM_0 0x20
#define READ_INTERNAL_RAN_N(x) (0x21+x)
#define WRITE_INTERNAL_RAM_0 0x60
#define WRITE_INTERNAL_RAM_N(x) (0x61+x)
#define DISABLE_SECOND_PS2 0xA7
#define ENABLE_SECOND_PS2 0xA8
#define TEST_SECOND_PS2 0xA9
#define TEST_PS2_CONTROLLER 0xAA
#define TEST_PS2_FIRST_PORT 0xAB
#define DIAGNOSTIC_DUMP 0xAC
#define DISABLE_FIRST_PS2 0xAD
#define ENABLE_FIRST_PS2 0xAE
#define READ_CONTROLLER_INPUT 0xC0
#define READ_CONTROLLER_OUTPUT 0xD0


#define COMMAND_REGISTER_PS2 0x64
#define DATA_PORT_PS2 0x60


void init_ps2(void);


static inline void disable_ps2_port(void) {

    outb(COMMAND_REGISTER_PS2, DISABLE_FIRST_PS2);
    outb(COMMAND_REGISTER_PS2, DISABLE_SECOND_PS2);
}

static inline void enable_ps2_port(void) {

    outb(COMMAND_REGISTER_PS2, ENABLE_FIRST_PS2);
    outb(COMMAND_REGISTER_PS2, ENABLE_SECOND_PS2);
}

#endif
