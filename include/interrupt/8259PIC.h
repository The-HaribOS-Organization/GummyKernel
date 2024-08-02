#ifndef _8259PIC_
#define _8259PIC_


#include <stdint.h>
#include "io.h"


#define MASTER_PIC_COMMAND 0x0020
#define MASTER_PIC_DATA 0x0021
#define SLAVE_PIC_COMMAND 0x00A0
#define SLAVE_PIC_DATA 0x00A1
#define PIC_EOI 0x20

#define ICW_ICW4 0x01
#define ICW_SINGLE 0x02
#define ICW_INTERVAL 0x04
#define ICW_LEVEL 0x08
#define ICW_INIT 0x10

#define ICW_8086 0x01
#define ICW_AUTO 0x02
#define ICW_BUFFER_SLAVE 0x08
#define ICW_BUFFER_MASTER 0x0C
#define ICW_SFNM 0x10

#define PIC_INIT_SEQUENCE 0x11


void initPIC(void);
void pic_set_mask(uint8_t irq);
void pic_clear_mask(uint8_t irq);
void remapPIC(uint8_t first_offset, uint8_t second_offset);
void pic_send_eoi(uint8_t irq);

inline void disable_pic(void) {

    outb(MASTER_PIC_DATA, 0xFF);
    outb(SLAVE_PIC_DATA, 0xFF);
}

inline uint8_t get_mask(uint16_t pic) {

    return inb(pic);
}

#endif
