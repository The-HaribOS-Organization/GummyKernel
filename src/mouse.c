#include <stdint.h>
#include <stdbool.h>
#include "mouse.h"
#include "comm/ps2.h"
#include "comm/serial.h"
#include "interrupt/irq_handler.h"
#include "interrupt/8259PIC.h"
#include "interrupt/isr.h"
#include "klibc/stdio.h"
#include "pit.h"
#include "gfx/framebuffer.h"


uint8_t mouse_cycle = 0;
uint8_t packet[3] = {0};
mouse_position_t mouse_pos = {0, 0};

void init_mouse(void) {

    // Activate the second PS/2 port.
    outb(COMMAND_REGISTER_PS2, ENABLE_SECOND_PS2);

    outb(COMMAND_REGISTER_PS2, READ_INTERNAL_RAM_0);
    sleep(10);
    uint8_t status = inb(DATA_PORT_PS2) | 2;
    outb(COMMAND_REGISTER_PS2, WRITE_INTERNAL_RAM_0);
    sleep(10);
    outb(DATA_PORT_PS2, status);

    // Set sample rate
    outb(COMMAND_REGISTER_PS2, 0xD4);
    outb(DATA_PORT, SET_SAMPLE_RATE);
    while (!(inb(COMMAND_REGISTER_PS2) & 0x1)) sleep(10);

    outb(COMMAND_REGISTER_PS2, 0xD4);
    outb(DATA_PORT, 200);
    while (!(inb(COMMAND_REGISTER_PS2) & 0x1)) sleep(10);
    
    // Set default settings
    /*outb(COMMAND_REGISTER_PS2, 0xD4);
    outb(DATA_PORT_PS2, 0xF6);
    while (!(inb(COMMAND_REGISTER_PS2) & 0x1)) sleep(10);*/

    // Enabling packet streaming
    outb(COMMAND_REGISTER_PS2, 0xD4);
    outb(DATA_PORT, ENABLE_PACKET_STREAMING);
    while (!(inb(COMMAND_REGISTER_PS2) & 0x1)) sleep(10);
    
    if (inb(DATA_PORT)) send_string(SERIAL_COM1, "[+]: Flux de donnee active.\n");

    pic_clear_mask(2);
    pic_clear_mask(12);
}


void mouse_handler(isr_frame *frame) {

    irq_stack_state = frame;

    uint8_t byte = inb(DATA_PORT_PS2);
    packet[mouse_cycle++] = byte;
    
    if (mouse_cycle == 3) {

        mouse_pos.mouse_x += packet[1] - ((packet[0] << 4) & 0x100);
        mouse_pos.mouse_y += packet[2] - ((packet[0] << 3) & 0x100);

        if (mouse_pos.mouse_x == WIDTH + 10) mouse_pos.mouse_x = 0;
        else if (-mouse_pos.mouse_y == HEIGHT + 10) mouse_pos.mouse_y = 0;
        mouse_cycle = 0;

        //drawPoint((Vec2){mouse_pos.mouse_x, mouse_pos.mouse_y}, (Vec3){255, 255, 0, 0});
    }
}
