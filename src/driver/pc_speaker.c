#include "driver/pc_speaker.h"

void make_beep(uint32_t frequency)
{
    uint8_t div = 1193182 / frequency;
    // outb(MODE_COMMAND_REGISTER, 0xB6);
    // outb(CHANNEL_DEUX, (uint8_t)(div & 0xFF));
    // outb(CHANNEL_DEUX, (uint8_t)((div >> 8) & 0xFF));

    uint8_t tmp /*= inb(PIT_IO_PORT) */;
    if (tmp != (tmp | 3))
    {
        // outb(PIT_IO_PORT, tmp | 3);
    }
}

void shutup()
{
    uint8_t tmp /*= inb(PIT_IO_PORT) & 0xFC */;
    // outb(PIT_IO_PORT, tmp);
}