#include <stdint.h>
#include <stdbool.h>
#include <pci/pci.h>
#include <io/cursor.h>
#include <libs/stdio.h>
#include <video/vga_text.h>
#include <io/serial_port.h>


uint32_t index_device = 0;
PCI_Device_Struct_t pci_devices[256];

const char *pciVendors[] = {
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

const char *pci_class[] = {
    "Unclassified", "Mass Storage Controller", "Network Controller", "Display Controller",
    "Multimedia Controller", "Memory Controller", "Bridge", "Simple Communication controller",
    "Base System Peripheral", "Input Device Controller", "Docking Station", "Processor",
    "Serial Bus Controller", "Wireless Controller", "Intelligent Controller", "Satellite Communication Controller",
    "Encryption Controller", "Signal Processing Controller", "Processing Accelerator", "Non-Essential Instrumentation",
    "", "Co-Processor", "", "Unassigned Class"
};

const char *pci_class_unclassified[] = {
    "Non-VGA-Compatible Device", "VGA-Compatible Device"
};

const char *pci_mass_storage_controller[] = {
    "SCSI Bus Controller", "IDE Controller", "Floppy Disk Controller",
    "IPI Bus Controller", "RAID Controller", "ATA Controller", "Serial ATA Controller",
    "Serial Attached SCSI Controller", "Non-Volatile Memory Controller"
};

const char *pci_network_controller[] = {
    "Ethernet Controller", "Token Ring Controller", "FDDI Controller", "ATM Controller",
    "ISDN Controller", "WorldFip Controller", "PICMG 2.14 Multi Computing Controller",
    "Infiniband Controller", "Fabric Controller"
};

const char *pci_display_controller[] = {
    "VGA Compatible Controller", "XGA Controller", "3D Controller"
};

const char *pci_multimedia_controller[] = {
    "Multimedia Video Controller", "Multimedia Audio Controller", "Computer Telephony Device", "Audio Device"
};

const char *pci_memory_controller[] = {
    "RAM Controller", "Flash Controller"
};

const char *pci_bridge[] = {
    "Host Bridge", "ISA Bridge", "EISA Bridge", "MCA Bridge", "PCI-to-PCI Bridge",
    "PCMCIA Bridge", "NuBus Bridge", "CardBus Bridge", "RACEway Bridge", "PCI-to-PCI Bridge",
    "InfiniBand-o-PCI Host Bridge"
};

const char *pci_simple_communication_controller[] = {
    "Serial Controller", "Parrallel Controller", "Multiport Serial Controller", "Modem",
    "IEEE 488.1/2 (GPIB) Controller", "Smart Card Controller"
};

const char *pci_base_system_peripheral[] = {
    "PIC", "DMA Controller", "Timer", "RTC Controller", "PCI Hot-Plug Controller",
    "SD Host Controller", "IOMMU"
};

const char *pci_input_device_controller[] = {
    "Keyboard Controller", "Digitizer Pen", "Mouse Controller", "Scanner Controller", "Gameport Controller"
};

const char *pci_docking_station[] = {
    "Generic"
};

const char *pci_serial_bus_controller[] = {
    "FireWire (IEE 1394) Controller", "ACCESS Bus Controller", "SSA", "USB Controller",
    "Fibre Channel", "SMBus Controller", "InfiniBand Controller", "IPMI Interface",
    "SERCOS Interface (IEC 61491)", "CANbus Controller"
};

const char *pci_wireless_controller[] = {
    "iRDA Compatible Controller", "Consumer IR Controller", "RF Controller", "Bluethoot Controller",
    "Broadband Controller", "Ethernet Controller (802.1a)", "Ethernet Controller (802.1b)"
};

const char *pci_satellite_communication_controller[] = {
    "Satellite TV Controller", "Satellite Audio Controller", "Satellite Voice Controller",
    "Satellite Data Controller"
};

const char *pci_encryption_controller[] = {
    "Network and Computing Encryption/Decryption", "Entertainment Encryption/Decryption"
};

const char *pci_signal_processing_controller[] = {
    "DPIO Modules", "Performance Counters", "Communication Sybchronizer", "Signal Processing Management"
};

// Dernier numéro: 0x109f

static uint16_t pciConfigReadWord(uint16_t bus, uint16_t device, uint16_t function, uint16_t offset) {

    uint32_t lbus = (uint32_t)bus;
    uint32_t ldevice = (uint32_t)device;
    uint32_t lfunction = (uint32_t)function;

    uint32_t address = (uint32_t)(lbus << 16) | (ldevice << 11) | (lfunction << 8) | (offset & 0xFC) | ((uint32_t)0x80000000);
    outb(CONFIG_ADDRESS, address);
    uint16_t tmp = (uint16_t)((inb(CONFIG_DATA) >> (offset & 0x2) * 8) & 0xFFFF);
    return tmp;
}

uint8_t getClass(uint16_t bus, uint16_t device, uint16_t function) {
    
    uint16_t class_code = pciConfigReadWord(bus, device, function, 0xA);
    return (uint8_t)(class_code & 0xFF00) >> 8;
}

uint8_t getSubClass(uint16_t bus, uint16_t device, uint16_t function) {

    uint16_t subclass_code = pciConfigReadWord(bus, device, function, 0xA);
    return (uint8_t)(subclass_code & 0x00FF);
}

uint16_t pciGetVendorID(uint16_t bus, uint16_t device, uint16_t function) {

    uint16_t vendor = pciConfigReadWord(bus, device, function, 0);
    return vendor;
}

uint16_t pciGetDeviceID(uint16_t bus, uint16_t device, uint16_t function) {

    uint16_t device_id = pciConfigReadWord(bus, device, function, 0x2);
    return device_id;
}

uint8_t getPCIHeaderType(uint16_t bus, uint16_t device, uint16_t function) {

    uint8_t header_type = pciConfigReadWord(bus, device, function, 0xD);
    return (header_type & 0x7F);
}

bool deviceHasMultipleFunctions(uint8_t header_type) {

    return header_type & 0x80;
}

void add_pci_device(PCI_Device_Struct_t pci_struct) {

    pci_devices[index_device] = pci_struct;
    index_device++;
}

const char *getPCIClassDevice(uint16_t bus, uint16_t device, uint16_t function) {
    
    uint16_t class_code = getClass(bus, device, function);
    return pci_class[class_code];
}

const char *getPCISubClassDevice(uint16_t bus, uint16_t device, uint16_t function) {
    
    uint8_t class_code, subclass_code;
    
    class_code = getClass(bus, device, function);
    subclass_code = getSubClass(bus, device, function);

    switch (class_code) {
        case 0x0:
            return pci_class_unclassified[subclass_code];
            break;
        case 0x1:
            return pci_mass_storage_controller[subclass_code];
            break;
        case 0x2:
            return pci_network_controller[subclass_code];
            break;
        case 0x3:
            return pci_display_controller[subclass_code];
            break;
        case 0x4:
            return pci_multimedia_controller[subclass_code];
            break;
        case 0x5:
            return pci_memory_controller[subclass_code];
            break;
        case 0x6:
            return pci_bridge[subclass_code];
            break;
        case 0x7:
            return pci_simple_communication_controller[subclass_code];
            break;
        case 0x8:
            return pci_base_system_peripheral[subclass_code];
            break;
        case 0x9:
            return pci_input_device_controller[subclass_code];
            break;
        case 0xA:
            return pci_docking_station[subclass_code];
            break;
        case 0xC:
            return pci_serial_bus_controller[subclass_code];
            break;
        case 0xD:
            return pci_wireless_controller[subclass_code];
            break;
        case 0xF:
            return pci_satellite_communication_controller[subclass_code];
            break;
        case 0x10:
            return pci_encryption_controller[subclass_code];
            break;
        case 0x11:
            return pci_signal_processing_controller[subclass_code];
            break;
        default:
            break;
    }

    return 0;
}

void checkBus(uint16_t bus) {

    for (uint8_t device = 0; device < 32; device++) {
        checkDevice(bus, device);
    }
}

uint8_t get_secondary_bus_number(uint16_t bus, uint16_t device, uint16_t function) {

    uint8_t secondary_bus_number = (pciConfigReadWord(bus, device, function, 0x18) & 0xFF) >> 8;
    return secondary_bus_number;
}

void checkDevice(uint16_t bus, uint16_t device) {
    
    uint16_t function = 0;
    uint16_t vendor_id = pciGetVendorID(bus, device, function);
    
    if (vendor_id == 0xFFFF) return;
    checkFunction(bus, device, function);

    PCI_Device_Struct_t pci_struct = dumpPCIInfos(bus, device, vendor_id, function);
    add_pci_device(pci_struct);

    uint8_t header_type = getPCIHeaderType(bus, device, function);
    if (deviceHasMultipleFunctions(header_type) == 1) {
        for (function = 1; function < 8; function++) {
            if (pciGetVendorID(bus, device, function) != 0xFFFF) {
                checkFunction(bus, device, function);
            }
        }
    }
}

void checkFunction(uint16_t bus, uint16_t device, uint16_t function) {

    uint8_t base_class = getClass(bus, device, function);
    uint8_t sub_class = getSubClass(bus, device, function);

    if ((base_class == 0x6) && (sub_class == 0x4)) {
        uint8_t secondary_bus_number = get_secondary_bus_number(bus, device, function);
        checkBus(secondary_bus_number);
    }
}

PCI_Device_Struct_t dumpPCIInfos(uint16_t bus, uint16_t device, uint16_t vendor, uint16_t function) {

    PCI_Device_Struct_t pci_struct = {0};
    pci_struct.vendor_id = vendor;
    pci_struct.device_id = device;
    pci_struct.command = function;
    pci_struct.base_class = getClass(bus, device, 0);
    pci_struct.sub_class = getSubClass(bus, device, 0);
    pci_struct.header_type = getPCIHeaderType(bus, device, 0);
    
    return pci_struct;
}

void detect_pci() {

    uint8_t function, bus;

    uint8_t header_type = getPCIHeaderType(0, 0, 0);
    if (deviceHasMultipleFunctions(header_type) == 0) {
        checkBus(0);
    } else {
        for (function = 0; function < 8; function++) {
            if (pciGetVendorID(0, 0, function) != 0xFFFF) break;
            bus = function;
            checkBus(bus);
        }
    }
}

void initPCI() {

    printf("[+]: Detection des appareils utilisant le PCI.\n");
    detect_pci();
    terminal_setcolor(VGA_LIGHT_MAGENTA);
    printf("[+]: liste des appareils disponibles.\n");
    terminal_setcolor(VGA_BROWN);

    for (uint8_t i = 0; i < 2; i++) {
        PCI_Device_Struct_t pci_current_struct = pci_devices[i];
        printf("[+]--> Vendeur: ");
        printf(pciVendors[pci_current_struct.vendor_id]);
        printf("\n");
        printf("[+]--> Classe: ");
        printf(pci_class[pci_current_struct.base_class]);
        printf("\n");
    }

    terminal_setcolor(VGA_WHITE);
}
