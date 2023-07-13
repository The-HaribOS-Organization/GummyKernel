/*
    File    : msr.h
    Utility : The MSR driver
 */

#ifndef KERNEL_MSR_H_INCLUDED
#define KERNEL_MSR_H_INCLUDED

#include <stdint.h>

/////////////////
//  Functions  //
/////////////////

void getMSR(uint32_t msr, uint32_t *lo, uint32_t *hi);
void setMSR(uint32_t msr, uint32_t lo, uint32_t hi);

#endif