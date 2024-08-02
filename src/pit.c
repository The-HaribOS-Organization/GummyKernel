#include <stdint.h>
#include <stdbool.h>
#include "pit.h"
#include "interrupt/isr.h"
#include "interrupt/irq_handler.h"
#include "io.h"
#include "libc/stdio.h"


volatile uint_fast32_t pit_count = 0;

void init_timer(uint32_t freq) {

    uint32_t divisor = PIT_INPUT_CLOCK / freq;
    outb((uint16_t)COMMAND_REGISTER, 0x36);
    outb((uint16_t)CHANNEL_0_DATA_PORT, (uint8_t)(divisor & 0xFF));
    outb((uint16_t)CHANNEL_0_DATA_PORT, (uint8_t)(divisor >> 8));

    pic_clear_mask(0);

    // L'utilisation de la fonction ci-dessous est à revoir plus tard.
    // set_irq_routine(0, pit_handler);
}

void pit_handler(isr_frame *frame) {

    pit_count++;
    irq_stack_state = frame;
}

void set_pit_count(uint32_t count) {

    __asm__ volatile("cli");
    outb(0x40, (count & 0xFF));
    outb(0x40, ((count & 0xFF00) >> 8));
    
    __asm__ volatile("sti");
}

void sleep(uint_fast32_t millis) {

    uint_fast32_t current_count = pit_count + millis;
    while (pit_count < current_count);
}

bool check_channel(uint8_t channel) {

    return ((channel & 0x0E) == (inb(COMMAND_REGISTER) & 0x0E)) ? true : false;
}

uint_fast32_t get_pit_count(void) {

    __asm__ volatile("cli");
    outb(COMMAND_REGISTER, 0x00);
    __asm__ volatile("sti");

    return inb(CHANNEL_0_DATA_PORT) | (inb(CHANNEL_0_DATA_PORT) << 8);
}
