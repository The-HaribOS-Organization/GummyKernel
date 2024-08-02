#ifndef _ISR_
#define _ISR_


#include <stdint.h>


typedef struct {
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t interrupt, error;
} __attribute__((packed)) isr_frame;


__attribute__ ((noreturn))
void isr_handler(isr_frame *frame);

extern void *isr_array[];

#endif
