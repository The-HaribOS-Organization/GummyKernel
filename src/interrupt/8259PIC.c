#include <stdint.h>
#include "io.h"
#include "interrupt/8259PIC.h"


void initPIC(void) {

    remapPIC(0x20, 0x28);
}

void remapPIC(uint8_t first_offset, uint8_t second_offset) {

    uint8_t first_mask = inb(MASTER_PIC_DATA), second_mask = inb(SLAVE_PIC_DATA);
// Initialisation de la séquence.
    outb(MASTER_PIC_COMMAND, PIC_INIT_SEQUENCE);
    outb(SLAVE_PIC_COMMAND, PIC_INIT_SEQUENCE);

// Spécification de l'offset pour le maître et l'esclave.
    outb(MASTER_PIC_DATA, first_offset);
    outb(SLAVE_PIC_DATA, second_offset);

// Spécification au maître qu'un PIC esclave se retrouve  sur l'IRQ 2
    outb(MASTER_PIC_DATA, 4);
    outb(SLAVE_PIC_DATA, 2);

    outb(MASTER_PIC_DATA, ICW_8086);
    outb(SLAVE_PIC_DATA, ICW_8086);

    outb(MASTER_PIC_DATA, first_mask);
    outb(SLAVE_PIC_DATA, second_mask);
}


// L'utilisation de cette fonction est à revoir.
void pic_send_eoi(uint8_t irq) {

    if (irq >= 8) outb(SLAVE_PIC_COMMAND, PIC_EOI);
    outb(MASTER_PIC_COMMAND, PIC_EOI);
}

void pic_set_mask(uint8_t irq) {

    uint16_t port;
    uint8_t value;

    if (irq < 8) {
        port = MASTER_PIC_DATA;
    } else {
        port = SLAVE_PIC_DATA;
        irq -= 8;
    }

    value = inb(port) | (1 << irq);
    outb(port, value);
}

void pic_clear_mask(uint8_t irq) {

    uint16_t port;
    uint8_t value;

    if (irq < 8) {
        port = MASTER_PIC_DATA;
    } else {
        port = SLAVE_PIC_DATA;
        irq -= 8;
    }

    value = inb(port) & ~(1 << irq);
    outb(port, value);
}
