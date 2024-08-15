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


#ifdef _MULTIBOOT_VERSION_1
#include "multiboot.h"
#endif

#ifdef _MULTIBOOT_VERSION_2
#include "multiboot2.h"
#endif


static const uint_fast32_t notes[6][8] = {
    {294, 587, 440, 392, 784, 440, 740, 440},
    {294, 587, 440, 392, 784, 440, 740, 440},
    {330, 587, 440, 392, 784, 440, 740, 440},
    {330, 587, 440, 392, 784, 440, 740, 440},
    {392, 587, 440, 392, 784, 440, 740, 440},
    {392, 587, 440, 392, 784, 440, 740, 440}};

uint8_t *rsdp;

void kernel_main(unsigned long multiboot_addr, uint_fast32_t signature) {

#ifdef _MULTIBOOT_VERSION_1
    if (signature == MULTIBOOT_BOOTLOADER_MAGIC) {
    
        multiboot_info_t *multiboot_struct = (multiboot_info_t *)multiboot_addr;
        void *fb = (void *)((unsigned long) multiboot_struct->framebuffer_addr);
        set_framebuffer(
            fb,
            multiboot_struct->framebuffer_pitch);
        fillScreen((Vec3){35, 38, 39, 0});
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
                fillScreen((Vec3){35, 38, 39, 0});
            } else if (tag->type == MULTIBOOT_TAG_TYPE_ACPI_NEW) {

                struct multiboot_tag_new_acpi *acpi = (struct multiboot_tag_new_acpi *)tag;
                printf("\x1b[255;176;107mRSDP address: 0x%x\n", (int_fast32_t)acpi->rsdp);
            } else if (tag->type == MULTIBOOT_TAG_TYPE_ACPI_OLD) {

                struct multiboot_tag_old_acpi *acpi = (struct multiboot_tag_old_acpi *)tag;
                printf("\x1b[255;176;107mRSDP address: 0x%x\n", (int_fast32_t)acpi->rsdp);
                rsdp = acpi->rsdp;
            }
        }
    }
#endif

    initGDT();
    printf("\x1b[241;202;255m[+]: GDT initialise\n");

    initIDT();
    printf("\x1b[241;202;255m[+]: IDT initialise\n");

    initRTC();
    printf("\x1b[241;202;255m[+]: RTC initialise\n");

    init_timer(15);
    printf("\x1b[241;202;255m[+]: PIT initialise\n");

    init_kboard();
    printf("\x1b[241;202;255m[+]: Clavier PS/2 initialise\n");

    datetime_t date = get_time();
    printf("\x1b[220;255;235m[+]: Date du jour: %s %u %s %d\n", map_week(date.weekday), date.day_month, map_month(date.month), date.year + 2000);
    
    find_FADT(rsdp);

    for (uint8_t i = 0; i < 4; i++) {
        
        for (uint8_t i = 0; i < 6; i++) {
            for (uint8_t j = 0; j < 8; j++) {

                make_beep(notes[i][j]);
                sleep(20);
                shutup();
            }
        }
    }

    for (;;) { asm("hlt"); }
}