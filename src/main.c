/*
Fonction main executant le code du kernel.
*/


#define _MULTIBOOT_VERSION_2

#include <stdint.h>
#include "gdt.h"
#include "gfx/text.h"
#include "gfx/framebuffer.h"
#include "interrupt/interrupt.h"
#include "klibc/stdio.h"
#include "rtc.h"
#include "interrupt/8259PIC.h"
#include "pit.h"
#include "gfx/shapes.h"
#include "keyboard.h"
#include "pc_speaker.h"
#include "acpi/rsdp.h"
#include "acpi/acpi.h"
#include "klibc/string.h"
#include "acpi/fadt.h"
#include "comm/ps2.h"
#include "comm/serial.h"
#include "comm/pci.h"
#include "acpi/mcfg.h"
#include "acpi/madt.h"
#include "gfx/effects.h"
#include "gfx/textinput.h"
#include "gfx/frame.h"
#include "mouse.h"
#include "klibc/math.h"
#include "pmm.h"
#include "page_table.h"


#ifdef _MULTIBOOT_VERSION_1
#include "multiboot.h"
#endif

#ifdef _MULTIBOOT_VERSION_2
#include "multiboot2.h"
#endif


uint8_t *rsdp;
void *fadt_address, *mcfg_table, *madt_table;


void kernel_main(unsigned long multiboot_addr, uint_fast32_t signature) {

#ifdef _MULTIBOOT_VERSION_1
    if (signature == MULTIBOOT_BOOTLOADER_MAGIC) {
    
        multiboot_info_t *multiboot_struct = (multiboot_info_t *)multiboot_addr;
        void *fb = (void *)((unsigned long) multiboot_struct->framebuffer_addr);
        set_framebuffer(
            fb,
            multiboot_struct->framebuffer_pitch);
        fillScreen(background_color);
    }
#endif

#ifdef _MULTIBOOT_VERSION_2
    
    if (signature == MULTIBOOT2_BOOTLOADER_MAGIC) {

        for (struct multiboot_tag *tag = (struct multiboot_tag *)(multiboot_addr + 8); tag->type != MULTIBOOT_TAG_TYPE_END; tag = (struct multiboot_tag *)((uint8_t *)tag + ((tag->size + 7) & ~7))) {

            if (tag->type == MULTIBOOT_TAG_TYPE_FRAMEBUFFER) {

                struct multiboot_tag_framebuffer *fbuffer = (struct multiboot_tag_framebuffer *)tag;
                void *fb = (void *)((unsigned long) fbuffer->common.framebuffer_addr);
                set_framebuffer(
                    fb,
                    fbuffer->common.framebuffer_pitch);
                fillScreen(background_color);
            } else if (tag->type == MULTIBOOT_TAG_TYPE_ACPI_NEW) {

                struct multiboot_tag_new_acpi *acpi = (struct multiboot_tag_new_acpi *)tag;
                rsdp = (uint8_t *)acpi->rsdp;

            } else if (tag->type == MULTIBOOT_TAG_TYPE_ACPI_OLD) {

                struct multiboot_tag_old_acpi *acpi = (struct multiboot_tag_old_acpi *)tag;
                rsdp = (uint8_t *)acpi->rsdp;
            }
        }
    }

#endif

    if (init_serial(SERIAL_COM1) == true) printf("[+]: Port serie initialise.\n");
    else printf("[+]: Port serie non active.\n");

    send_string(SERIAL_COM1, "[+]: RSDP address: 0x%x\n", rsdp);
    rsdp_t *rsdp_struct = get_rsdp_struct(rsdp);

    fadt_address = findDescriptor((uint32_t *)rsdp_struct->rsdt_address, "FACP");
    if (fadt_address == NULL) {
        send_string(SERIAL_COM1, "[+]: Erreur, descripteur null.\n");
    } else {
        fadt_structure = (fadt_t *)fadt_address;
        send_string(SERIAL_COM1, "[+]: Descripteur trouve: %s\n", fadt_structure->h.signature);
        if (!checksum_field(&fadt_structure->h)) send_string(SERIAL_COM1, "[+]: FADT non valide.\n");
    }


    mcfg_table = findDescriptor((uint32_t *)rsdp_struct->rsdt_address, "MCFG");
    if (mcfg_table == NULL) {
        send_string(SERIAL_COM1, "[+]: Erreur, descripteur null.\n");
    } else {
        mcfg_structure = (mcfg_t *)mcfg_table;
        send_string(SERIAL_COM1, "[+]: Descripteur trouve: %s\n", mcfg_structure->h.signature);
        if (!checksum_field(&mcfg_structure->h)) send_string(SERIAL_COM1, "[+]: MCFG non valide.\n");
    }

    madt_table = findDescriptor((uint32_t *)rsdp_struct->rsdt_address, "APIC");
    if (madt_table == NULL) {
        send_string(SERIAL_COM1, "[+]: Erreur, descripteur null.\n");
    } else {
        madt_structure = (madt_t *)madt_table;
        send_string(SERIAL_COM1, "[+]: Descripteur trouve: %s\n", madt_structure->h.signature);
        if (!checksum_field(&madt_structure->h)) send_string(SERIAL_COM1, "[+]: MADT non valide.\n");
    }

    if (!check_acpi_enable()) {
        send_string(SERIAL_COM1, "[+]: Activation de l'ACPI.\n");
        outb(fadt_structure->smi_cmd, fadt_structure->acpi_enable);
        send_string(SERIAL_COM1, "[+]: ACPI active.\n");
    } else {
        send_string(SERIAL_COM1, "[+]: ACPI active.\n");
    }

    init_k_heap();

    initGDT();
    send_string(SERIAL_COM1, "[+]: GDT initialise.\n");

    initIDT();
    send_string(SERIAL_COM1, "[+]: IDT Initialise.\n");

    // init_paging();
    // for (uint32_t i = 0; i < WIDTH * HEIGHT * 4; i += 0x1000) map_address((void *)framebuffer + i, (void *)virtual_framebuffer + i);
    //printf("Pagin init.\n");

    initRTC();
    send_string(SERIAL_COM1, "[+]: RTC initialise.\n");

    init_timer(15);
    send_string(SERIAL_COM1, "[+]: PIT initialise.\n");

    init_ps2();
    send_string(SERIAL_COM1, "[+]: Controleur PS/2 initialise.\n");
    init_kboard();
    send_string(SERIAL_COM1, "[+]: Clavier initialise initialise.\n");
    init_mouse();
    send_string(SERIAL_COM1, "[+]: Souris PS/2 initialise.\n");

    pci_probe();


    datetime_t date = get_time();
    printf("[+]: Date du jour: %s %u %s %d\n", map_week(date.weekday), date.day_month, map_month(date.month), date.year + 2000);
    send_string(SERIAL_COM1, "[+]: Date du jour: %s %u %s %d\n", map_week(date.weekday), date.day_month, map_month(date.month), date.year + 2000);
    printf("Bienvenu sur GummyKernel.\n");
    printf("#/> ");

    drawEllipse((Vec2){500, 250}, (Vec2){175, 150}, (Vec3){255, 255, 255, 0});
    for (;;) asm("hlt");
}
