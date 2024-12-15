#ifndef _DSDT_H
#define _DSDT_H


#include <stdint.h>
#include "acpi/acpi.h"


typedef struct {

    description_header_t h;
    char *aml_code;
} __attribute__((packed)) dsdt_t;

extern dsdt_t *dsdt_structure;

#endif
