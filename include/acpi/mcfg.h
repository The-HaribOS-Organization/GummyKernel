#ifndef _MCFG_H
#define _MCFG_H


#include <stdint.h>
#include "acpi/acpi.h"


struct config_space {
    uint64_t base_address;
    uint16_t pci_segment_group;
    uint8_t start_pci_bus;
    uint8_t end_pci_bus;
    uint32_t reserved;
};

typedef struct {

    description_header_t h;
    uint64_t reserved;
    struct config_space config[2048];    
} mcfg_t;

extern mcfg_t *mcfg_structure;

#endif
