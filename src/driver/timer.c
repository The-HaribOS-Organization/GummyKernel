#include <timer/pit.h>
#include <stdint.h>
#include <idt/irq/irq.h>
#include <libs/stdio.h>
#include <io/pic.h>
#include <io/cursor.h>
#include <video/vga_text.h>


char *timer;
uint32_t time = 0;

static void pit_callback(registers_t *regs) {
    
    time++;
    itoa(time, timer, 10);
    printf("[+]: Tic Tac: ");
    printf(timer);
    printf("\n");
}

void init_pit(uint8_t frequency) {

    printf("[+]: Initialisation du PIT.\n");

    uint32_t divisor = 1193182 / frequency;
    outb(MODE_COMMAND_REGISTER, 0x36);

    outb(CHANNEL_ZERO, (uint8_t)(divisor & 0xFF));
    outb(CHANNEL_ZERO, (uint8_t)((divisor >> 8) & 0xFF));
    register_interrupt_handler(0, pit_callback);
    
    terminal_setcolor(VGA_GREEN);
    printf("[+]: PIT initialise.\n");
    terminal_setcolor(VGA_WHITE);
}

void timer_wait(uint32_t delay) {
    
    uint32_t eticks;
 
    eticks = time + delay;
    while(time < eticks) {
        __asm__ __volatile__ ("sti//hlt//cli");
    }
}

uint32_t read_pit_count() {

    asm volatile("cli");

    outb(MODE_COMMAND_REGISTER, 0b0000000);
    uint32_t count = inb(CHANNEL_ZERO);
    count |= inb(CHANNEL_ZERO) << 8;
    asm volatile("sti");

    return count;
}

void write_pit_count(uint32_t value) {

    asm volatile("cli");

    outb(CHANNEL_ZERO, (value & 0xFF));
    outb(CHANNEL_ZERO, ((value >> 8) & 0xFF));
    asm volatile("sti");
}
