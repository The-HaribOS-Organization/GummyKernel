#ifndef _INTERRUPT_
#define _INTERRUPT_
#define USE_ASSEMBLY_ROUTINE_


#define INTERRUPT_GATE 0x8E
#define TRAP_GATE 0x8F
#define TASK_GATE 0x85


#include <stdint.h>


typedef struct {

    uint16_t size;
    uint32_t offset;
} __attribute__((packed)) idtr_t;

typedef struct {

    uint16_t offset_low;
    uint16_t segment_selector;
    uint8_t reserved;
    uint8_t gate_type;
    uint16_t offset_high;
} __attribute__((packed)) idt_descriptor_t;


void initIDT(void);
void setIDTDescriptor(uint8_t vector, void *isr, uint8_t flag);

extern void setIDT(uint32_t);

#endif
