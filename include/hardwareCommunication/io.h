#ifndef INCLUDE_CURSOR
#define INCLUDE_CURSOR

#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3D5
#define FB_HIGH_BYTE 14
#define FB_LOW_BYTE 15

extern void outb(unsigned short port, unsigned char data);
extern uint8_t inb(unsigned short port);
extern void io_wait();

#endif