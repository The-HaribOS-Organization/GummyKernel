#include <stdint.h>
#include "interrupt/irq_handler.h"
#include "interrupt/8259PIC.h"
#include "interrupt/isr.h"
#include "libc/stdio.h"


// Cette fonction ne marche pas à la place on pass directement par les routines en assembleur.
// L'appel des routines pour chaque IRQ ne fonctionne pas en passant par le C.
// En attendant de régler le problème, nous passerons par l'assembleur.

volatile isr_frame *irq_stack_state;

/* void irq_handler(isr_frame *frame) {

    
    printf("IRQ declenche: ", (Vec3){255, 125, 50, 0});
    printf(itoa(frame->interrupt, 10), (Vec3){255, 125, 50, 0});
    putchar('\n', (Vec3){255, 125, 50, 0});

    void (*handler)(isr_frame *frame);
    handler = irq_routines[frame->interrupt - 32];

    handler(frame);

    pic_send_eoi(frame->interrupt - 32);
}*/
