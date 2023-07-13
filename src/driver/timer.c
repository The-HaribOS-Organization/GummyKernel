#include "driver/timer.h"

static uint32_t time = 0;

// TODO IRQ
static void pit_callback(/* registers_t *regs */)
{
    ++time;
    
    char timer[11]; // -> 2147483647 is the int32_t max
    itoa(time, timer, 10);
    
    puts("[+]: Tic Tac: ");
    puts(timer);
    puts("\n");
}

void timer_initPIT(uint8_t frequency)
{
    puts("[+]: Initialisation du PIT.\n");

    uint32_t divisor = 1193182 / frequency;
    outb(MODE_COMMAND_REGISTER, 0x36);

    outb(CHANNEL_ZERO, (uint8_t)(divisor & 0xFF));
    outb(CHANNEL_ZERO, (uint8_t)((divisor >> 8) & 0xFF));

    // TODO IRQ
    (void)pit_callback; // Unused function

    // register_interrupt_handler(0, pit_callback);

    // terminal_setcolor(VGA_GREEN);
    puts("[+]: PIT initialise.\n");
    // terminal_setcolor(VGA_WHITE);
}

void timer_wait(uint32_t delay)
{
    uint32_t eticks = time + delay;
    while (time < eticks)
    {
        __asm__ __volatile__("sti//hlt//cli");
    }
}

uint32_t timer_readPITCount()
{
    __asm__ volatile("cli");

    outb(MODE_COMMAND_REGISTER, 0b0000000);
    uint32_t count = inb(CHANNEL_ZERO);
    count |= inb(CHANNEL_ZERO) << 8;
    
    __asm__ volatile("sti");

    return count;
}

void timer_writePITCount(uint32_t value)
{
    __asm__ volatile("cli");

    outb(CHANNEL_ZERO, (value & 0xFF));
    outb(CHANNEL_ZERO, ((value >> 8) & 0xFF));

    __asm__ volatile("sti");
}
