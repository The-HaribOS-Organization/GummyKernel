#include <stdint.h>
#include <sound/pc_speaker.h>
#include <timer/pit.h>
#include <io/cursor.h>

void make_beep(uint32_t frequency) {

    uint32_t div;
    uint8_t tmp;

    div = 1193182 / frequency;
    outb(MODE_COMMAND_REGISTER, 0xB6);
    outb(CHANNEL_DEUX, (uint8_t)(div & 0xFF));
    outb(CHANNEL_DEUX, (uint8_t)((div >> 8) & 0xFF));

    tmp = inb(PIT_IO_PORT);
    if (tmp != (tmp | 3)) {
        outb(PIT_IO_PORT, tmp | 3);
    }
}

void shutup() {

    uint8_t tmp = inb(PIT_IO_PORT) & 0xFC;
    outb(PIT_IO_PORT, tmp);
}