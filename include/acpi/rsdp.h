#ifndef _RSDP_H
#define _RSDP_H


#include <stdint.h>
#include "libc/stdio.h"


typedef struct {
    char signature[8];
    uint8_t checksum;
    char OEMString[6];
    uint8_t revision;
    uint32_t rsdt_address;

#ifdef ACPI_2
    uint32_t lenght;
    uint64_t xsdt_address;
    uint8_t extended_checksum;
    uint8_t reserved[3];
#endif
} __attribute__((packed)) rsdp_t;


inline rsdp_t *get_rsdp_struct(uint8_t *rsdp_pointer) {

    rsdp_t *rsdp = (rsdp_t *)rsdp_pointer;
    printf(rsdp->signature, (Vec3){125, 125, 125, 0});
    putchar('\n',(Vec3){125, 125, 125, 0});

    return rsdp;
}


#endif
