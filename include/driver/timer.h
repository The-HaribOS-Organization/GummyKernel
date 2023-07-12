/* Contient tous les prototypes de fonctions permettant
d'initialiser le PIT.*/

#ifndef KERNEL_PIT_H_INCLUDED
#define KERNEL_PIT_H_INCLUDED

// #include <stdio.h>
#include <stdint.h>
#include "apic/pic.h"

/////////////////////////
//  Constants & types  //
/////////////////////////

#define MODE_COMMAND_REGISTER 0x43
#define CHANNEL_ZERO 0x40
#define CHANNEL_ONE 0x41
#define CHANNEL_TWO 0x42
#define PIT_IO_PORT 0x61

/////////////////
//  Functions  //
/////////////////

void timer_initPIT(uint8_t frequency);
void timer_shutup();

void timer_wait(uint32_t delay);
void timer_makeBeep(uint32_t frequency);

uint32_t timer_readPITCount();
void timer_writePITCount(uint32_t value);

#endif // KERNEL_PIT_H_INCLUDED
