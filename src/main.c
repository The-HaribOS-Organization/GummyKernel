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
                printf("RSDP address: ", (Vec3){255, 176, 107, 0});
                printf(itoa((int_fast32_t)acpi->rsdp, 16), (Vec3){255, 176, 107, 0});
            } else if (tag->type == MULTIBOOT_TAG_TYPE_ACPI_OLD) {

                struct multiboot_tag_old_acpi *acpi = (struct multiboot_tag_old_acpi *)tag;
                printf("RSDP address: ", (Vec3){255, 176, 107, 0});
                printf(itoa((int_fast32_t)acpi->rsdp, 16), (Vec3){255, 176, 107, 0});
                putchar('\n', (Vec3){255, 176, 107, 0});

                rsdp = acpi->rsdp;
            }
        }
    }
#endif

    initGDT();
    printf("[+]: GDT initialise\n", (Vec3){241, 202, 255, 0});

    initIDT();
    printf("[+]: IDT initialise\n", (Vec3){241, 202, 255, 0});

    initRTC();
    printf("[+]: RTC initialise\n", (Vec3){241, 202, 255, 0});

    init_timer(15);
    printf("[+]: PIT initialise\n", (Vec3){241, 202, 255, 0});

    init_kboard();
    printf("[+]: Clavier PS/2 initialise\n", (Vec3){241, 202, 255, 0});

    datetime_t date = get_time();

    printf("[+]: Date du jour: ", (Vec3){220, 255, 235, 0});
    printf(map_week(date.weekday), (Vec3){220, 255, 235, 0});
    putchar(' ', (Vec3){255, 255, 255, 0});
    printf(itoa(date.day_month, 10), (Vec3){220, 255, 235, 0});
    putchar(' ', (Vec3){255, 255, 255, 0});
    printf(map_month(date.month), (Vec3){220, 255, 235, 0});
    putchar(' ', (Vec3){255, 255, 255, 0});
    printf(itoa(date.year + 2000, 10), (Vec3){220, 255, 235, 0});
    putchar('\n', (Vec3){255, 255, 255, 0});

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