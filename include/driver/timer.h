/* Contient tous les prototypes de fonctions permettant
d'initialiser le PIT.*/

#ifndef _PIT_
#define _PIT_

#include <stdint.h>
#include <idt/irq/irq.h>

#define MODE_COMMAND_REGISTER 0x43
#define CHANNEL_ZERO 0x40
#define CHANNEL_UN 0x41
#define CHANNEL_DEUX 0x42
#define PIT_IO_PORT 0x61

void init_pit(uint8_t frequency);
void timer_wait(uint32_t delay);
void make_beep(uint32_t frequency);
void shutup();
uint32_t read_pit_count();
void write_pit_count(uint32_t value);

#endif
