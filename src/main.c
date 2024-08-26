/*
Fonction main executant le code du kernel.
*/


#define _MULTIBOOT_VERSION_2

#include <stdint.h>
#include "gdt.h"
#include "gfx/text.h"
#include "gfx/framebuffer.h"
#include "interrupt/interrupt.h"
#include "libc/stdio.h"
#include "rtc.h"
#include "interrupt/8259PIC.h"
#include "pit.h"
#include "gfx/shapes.h"
#include "keyboard.h"
#include "pc_speaker.h"
#include "acpi/rsdp.h"
#include "acpi/acpi.h"
#include "libc/mem.h"
#include "acpi/fadt.h"
#include "comm/ps2.h"


#ifdef _MULTIBOOT_VERSION_1
#include "multiboot.h"
#endif

#ifdef _MULTIBOOT_VERSION_2
#include "multiboot2.h"
#endif


uint8_t *rsdp;
void *fadt_address;


void kernel_main(unsigned long multiboot_addr, uint_fast32_t signature) {

#ifdef _MULTIBOOT_VERSION_1
    if (signature == MULTIBOOT_BOOTLOADER_MAGIC) {
    
        multiboot_info_t *multiboot_struct = (multiboot_info_t *)multiboot_addr;
        void *fb = (void *)((unsigned long) multiboot_struct->framebuffer_addr);
        set_framebuffer(
            fb,
            multiboot_struct->framebuffer_pitch);
        fillScreen((Vec3){75, 50, 48, 0});
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
                fillScreen((Vec3){75, 50, 48, 0});
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

    printf("\x1b[255;176;107mRSDP address: 0x%x\n", rsdp);
    rsdp_t *rsdp_struct = get_rsdp_struct(rsdp);

    if ((fadt_address = findDescriptor((uint32_t *)rsdp_struct->rsdt_address, "FACP")) == NULL) printf("\x1b[255;120;107m[+]: Erreur, descripteur null.\n");
    else fadt_structure = (fadt_t *)fadt_address;

    if (!checksum_field(&fadt_structure->h)) printf("\x1b[255;120;107m[+]: FADT non valide.\n");


    if (!check_acpi_enable()) {
        printf("\x1b[255;176;107m[+]: Activation de l'ACPI.\n");
        outb(fadt_structure->smi_cmd, fadt_structure->acpi_enable);
        printf("\x1b[107;255;152m[+]: ACPI active.\n");
    } else {
        printf("\x1b[107;255;152m[+]: ACPI active.\n");
    }

    initGDT();
    printf("\x1b[241;202;255m[+]: GDT initialise\n");

    initIDT();
    printf("\x1b[241;202;255m[+]: IDT initialise\n");

    initRTC();
    printf("\x1b[241;202;255m[+]: RTC initialise\n");

    init_timer(15);
    printf("\x1b[241;202;255m[+]: PIT initialise\n");

    init_ps2();

    init_kboard();
    printf("\x1b[241;202;255m[+]: Clavier PS/2 initialise\n");

    datetime_t date = get_time();
    printf("\x1b[220;255;235m[+]: Date du jour: %s %u %s %d\n", map_week(date.weekday), date.day_month, map_month(date.month), date.year + 2000);

    for (;;) { asm("hlt"); }
}