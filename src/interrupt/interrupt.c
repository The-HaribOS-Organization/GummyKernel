#include <stdint.h>
#include "interrupt/interrupt.h"
#include "interrupt/isr.h"
#include "interrupt/irq_handler.h"
#include "interrupt/8259PIC.h"
#include "gfx/utils.h"
#include "libc/stdio.h"


__attribute__((aligned(0x10)))
static idt_descriptor_t idt_routine[256]; 
static idtr_t idt;

// Initialisation de l'IDT, l'adresse du premier élément
// du tableau idtr représente l'adresse de base où trouver chaque ISR.
// et l'offset représente la limite du nombre d'élément.
void initIDT(void) {

    __asm__ volatile("cli");
    idt.offset = (uintptr_t)&idt_routine[0];
    idt.size = sizeof(idt_descriptor_t) * 256 - 1;

    for (uint8_t i = 0; i < 32; i++)
        setIDTDescriptor(i, isr_array[i], INTERRUPT_GATE);

    initPIC();
    printf("\x1b[241;202;255m[+]: PIC initialise\n");
    // for (uint8_t i = 32; i < 48; i++)
    setIDTDescriptor(32, irq_0, INTERRUPT_GATE);
    setIDTDescriptor(33, irq_1, INTERRUPT_GATE); // , irq_array[i-32], INTERRUPT_GATE);

#ifdef USE_ASSEMBLY_ROUTINE_
    setIDT((uint32_t)&idt);
#endif

#ifdef USE_INLINE_ASSEMBLY_
    __asm__ volatile("lidt %0" : : "m"(idt));
#endif
    
    __asm__ volatile("sti");
}

void setIDTDescriptor(uint8_t vector, void *isr, uint8_t flag) {

    idt_descriptor_t *descriptor = &idt_routine[vector];
    descriptor->offset_low = ((uint32_t)isr & 0xFFFF);
    descriptor->segment_selector = 0x08;
    descriptor->gate_type = flag;
    descriptor->reserved = 0;
    descriptor->offset_high = (((uint32_t)isr >> 16) & 0xFFFF);
}
