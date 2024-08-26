#include <stdint.h>
#include "io.h"
#include "pc_speaker.h"
#include "pit.h"


void make_beep(uint_fast32_t frequency) {

    uint_fast32_t divisor = PIT_INPUT_CLOCK / frequency;
    outb(COMMAND_REGISTER, 0xB6);
    outb(CHANNEL_2_DATA_PORT, (uint8_t)divisor);
    outb(CHANNEL_2_DATA_PORT, (uint8_t)(divisor >> 8));

    uint8_t tmp = inb(0x61);
    (tmp != (tmp | 3)) ? outb(0x61, tmp | 3) : outb(0x61, tmp);

}

void shutup(void) {

    uint8_t tmp = inb(0x61) & 0xFC;
    outb(0x61, tmp);
}
