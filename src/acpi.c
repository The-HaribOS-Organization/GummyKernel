#include <stdint.h>
#include <stddef.h>
#include "acpi/acpi.h"
#include "acpi/rsdp.h"
#include "libc/stdio.h"
#include "pit.h"
#include "libc/string.h"
#include "acpi/fadt.h"
#include "io.h"


fadt_t *fadt_structure;


void *findDescriptor(uint32_t *rsdt, char *signature) {

    void *descriptor = NULL;

    acpi_rsdt_t *rsdt_struct = (acpi_rsdt_t *)rsdt;
    int entries = (rsdt_struct->h.lenght - sizeof(rsdt_struct->h)) / 4;

    for (int_fast32_t i = 0; i < entries; i++) {
        
        description_header_t *h = (description_header_t *)rsdt_struct->other_sdt[i];
        if (strcmp(signature, h->signature)) {
            printf("\x1b[107;255;152m[+]: Descripteur trouve: %s\n", h->signature);

            descriptor = h;
            break;
        } else {
            continue;
        }
    }

    return descriptor;
}


bool check_acpi_enable(void) {

    if (fadt_structure->smi_cmd == 0 || ((fadt_structure->acpi_disable == 0 && fadt_structure->acpi_enable == 0)) || (fadt_structure->pm1a_cnt_blk & 0x0)) return true;
    else return false;
}
