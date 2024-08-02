#ifndef _PIT_
#define _PIT_


#include <stdint.h>
#include <stdbool.h>
#include "io.h"
#include "interrupt/irq_handler.h"
#include "interrupt/isr.h"


#define CHANNEL_0_DATA_PORT 0x40
#define CHANNEL_1_DATA_PORT 0x41
#define CHANNEL_2_DATA_PORT 0x42
#define COMMAND_REGISTER 0x43

#define PIT_INPUT_CLOCK 1193182


void init_timer(uint32_t freq);
void pit_handler(isr_frame *frame);
void set_pit_count(uint32_t count);
void sleep(uint_fast32_t millis);

bool check_channel(uint8_t channel);

uint_fast32_t get_pit_count(void);

#endif
