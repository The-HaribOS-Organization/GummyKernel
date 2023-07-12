#ifndef KERNEL_IO_H_INCLUDED
#define KERNEL_IO_H_INCLUDED

#include <stdint.h>

/////////////////////////
//  Constants & types  //
/////////////////////////

#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3D5
#define FB_HIGH_BYTE 14
#define FB_LOW_BYTE 15

/////////////////
//  Functions  //
/////////////////

void outb(unsigned short port, unsigned char data);
uint8_t inb(unsigned short port);
void io_wait();

#endif // KERNEL_IO_H_INCLUDED