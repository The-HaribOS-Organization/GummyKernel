#include "hardwareCommunication/pci.h"

static uint32_t indexDevice = 0;
static PCIDeviceStruct pciDevices[256];

static const char *pciVendors[] =
{
    "", "SafeNet", "", "", "Allied Telesis, Inc", "Loongson Technology LLC",
    "Fn-Link Technology Limited", "", "PEAK-System Technik GmbH", "", "Lockheed Martin-Marietta Corp",
    "", "", "Tiger Jet Network Inc", "Hauppauge computer works Inc", "Nebula Electronics Ltd", "", "Silicon Image, Inc",
    "Teles AG", "", "", "", "nCipher Security", "", "", "", "General Dynamics", "Dell", "", "", "LevelOne", "",
    "Oxide Computer Company", "Dell", "Compaq Computer Corporation", "", "Solidigm", "", "Hauppauge computer works Inc",
    "Davicom Semiconductor Inc", "", "SpeedStream", "XFX Pine Group Inc", "Hewlett-Packard Company", "ZyXEL Communications Corporation",
    "SK-Electronics Co", "TITech Computertechnik AG", "", "", "", "", "", "", "", "", "", "SCM Microsystems, Inc", "", "", "", "", "",
    "", "", "", "", "Dell Inc", "", "", "", "", "", "", "", "","", "", "", "", "", "", "", "", "", "", "", "Lightelligence", "", "",
    "Dynalink", "", "", "", "", "", "", "", "", "Sapphire, Inc", "Jingjia Microelectronics Co Ltd", "", "", "Ubiquiti Networks, Inc",
    "", "Wired Inc", "", "", "", "", "D-Link System Inc", "", "", "T1042 [Freescale]", "", "", "", "", "", "VIA Technologies, Inc", "",
    "", "", "", "", "", "", "", "", "", "BREA Technologies Inc", "", "", "Rhino Equipment Corp", "", "", "Bachmann electronic GmbH", "",
    "", "", "", "Preferred Networks, Inc", "", "", "Compaq Computer Corporation", "", "", "HaSoTec GmbH", "", "SHF Communication Technologies AG",
    "Acrox Technologies Co., Ltd", "", "", "", "Broadcom / LSI", "Kolter Electronic", "Advanced Micro Devices, Inc", "ULSI Systems",
    "VLSI, Technology Inc", "Avance Logic Inc", "Reply Group", "NetFrame Systems Inc", "Epson", "Phoenix Technologies", "National Semiconductor Corporation",
    "Tseng Labs Inc", "AST Research Inc", "Weitek", "Video Logic, Ltd", "Digital Equipment Corporation", "Micronics Computers Inc", "Cirrus Logic", "IBM",
    "LSI Logic Corp of Canada", "ICL Personal Systems", "SPEA Software AG", "Unisys Systems", "Elitegroup Computer Systems", "AT&T GIS (NCR)",
    "Vitesse Semiconductor", "Western Digital", "Maxim Integrated Products", "American Megatrends Inc", "PictureTel", "Hitachi Computer Products",
    "OKI Electric Industry Co. Ltd", "Advanced Micro Devices, Inc", "Trident Microsystems", "Beijing Dajia Internet Information Technology Co", "Acer Incorporated",
    "Dell", "Siemens Nixdorf IS", "LSI Logic", "Matrox Electronics System Ltd", "Chips and Technologies", "Wyse Technology Inc", "Olivetti Advanced Technology",
    "Toshiba America", "TMC Research", "Miro Computer Products AG", "Compaq", "NEC Corporation", "Framatome Connectors USA Inc", "Comp. & Comm. Research Lab",
    "Future Domain Corp.", "Hitachi Micro Systems", "AMP, Inc", "Silicon Integrated Systems", "Seiko Epson Corporation", "Tatung Corp. Of America", "Hewlett-Packard Company",
    "Solliday Engineering", "Synopsys/Logic Modelling Group", "Accelgraphics Inc", "Computrend", "Micron", "ASUSTeK Computer Inc", "Adaptec", "OPTi Inc", "IPC Corporation, Ltd",
    "Genoa Systems Corp", "Elsa AG", "Fountain Technologies, Inc", "STMicroelectronics", "BusLogic", "Texas Instruments", "Sony Corporation", "Oak Technology, Inc", "Co-time Computer Ltd",
    "Winbond Electronics Corp", "Anigma, Inc", "?Young Micro Systems", "Young Micro Systems", "Hitachi, Ltd", "Microchip Technology / SMSC", "ICL", "Motorola", "Electronics & Telecommunications RSH",
    "Kontron", "Promise Technology, Inc", "Foxconn Internationel, Inc", "Wipro Infotech Limited", "Number 9 Computer Compagny", "Vtech Computers Ltd", "Infotronic America Inc", "United Microelectronics",
    "I.I.T", "Maspar Computer Corp", "Ocean Office Automation", "Alcatel", "Texas Microsystems", "PicoPower Technology", "Mitshubishi Electric", "Diversified Technology", "Mylex Corporation",
    "Aten Research Inc", "Apple Inc", "Hynix Semiconductor", "Sequent Computer Systems", "DFI, Inc", "City Gate Develoment Ltd", "Daewoo Telecom Ltd", "Mitac", "CIT Co  Ltd", "Tamaha Corporation",
    "NexGen Microsystems", "Advanced Integrations Research", "Chaintech Computer Co. Ltd", "QLogic Corp", "Cyrix Corporation", "I-Bus", "NetWorth", "Gateway, Inc", "LG Electronics", "LeadTek Research Inc",
    "Interphase Corporation", "Data Technology Corporation", "Contaq Microsystems", "Supermac Technology", "EFA Corporation of America", "Forex Computer Corporation", "Parador", "", "J.Bond Computer Systems",
    "Cache Computer", "Microcomputer Systems(M) Son", "Data General Corporation", "SBS Technologies", "Oakleigh Systems Inc", "Olicom", "Oracle/SUN", "Systemsoft", "Compro Computer Services, Inc",
    "Intergraph Corporation", "Diamond Multimedia Systems", "National Instruments", "First International Computers", "Silicon Image, Inc", "Alacron", "Appian Technology", "Quantum Designs Ltd",
    "Samsung Electronics Co., Ltd", "Packard Bell", "Gemlight Computer Ltd.", "Megachips Corporation", "Zida Technologies Ltd", "Brooktree Corporation", "Trigem Computer Inc"
};

static const char *pciClass[] =
{
    "Unclassified", "Mass Storage Controller", "Network Controller", "Display Controller",
    "Multimedia Controller", "Memory Controller", "Bridge", "Simple Communication controller",
    "Base System Peripheral", "Input Device Controller", "Docking Station", "Processor",
    "Serial Bus Controller", "Wireless Controller", "Intelligent Controller", "Satellite Communication Controller",
    "Encryption Controller", "Signal Processing Controller", "Processing Accelerator", "Non-Essential Instrumentation",
    "", "Co-Processor", "", "Unassigned Class"
};

static const char *pciClassUnclassified[] =
{
    "Non-VGA-Compatible Device", "VGA-Compatible Device"
};

static const char *pciMassStorageController[] =
{
    "SCSI Bus Controller", "IDE Controller", "Floppy Disk Controller",
    "IPI Bus Controller", "RAID Controller", "ATA Controller", "Serial ATA Controller",
    "Serial Attached SCSI Controller", "Non-Volatile Memory Controller"
};

static const char *pciNetworkController[] =
{
    "Ethernet Controller", "Token Ring Controller", "FDDI Controller", "ATM Controller",
    "ISDN Controller", "WorldFip Controller", "PICMG 2.14 Multi Computing Controller",
    "Infiniband Controller", "Fabric Controller"
};

static const char *pciDisplayController[] =
{
    "VGA Compatible Controller", "XGA Controller", "3D Controller"
};

static const char *pciMultimediaController[] =
{
    "Multimedia Video Controller", "Multimedia Audio Controller", "Computer Telephony Device", "Audio Device"
};

static const char *pciMemoryController[] =
{
    "RAM Controller", "Flash Controller"
};

static const char *pciBridge[] =
{
    "Host Bridge", "ISA Bridge", "EISA Bridge", "MCA Bridge", "PCI-to-PCI Bridge",
    "PCMCIA Bridge", "NuBus Bridge", "CardBus Bridge", "RACEway Bridge", "PCI-to-PCI Bridge",
    "InfiniBand-o-PCI Host Bridge"
};

static const char *pciSimpleCommunicationController[] =
{
    "Serial Controller", "Parrallel Controller", "Multiport Serial Controller", "Modem",
    "IEEE 488.1/2 (GPIB) Controller", "Smart Card Controller"
};

static const char *pciBaseSystemPeripheral[] =
{
    "PIC", "DMA Controller", "Timer", "RTC Controller", "PCI Hot-Plug Controller",
    "SD Host Controller", "IOMMU"
};

static const char *pciInputDeviceController[] =
{
    "Keyboard Controller", "Digitizer Pen", "Mouse Controller", "Scanner Controller", "Gameport Controller"
};

static const char *pciDockingStation[] =
{
    "Generic"
};

static const char *pciSerialBusController[] =
{
    "FireWire (IEE 1394) Controller", "ACCESS Bus Controller", "SSA", "USB Controller",
    "Fibre Channel", "SMBus Controller", "InfiniBand Controller", "IPMI Interface",
    "SERCOS Interface (IEC 61491)", "CANbus Controller"
};

static const char *pciWirelessController[] =
{
    "iRDA Compatible Controller", "Consumer IR Controller", "RF Controller", "Bluethoot Controller",
    "Broadband Controller", "Ethernet Controller (802.1a)", "Ethernet Controller (802.1b)"
};

static const char *pciSatelliteCommunicationController[] =
{
    "Satellite TV Controller", "Satellite Audio Controller", "Satellite Voice Controller",
    "Satellite Data Controller"
};

static const char *pciEncryptionController[] =
{
    "Network and Computing Encryption/Decryption", "Entertainment Encryption/Decryption"
};

static const char *pciSignalProcessingController[] =
{
    "DPIO Modules", "Performance Counters", "Communication Sybchronizer", "Signal Processing Management"
};

// Dernier numéro: 0x109f

static uint16_t pciConfigReadWord(uint16_t bus, uint16_t device, uint16_t function, uint16_t offset)
{
    uint32_t lbus = (uint32_t)bus;
    uint32_t ldevice = (uint32_t)device;
    uint32_t lfunction = (uint32_t)function;

    uint32_t address = (uint32_t)(lbus << 16) | (ldevice << 11) | (lfunction << 8) | (offset & 0xFC) | ((uint32_t)0x80000000);
    outb(CONFIG_ADDRESS, address);
    uint16_t tmp = (uint16_t)((inb(CONFIG_DATA) >> (offset & 0x2) * 8) & 0xFFFF);
    return tmp;
}

void PCI_init()
{
    puts("[+]: Detection des appareils utilisant le PCI.\n");
    PCI_detect();
    // terminal_setcolor(VGA_LIGHT_MAGENTA);
    puts("[+]: liste des appareils disponibles.\n");
    // terminal_setcolor(VGA_BROWN);

    for (uint8_t i = 0; i < 2; i++)
    {
        PCIDeviceStruct pciCurrentStruct = pciDevices[i];

        (void)pciCurrentStruct;
        (void)pciVendors; // Unused variable
        puts("[+]--> Vendeur: ");
        puts(pciVendors[pciCurrentStruct.vendorID]);
        puts("\n");
        puts("[+]--> Classe: ");
        puts(pciClass[pciCurrentStruct.baseClass]);
        puts("\n");
    }

    // terminal_setcolor(VGA_WHITE);
}

void PCI_detect()
{
    uint8_t function, bus;

    uint8_t headerType = PCI_getHeaderType(0, 0, 0);
    if (PCI_deviceHasMultipleFunctions(headerType) == 0)
    {
        PCI_checkBus(0);
    }
    else
    {
        for (function = 0; function < 8; function++)
        {
            if (PCI_pciGetVendorID(0, 0, function) != 0xFFFF)
            {
                break;
            }
            bus = function;
            PCI_checkBus(bus);
        }
    }
}

void PCI_checkBus(uint16_t bus)
{
    for (uint8_t device = 0; device < 32; device++)
    {
        PCI_checkDevice(bus, device);
    }
}

void PCI_checkDevice(uint16_t bus, uint16_t device)
{
    uint16_t function = 0;
    uint16_t vendorID = PCI_pciGetVendorID(bus, device, function);
    
    if (vendorID == 0xFFFF) return;
    PCI_checkFunction(bus, device, function);

    PCIDeviceStruct pciStruct = PCI_dumpPCIInfos(bus, device, vendorID, function);
    PCI_addDevice(pciStruct);

    uint8_t headerType = PCI_getHeaderType(bus, device, function);
    if (PCI_deviceHasMultipleFunctions(headerType) == 1)
    {
        for (function = 1; function < 8; ++function)
        {
            if (PCI_pciGetVendorID(bus, device, function) != 0xFFFF)
            {
                PCI_checkFunction(bus, device, function);
            }
        }
    }
}

void PCI_checkFunction(uint16_t bus, uint16_t device, uint16_t function)
{
    uint8_t baseClass = PCI_getClass(bus, device, function);
    uint8_t subClass = PCI_getSubClass(bus, device, function);

    if ((baseClass == 0x6) && (subClass == 0x4)) {
        uint8_t secondaryBusNumber = PCI_getSecondaryBusNumber(bus, device, function);
        PCI_checkBus(secondaryBusNumber);
    }
}

void PCI_addDevice(PCIDeviceStruct pciStruct)
{
    pciDevices[indexDevice] = pciStruct;
    ++indexDevice;
}

bool PCI_deviceHasMultipleFunctions(uint8_t header_type) {

    return header_type & 0x80;
}

const char *PCI_getClassDevice(uint16_t bus, uint16_t device, uint16_t function)
{
    uint16_t classCode = PCI_getClass(bus, device, function);
    return pciClass[classCode];
}

const char *PCI_getSubClassDevice(uint16_t bus, uint16_t device, uint16_t function)
{
    uint8_t classCode, subclassCode;
    
    classCode = PCI_getClass(bus, device, function);
    subclassCode = PCI_getSubClass(bus, device, function);
    
    switch (classCode) {
        case 0x0:
            return pciClassUnclassified[subclassCode];
            break;
        case 0x1:
            return pciMassStorageController[subclassCode];
            break;
        case 0x2:
            return pciNetworkController[subclassCode];
            break;
        case 0x3:
            return pciDisplayController[subclassCode];
            break;
        case 0x4:
            return pciMultimediaController[subclassCode];
            break;
        case 0x5:
            return pciMemoryController[subclassCode];
            break;
        case 0x6:
            return pciBridge[subclassCode];
            break;
        case 0x7:
            return pciSimpleCommunicationController[subclassCode];
            break;
        case 0x8:
            return pciBaseSystemPeripheral[subclassCode];
            break;
        case 0x9:
            return pciInputDeviceController[subclassCode];
            break;
        case 0xA:
            return pciDockingStation[subclassCode];
            break;
        case 0xC:
            return pciSerialBusController[subclassCode];
            break;
        case 0xD:
            return pciWirelessController[subclassCode];
            break;
        case 0xF:
            return pciSatelliteCommunicationController[subclassCode];
            break;
        case 0x10:
            return pciEncryptionController[subclassCode];
            break;
        case 0x11:
            return pciSignalProcessingController[subclassCode];
            break;
        default:
            break;
    }

    return 0;
}

uint8_t PCI_getSecondaryBusNumber(uint16_t bus, uint16_t device, uint16_t function)
{
    uint8_t secondary_bus_number = (pciConfigReadWord(bus, device, function, 0x18) & 0xFF) >> 8;
    return secondary_bus_number;
}

uint8_t PCI_getHeaderType(uint16_t bus, uint16_t device, uint16_t function)
{
    uint8_t header_type = pciConfigReadWord(bus, device, function, 0xD);
    return (header_type & 0x7F);
}

uint8_t PCI_getClass(uint16_t bus, uint16_t device, uint16_t function)
{
    uint16_t classCode = pciConfigReadWord(bus, device, function, 0xA);
    return (uint8_t)(classCode & 0xFF00) >> 8;
}

uint8_t PCI_getSubClass(uint16_t bus, uint16_t device, uint16_t function)
{
    uint16_t subclassCode = pciConfigReadWord(bus, device, function, 0xA);
    return (uint8_t)(subclassCode & 0x00FF);
}

uint16_t PCI_pciGetVendorID(uint16_t bus, uint16_t device, uint16_t function)
{
    uint16_t vendor = pciConfigReadWord(bus, device, function, 0);
    return vendor;
}

uint16_t PCI_pciGetDeviceID(uint16_t bus, uint16_t device, uint16_t function)
{
    uint16_t device_id = pciConfigReadWord(bus, device, function, 0x2);
    return device_id;
}

PCIDeviceStruct PCI_dumpPCIInfos(uint16_t bus, uint16_t device, uint16_t vendor, uint16_t function) {

    PCIDeviceStruct pciStruct = {0};
    pciStruct.vendorID = vendor;
    pciStruct.deviceID = device;
    pciStruct.command = function;
    pciStruct.baseClass = PCI_getClass(bus, device, 0);
    pciStruct.subClass = PCI_getSubClass(bus, device, 0);
    pciStruct.headerType = PCI_getHeaderType(bus, device, 0);
    
    return pciStruct;
}
