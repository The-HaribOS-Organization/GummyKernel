#ifndef _RSDP_H
#define _RSDP_H


#include <stdint.h>
#include "klibc/stdio.h"


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
    return rsdp;
}

inline bool checksum_field(description_header_t *tableHeader) {

    unsigned char sum = 0;

    for (uint32_t i = 0; i < tableHeader->lenght; i++)
        sum += ((char *) tableHeader)[i];

    return sum == 0;
}


#endif
