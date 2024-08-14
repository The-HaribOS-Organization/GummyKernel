#include <stdint.h>
#include "acpi/acpi.h"
#include "acpi/rsdp.h"
#include "libc/stdio.h"
#include "pit.h"
#include "libc/string.h"


void find_FADT(uint8_t *rsdp_pointer) {

    acpi_rsdt_t *rsdt = (acpi_rsdt_t *)rsdp_pointer;
    uint32_t entry = (rsdt->h.lenght - sizeof(acpi_rsdt_t)) / 4;

    for (uint32_t i = 0; i < entry; i++) {

        description_header_t *h = (description_header_t *)rsdt->entries[i];
        if (!strcmp("FACP", h->signature)) printf("\x1b[87;255;127mFADT trouve.\n");
    }
}