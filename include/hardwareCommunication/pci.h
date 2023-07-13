/*
    File    : pci.h
    Utility : The PCI driver
 */

#ifndef KERNEL_PCI_H_INCLUDED
#define KERNEL_PCI_H_INCLUDED

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "driver/serial_port.h"
#include "hardwareCommunication/io.h"

/////////////////////////
//  Constants & types  //
/////////////////////////

#define CONFIG_ADDRESS 0xCF8
#define CONFIG_DATA 0xCFC

/* Structure pour les appareils PCI permettant de récupérer la marque ainsi que
le nom de l'appareil. Par ailleurs, nous pouvons obtenir le type d'appareil
(carte réseau, carte son, carte graphique, ssd nvme)*/

typedef struct {
    uint16_t vendorID;
    uint16_t deviceID;
    uint16_t command;
    uint16_t status;
    uint8_t revisionID;
    uint8_t progIF;
    uint8_t subClass;
    uint8_t baseClass;
    uint8_t cacheLineSize;
    uint8_t latencyTimer;
    uint8_t headerType;
    uint8_t bist;

    union {
        struct PCIHeaderType0 {
            uint32_t bar0, bar1, bar2, bar3, bar4, bar5;
            uint32_t cardbusCisPointer;
            uint32_t subsystemVendorID;
            uint32_t expansionRomBaseAddress;
            uint32_t capabilitiesPointer;
            uint32_t reserved;
            uint8_t maxLatency, minGrant, interruptPin, interruptLine;
        } type0;

        struct PCI_Header_Type_1 {
            uint32_t bar0, bar1;
            uint8_t secondary_latency_timer, subordinate_bus_number, secondary_bus_number, primary_bus_number;
            uint16_t secondary_status;
            uint8_t IO_limit, IO_base;
            uint16_t memoryLimit, memoryBase;
            uint16_t prefetchableMemoryLimit, prefetchableMemoryBase;
            uint32_t prefetchableBaseUpper32Bits;
            uint32_t prefetchableLimitUpper32Bits;
            uint32_t capabilityPointer;
            uint32_t expansionRomBaseAddress;
            uint16_t bridgeController;
            uint8_t interruptPin, interruptLine;
        } type1;

        struct PCI_Header_Type_2 {
            uint32_t cardbusSocket;
            uint16_t secondaryStatus;
            uint8_t reserved, offsetCapabilitesList;
            uint8_t cardbusLatencyTimer, subordinateBusNumber, cardbusBusNumber, pciBusNumber;
            uint32_t memoryBaseAddress0, memoryLimit0, memoryBaseAddress1, memoryLimit1;
            uint32_t IOBaseAddress0, IOLimit0, IOBaseAddress1, IOLimit1;
            uint16_t birdgeControl;
            uint8_t interruptPin, interruptLine;
            uint16_t subsystemVendorID, subsystemDeviceID;
            uint32_t pcCardLegacyModeBaseAddress;
        } type2;
    } u;
} PCIDeviceStruct;

/////////////////
//  Functions  //
/////////////////

void PCI_init();
void PCI_detect();

void PCI_checkBus(uint16_t bus);
void PCI_checkDevice(uint16_t bus, uint16_t device);
void PCI_checkFunction(uint16_t bus, uint16_t device, uint16_t function);

void PCI_addDevice(PCIDeviceStruct pciStruct);
bool PCI_deviceHasMultipleFunctions(uint8_t header_type);

const char *PCI_getClassDevice(uint16_t bus, uint16_t device, uint16_t function);
const char *PCI_getSubClassDevice(uint16_t bus, uint16_t device, uint16_t function);
uint8_t PCI_getSecondaryBusNumber(uint16_t bus, uint16_t device, uint16_t function);
uint8_t PCI_getHeaderType(uint16_t bus, uint16_t device, uint16_t function);
uint8_t PCI_getClass(uint16_t bus, uint16_t device, uint16_t function);
uint8_t PCI_getSubClass(uint16_t bus, uint16_t device, uint16_t function);
uint16_t PCI_pciGetVendorID(uint16_t bus, uint16_t device, uint16_t function);
uint16_t PCI_pciGetDeviceID(uint16_t bus, uint16_t device, uint16_t function);

PCIDeviceStruct PCI_dumpPCIInfos(uint16_t bus, uint16_t device, uint16_t vendor, uint16_t function);

#endif // KERNEL_PCI_H_INCLUDED
