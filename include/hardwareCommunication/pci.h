/* ce fichier contient tous les prototypes de fonction
ainsi que les macros nécessaire à l'utilisation du PCI*/

#ifndef _PCI_
#define _PCI_

#include <stdint.h>

#define CONFIG_ADDRESS 0xCF8
#define CONFIG_DATA 0xCFC


/* Structure pour les appareils PCI permettant de récupérer la marque ainsi que
le nom de l'appareil. Par ailleurs, nous pouvons obtenir le type d'appareil
(carte réseau, carte son, carte graphique, ssd nvme)*/

typedef struct PCI_Device_Struct PCI_Device_Struct_t;
struct PCI_Device_Struct {
    uint16_t vendor_id;
    uint16_t device_id;
    uint16_t command;
    uint16_t status;
    uint8_t revision_id;
    uint8_t prog_if;
    uint8_t sub_class;
    uint8_t base_class;
    uint8_t cache_line_size;
    uint8_t latency_timer;
    uint8_t header_type;
    uint8_t bist;

    union {
        struct PCI_Header_Type_0 {
            uint32_t bar0, bar1, bar2, bar3, bar4, bar5;
            uint32_t cardbus_cis_pointer;
            uint32_t subsystem_vendor_id;
            uint32_t expansion_rom_base_address;
            uint32_t capabilities_pointer;
            uint32_t reserved;
            uint8_t max_latency, min_grant, interrupt_pin, interrupt_line;
        } type0;

        struct PCI_Header_Type_1 {
            uint32_t bar0, bar1;
            uint8_t secondary_latency_timer, subordinate_bus_number, secondary_bus_number, primary_bus_number;
            uint16_t secondary_status;
            uint8_t IO_limit, IO_base;
            uint16_t memory_limit, memory_base;
            uint16_t prefetchable_memory_limit, prefetchable_memory_base;
            uint32_t prefetchable_base_upper_32_bits;
            uint32_t prefetchable_limit_upper_32_bits;
            uint32_t capability_pointer;
            uint32_t expansion_rom_base_address;
            uint16_t bridge_controller;
            uint8_t interrupt_pin, interrupt_line;
        } type1;

        struct PCI_Header_Type_2 {
            uint32_t cardbus_socket;
            uint16_t secondary_status;
            uint8_t reserved, offset_capabilites_list;
            uint8_t cardbus_latency_timer, subordinate_bus_number, cardbus_bus_number, pci_bus_number;
            uint32_t memory_base_address_0, memory_limit_0, memory_base_address_1, memory_limit_1;
            uint32_t IO_base_address_0, IO_limit_0, IO_base_address_1, IO_limit_1;
            uint16_t birdge_control;
            uint8_t interrupt_pin, interrupt_line;
            uint16_t subsystem_vendor_id, subsystem_device_id;
            uint32_t pc_card_legacy_mode_base_address;
        } type2;
    } u;
};

void initPCI();
void detect_pci();
void checkBus(uint16_t bus);
void checkDevice(uint16_t bus, uint16_t device);
void checkFunction(uint16_t bus, uint16_t device, uint16_t function);
void add_pci_device(PCI_Device_Struct_t pci_struct);
bool deviceHasMultipleFunctions(uint8_t header_type);
const char *getPCIClassDevice(uint16_t bus, uint16_t device, uint16_t function);
const char *getPCISubClassDevice(uint16_t bus, uint16_t device, uint16_t function);
uint8_t get_secondary_bus_number(uint16_t bus, uint16_t device, uint16_t function);
uint8_t getPCIHeaderType(uint16_t bus, uint16_t device, uint16_t function);
uint8_t getClass(uint16_t bus, uint16_t device, uint16_t function);
uint8_t getSubClass(uint16_t bus, uint16_t device, uint16_t function);
uint16_t pciGetVendorID(uint16_t bus, uint16_t device, uint16_t function);
uint16_t pciGetDeviceID(uint16_t bus, uint16_t device, uint16_t function);
PCI_Device_Struct_t dumpPCIInfos(uint16_t bus, uint16_t device, uint16_t vendor, uint16_t function);

#endif
