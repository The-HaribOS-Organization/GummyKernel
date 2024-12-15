#include <stdint.h>
#include <stddef.h>
#include "acpi/acpi.h"
#include "acpi/rsdp.h"
#include "klibc/string.h"
#include "acpi/fadt.h"
#include "acpi/mcfg.h"
#include "acpi/madt.h"
#include "acpi/dsdt.h"
#include "klibc/stdio.h"


fadt_t *fadt_structure;
mcfg_t *mcfg_structure;
madt_t *madt_structure;
dsdt_t *dsdt_structure;

void *findDescriptor(uint32_t *rsdt, char signature[4]) {

    acpi_rsdt_t *rsdt_struct = (acpi_rsdt_t *)rsdt;
    int entries = (rsdt_struct->h.lenght - sizeof(rsdt_struct->h)) / 4;

    for (int_fast32_t i = 0; i < entries; i++) {
        
        description_header_t *h = (description_header_t *)rsdt_struct->other_sdt[i];
        if (strncmp(h->signature, signature, 4) == 0) return (void *)h;
    }

    return NULL;
}


bool check_acpi_enable(void) {

    if (fadt_structure->smi_cmd == 0 || ((fadt_structure->acpi_disable == 0 && fadt_structure->acpi_enable == 0)) || (fadt_structure->pm1a_cnt_blk & 0x0)) return true;
    else return false;
}
