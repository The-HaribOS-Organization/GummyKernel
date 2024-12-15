#include "mouse.h"
#include "comm/ps2.h"
#include "interrupt/irq_handler.h"
#include "interrupt/8259PIC.h"
#include "interrupt/isr.h"
#include "klibc/stdio.h"
#include <stdint.h>



void init_mouse(void) {

    disable_ps2_port();

    outb(COMMAND_REGISTER_KBOARD, 0xA8);
    outb(COMMAND_REGISTER_KBOARD, 0x20);
    uint8_t status_byte = inb(0x60) | 2;

    outb(COMMAND_REGISTER_KBOARD, 0x60);
    outb(DATA_PORT, status_byte);

    outb(COMMAND_REGISTER_KBOARD, 0xD4);
    outb(DATA_PORT, 0xF4);
    pic_clear_mask(12);

    disable_ps2_port();
    printf("Souris initialise.\n");
}


void mouse_handler(isr_frame *frame) {

    irq_stack_state = frame;
    printf("Souris bouge.\n");
}