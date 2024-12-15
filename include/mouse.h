#ifndef _MOUSE_H
#define _MOUSE_H


#include <stdint.h>
#include "interrupt/isr.h"
#include "interrupt/8259PIC.h"
#include "io.h"


#define RESET 0xFF
#define RESEND 0xFE
#define SET_DEFAULT 0xF6
#define DISABLE_PACKET_STREAMING 0xF5
#define ENABLE_PACKET_STREAMING 0xF4
#define SET_SAMPLE_RATE 0xF3
#define GET_MOUSID 0xF2
#define REQUEST_SINGLE_PACKET 0xEB
#define STATUS_REQUEST 0xE9
#define SET_RESOLUTION 0xE8
#define SET_REMOTE_MODE 0xF0
#define SET_WRAP_MODE 0xEE
#define RESET_WRAP_MODE 0xEC
#define SET_STREAM_MODE 0xEA
#define SET_SCALLING_2_1 0xE7
#define SET_SCALLING_1_1 0xE6

#define DATA_PORT 0x60
#define COMMAND_REGISTER_KBOARD 0x64


void init_mouse(void);
void mouse_handler(isr_frame *frame);


inline void write_mouse(uint8_t info) {

    outb(COMMAND_REGISTER_KBOARD, 0xD4);
    outb(DATA_PORT, info);
}

inline uint8_t read_mouse(void) {

    return inb(DATA_PORT);
}

#endif
