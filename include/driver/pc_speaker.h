/*
    File    : pc_speaker.h
    Utility : The speaker driver
 */

#ifndef KERNEL_PC_SPEAKER_H_INCLUDED
#define KERNEL_PC_SPEAKER_H_INCLUDED

#include <stdint.h>

#include "driver/timer.h"

/////////////////
//  Functions  //
/////////////////

void pcBeeper_makeBeep(uint32_t frequency);
void pcBeeper_shutup();

#endif // KERNEL_PC_SPEAKER_H_INCLUDED