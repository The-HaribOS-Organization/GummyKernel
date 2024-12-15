#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "io.h"
#include "comm/pci.h"
#include "klibc/stdio.h"
#include "acpi/mcfg.h"


static uint16_t device_number = 0;
static pci_device pci_devices[256];

static const char *class_codes[] = {
    "Unclassified", "Mass Storage Controller", "Network Controller", "Display Controller",
    "Multimedia Controller", "Memory Controller", "Bridge", "Simple Communication Controller",
    "Base System Peripheral", "Input Device Controller", "Docking Station", "Processor",
    "Serial Bus Controller", "Wireless Controller", "Intelligent Controller", "Satellite Communication Controller",
    "Encryption Controller", "Signal Processing Controller", "Processing Accelerator", "Non-Essential Instrumentation",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "Co-Processor",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "Unassigned Class"};


static const char *sub_class_code[20][70] = {
    {"Non-VGA Compatible Unclassified Device", "VGA Compatible Unclassified Device"},
    {"SCSI Bus Controller", "IDE Controller", "Floppy Disk Controller", "IPI Bus Controller",
    "RAID Controller", "ATA Controller", "Serial ATA Controller", "Serial Attached SCSI Controller",
    "Non-Volatile Memory Controller"},
    {"Ethernet Controller", "Token Ring Controller", "FDDI Controller", "ATM Controller",
    "ISDN Controller", "WorldFip Controller", "PICMG 2.14 Multi Computing Controller",
    "Infiniband Controller", "Fabric Controller"},
    {"VGA Compatible", "XGA Controller", "3D Controller (Not VGA-Compatible)"},
    {"Multimedia Video Controller", "Multimedia Audio Controller", "Computer Telephony Device",
    "Audio Device"},
    {"RAM Controller", "Flash Controller"},
    {"Host Bridge", "ISA Bridge", "EISA Bridge", "MCA Bridge", "PCI-to-PCI Bridge", "PCMCIA Bridge",
    "NuBus Bridge", "CardBus Bridge", "RACEway Bridge", "PCI-to-PCI Bridge", "InfiniBand-to-PCI Host Bridge"},
    {"Serial Controller", "Parallel Controller", "Multiport Serial Controller", "Modem",
    "IEEE 488.1/2 (GPIB) Controller", "Smart Card Controller"},
    {"PIC", "DMA Controller", "Timer", "RTC Controller", "PCI Hot-Plug Controller", "SD Host Controller",
    "IOMMU"},
    {"Keyboard Controller", "Digitizer Pen", "Mouse Controller", "Scanner Controller", "Gameport Controller"},
    {"Generic"},
    {"386", "486", "Pentium", "Pentium Pro", "", "", "", "", "", "", "", "", "", "", "", "" , "", "Alpha", "",
    "", "", "", "", "", "", "", "", "", "", "" , "", "", "", "", "PowerPC", "", "", "", "", "", "", "", "", "",
    "", "", "" , "", "", "", "", "MIPS", "", "", "", "", "", "", "", "", "", "", "", "" , "", "", "", "", "Co-Processor"},
    {"FireWire (IEEE 1394) Controller", "ACCESS Bus Controller", "SSA", "USB Controller", "Fibre Channel",
    "SMBus Controller", "InfiniBand Controller", "IPMI Interface", "SERCOS Interface", "CANbus Controller"},
    {"iRDA Compatible Controller", "Consumer IR Controller", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "RF Controller", "Bluethoot Controller", "Broadband Controller", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "Ethernet Controller (802.1a)", "Ethernet Controller (802.1b)"},
    {"I20"},
    {"Satellite TV Controller", "Satellite Audio Controller", "Satellite Voice Controller", "Satellite Data Controller"},
    {"Network and Computing Encryption/Decryption", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "Entertainment Encryption/Decryption"},
    {"DPIO Modules", "Performance Counters", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "Communication Synchronizer", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "Signal Processing Management"}
};


void check_bus(void) {

    uint16_t entries = (mcfg_structure->h.lenght - (sizeof(mcfg_structure->h) + sizeof(mcfg_structure->reserved)) / sizeof(struct config_space));

    for (uint16_t i = 0; i < entries; i++) {

        struct config_space *space = (struct config_space *)&mcfg_structure->config[i];
        for (uint16_t bus = space->start_pci_bus; bus < space->end_pci_bus; bus++) {

            uintptr_t bus_address = space->base_address | ((uintptr_t)bus << 20);

            //if (pci_device->vendor_id == 0xFFFF && pci_device->vendor_id == 0x0) return;

            for (uint8_t device = 0; device < 32; device++) check_device(bus_address, device);
        }
    }
}

void check_device(uintptr_t bus_address, uint8_t device) {

    uint8_t function = 0;
    struct pci_t *address_device;

    if ((get_vendor_id((bus_address | ((uintptr_t)device << 15)), function) == 0xFFFF) && (get_vendor_id((bus_address | ((uintptr_t)device << 15)), function) == 0x0)) return;

    check_function((bus_address | ((uintptr_t)device << 15)), function);
    if ((get_header_type((bus_address | ((uintptr_t)device << 15)), function) & 0x80) != 0) {

        for (function = 0; function < 8; function++) {

            if ((get_vendor_id((bus_address | ((uintptr_t)device << 15)), function) != 0xFFFF) && (get_vendor_id((bus_address | ((uintptr_t)device << 15)), function) != 0x0)) {
                
                address_device = (struct pci_t *)(bus_address | ((uintptr_t)device << 15 | (function << 12)));
                pci_devices[device_number].bus_address = bus_address;
                pci_devices[device_number].device = device;
                pci_devices[device_number].function = function;
                pci_devices[device_number].infos = *(struct pci_t *)address_device;
                device_number++;

                check_function((bus_address | ((uintptr_t)device << 15)), function);
            }
        }
    }

}

void check_function(uintptr_t device_address, uint8_t function) {

    if ((get_class_code(device_address, function) == 0x6) && (get_sub_class_code(device_address, function) == 0x4)) printf("[+]: PCI-to-PCI Bridge.\n"); // check_bus(get_secondary_bus(device_address, function));
}

void pci_probe(void) {

    check_bus();

    for (uint16_t i = 0; i < device_number; i++) {

        printf("[+]------->: Device class: %s\n", class_codes[pci_devices[i].infos.class_code]);
        printf("[+]------->: Device subclass: %s\n", sub_class_code[pci_devices[i].infos.class_code][pci_devices[i].infos.subclass]);
        printf("[+]------->: Device vendor ID: %d\n", pci_devices[i].infos.vendor_id);
        printf("[+]------->: Device bus address: 0x%x\n", pci_devices[i].bus_address);
    }
}