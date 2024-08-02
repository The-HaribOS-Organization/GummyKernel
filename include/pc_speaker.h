#ifndef _PC_SPEAKER_H
#define _PC_SPEAKER_H

#include <stdint.h>
#include "io.h"


void make_beep(uint_fast32_t frequency);
void shutup(void);


#endif
