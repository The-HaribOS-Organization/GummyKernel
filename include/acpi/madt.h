#ifndef _MADT_H
#define _MADT_H


#include <stdint.h>
#include "acpi/acpi.h"


#define PCAT_COMPAT 0x00000001

#define PROCESSOR_LAPIC 0x0
#define IO_APIC 0x1
#define INT_SOURCE_OVERRIDE 0x2
#define NMI_SOURCE 0x3
#define LAPIC_NMI 0x4
#define LAPIC_ADDRESS_OVERRIDE 0x5
#define IO_SAPIC 0x6
#define L_SAPIC 0x7
#define PLATFORM_INT_SOURCE 0x8
#define PROCESSOR_LOCAL_x2APIC 0x9
#define LOCAL_x2APIC_NMI 0xA


typedef struct {

    description_header_t h;
    uint32_t local_interrupt_physical_address;
    uint32_t flags;
    uint8_t interrupt_controller_structure[];
} __attribute__((packed)) madt_t;

extern madt_t *madt_structure;

#endif
