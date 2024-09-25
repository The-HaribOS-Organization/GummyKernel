#ifndef _PCI_H
#define _PCI_H


#include <stdint.h>


#define CONFIG_ADDRESS 0xCF8
#define CONFIG_DATA 0xCFC


// structure de donnée.

struct pci_t {

    uint16_t vendor_id;
    uint16_t device_id;
    uint16_t command;
    uint16_t status;
    uint8_t revision_id;
    uint8_t prog_if;
    uint8_t subclass;
    uint8_t class_code;
    uint8_t cache_line_size;
    uint8_t latency_timer;
    uint8_t header_type;
    uint8_t bist;
} __attribute__((packed));

typedef struct {

    struct pci_t header;
    uint32_t bar_0;
    uint32_t bar_1;
    uint32_t bar_2;
    uint32_t bar_3;
    uint32_t bar_4;
    uint32_t bar_5;
    uint32_t cardbus_cis;
    uint16_t subsystem_vendor_id;
    uint16_t subsystem_id;
    uint32_t expansion_rom_base_address;
    uint32_t reserved;
    uint32_t reserved1;
    uint8_t interrupt_line;
    uint8_t interrupt_pin;
    uint8_t min_grant;
    uint8_t max_latency;
} __attribute__((packed)) pci_general_device;


typedef struct {

    struct pci_t header;
    uint32_t bar_0;
    uint32_t bar_1;
    uint8_t primary_bus;
    uint8_t secondary_bus;
    uint8_t subordinate_bus;
    uint8_t secondary_latency_timer;
    uint8_t io_base;
    uint8_t io_limit;
    uint16_t secondary_status;
    uint16_t memory_base;
    uint16_t memory_limit;
    uint32_t prefetchable_base_upper;
    uint32_t prefetchable_limit_upper;
    uint16_t io_base_upper;
    uint16_t io_limit_upper;
    uint32_t reserved;
    uint32_t expansion_rom_base_address;
    uint8_t interrupt_line;
    uint8_t interrupt_pin;
    uint16_t bridge_control;
} __attribute__((packed)) pci_to_pci_bridge;


typedef struct {

    struct pci_t header;
    uint32_t cardbus_socket_base_address;
    uint8_t offset_capabilities_list;
    uint8_t reserved;
    uint16_t secondary_status;
    uint8_t pci_bus;
    uint8_t cardbus_bus;
    uint8_t subordinate_bus;
    uint8_t cardbus_latency_timer;
    uint32_t memory_base_address_0;
    uint32_t memory_limit_0;
    uint32_t memory_base_address_1;
    uint32_t memory_limit_1;
    uint32_t io_base_address_0;
    uint32_t io_limit_0;
    uint32_t io_base_address_1;
    uint32_t io_limit_1;
    uint8_t interrupt_line;
    uint8_t interrupt_pin;
    uint16_t bridge_control;
    uint16_t subsystem_device_id;
    uint16_t subsystem_vendor_id;
    uint32_t legacy_mode_base_address;
} __attribute__((packed)) pci_to_cardbus;


typedef struct {

    uintptr_t bus_address;
    uint8_t device;
    uint8_t function;
    struct pci_t infos;
} __attribute__((packed)) pci_device;


void check_bus(void);
void check_device(uintptr_t bus_address, uint8_t device);
void check_function(uintptr_t device_address, uint8_t function);
void pci_probe(void);


inline uint16_t get_vendor_id(uintptr_t device_address, uint8_t function) {

    struct pci_t *device = (struct pci_t *)(device_address | ((uintptr_t)function << 12));
    return device->vendor_id;
}

inline uint16_t get_header_type(uintptr_t device_address, uint8_t function) {

    struct pci_t *device = (struct pci_t *)(device_address | ((uintptr_t)function << 12));
    return device->header_type;
}

inline uint8_t get_class_code(uintptr_t device_address, uint8_t function) {

    struct pci_t *device = (struct pci_t *)(device_address | ((uintptr_t)function << 12));
    return device->class_code;
}

inline uint8_t get_sub_class_code(uintptr_t device_address, uint8_t function) {

    struct pci_t *device = (struct pci_t *)(device_address | ((uintptr_t)function << 12));
    return device->subclass;
}

inline int8_t get_secondary_bus(uintptr_t device_address, uint8_t function) {
    
    struct pci_t *device = (struct pci_t *)(device_address | ((uintptr_t)function << 12));
    if (device->header_type == 0x1) {

        pci_to_pci_bridge *bridge = (pci_to_pci_bridge *)(device_address | ((uintptr_t)function << 12));
        return bridge->secondary_bus;
    } else {
        return -1;
    }
}

#endif
