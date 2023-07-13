/*
    File    : serial_port.h
    Utility : The serial port driver
 */

#ifndef KERNEL_SERIAL_PORT_H_INCLUDED
#define KERNEL_SERIAL_PORT_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

#include "hardwareCommunication/io.h"

/////////////////////////
//  Constants & types  //
/////////////////////////

typedef enum {
    SERIAL_COM1_PORT = 0x3F8,
    SERIAL_COM2_PORT = 0x2F8,
    SERIAL_COM3_PORT = 0x3E8,
    SERIAL_COM4_PORT = 0x2E8,
    SERIAL_COM5_PORT = 0x5F8,
    SERIAL_COM6_PORT = 0x4F8,
    SERIAL_COM7_PORT = 0x5E8,
    SERIAL_COM8_PORT = 0x4E8
} SerialPorts;

#define SERIAL_COM_PORT(base) (base)
#define SERIAL_ACTIVATION_INTERRUPT(base) (base+1)
#define SERIAL_ACTIVATION_INTERRUPT_FIFO(base) (base+2)
#define SERIAL_LINE_CONTROL(base) (base+3)
#define SERIAL_MODEM_CONTROL(base) (base+4)
#define SERIAL_LINE_STATE(base) (base+5)
#define SERIAL_MODEM_STATE(base) (base+6)
#define SERIAL_GRAB_REGISTER(base) (base+7)

#define SERIAL_LINE_ENABLE_DLAB 0x80

/////////////////
//  Functions  //
/////////////////

void serial_setBaudsSpeedRate(uint16_t com, uint16_t divisor);
void serial_configureLine(uint16_t com);

uint8_t serial_isFIFOEmpty(uint16_t com);
uint16_t serial_isRecieved(uint16_t com);

char serial_read(uint16_t com);

void serial_putchar(unsigned char character, uint16_t com);
void serial_print(const char *string, uint16_t com);

#endif // KERNEL_SOUND_BLASTER_H_INCLUDED