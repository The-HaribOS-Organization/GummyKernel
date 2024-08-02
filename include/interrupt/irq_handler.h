#ifndef _IRQ_HANDLER_
#define _IRQ_HANDLER_


#include <stdint.h>
#include "interrupt/8259PIC.h"
#include "interrupt/isr.h"



// L'appel des routines pour chaque IRQ ne fonctionne pas en passant par le C.
// En attendant de régler le problème, nous passerons par l'assembleur.

/* void *irq_routines[16] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0};


__attribute__ ((noreturn))
void irq_handler(isr_frame *frame);

inline void set_irq_routine(uint8_t number, void (*handler)(isr_frame *frame)) {

    irq_routines[number] = handler;
}*/

extern volatile isr_frame *irq_stack_state;

extern void irq_0(void);
extern void irq_1(void);

#endif
