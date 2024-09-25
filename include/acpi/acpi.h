#ifndef _ACPI_H
#define _ACPI_H

#define RSDT_

#include <stdint.h>
#include <stdbool.h>


typedef struct {

    char signature[4];
    uint32_t lenght;
    uint8_t revision;
    uint8_t checksum;
    char OEMID[6];
    char OEM_table_ID[8];
    uint32_t OEM_revision;
    uint32_t creator_ID;
    uint32_t creator_revision;
} __attribute__((packed)) description_header_t;


typedef struct {
    description_header_t h;
#ifdef RSDT_
    uint32_t other_sdt[4096];
#elif defined(XSDT_T)
    uint64_t other_sdt[8192];
#endif
} __attribute__((packed)) acpi_rsdt_t;

void *findDescriptor(uint32_t *rsdt, char signature[4]);
bool check_acpi_enable(void);

#endif
