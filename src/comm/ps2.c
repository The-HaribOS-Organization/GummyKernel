#include <stdint.h>
#include "comm/ps2.h"
#include "comm/serial.h"
#include "acpi/fadt.h"
#include "klibc/stdio.h"
#include "io.h"
#include "pit.h"


void init_ps2(void) {
    
    uint8_t controllers_port = 0, controller_byte = 0;

    (fadt_structure->iapc_boot_arch & 0x2) 
        ? send_string(SERIAL_COM1, "[+]: PS/2 controleur initialise.\n")
        : send_string(SERIAL_COM1, "[+]: Pas d'appareil PS/2 a configurer.\n");

    // Désactivation des ports PS/2.
    outb(COMMAND_REGISTER_PS2, DISABLE_FIRST_PS2);
    outb(COMMAND_REGISTER_PS2, DISABLE_SECOND_PS2);

    // Flush du buffer.
    inb(DATA_PORT_PS2);

    // On réécrit l'octect du contrôleur PS/2
    outb(COMMAND_REGISTER_PS2, READ_INTERNAL_RAM_0);
    controller_byte = inb(DATA_PORT_PS2);

    outb(COMMAND_REGISTER_PS2, WRITE_INTERNAL_RAM_0);
    outb(COMMAND_REGISTER_PS2, (controller_byte & 0x2E));

    // Test du contrôleur.
    outb(COMMAND_REGISTER_PS2, TEST_PS2_CONTROLLER);
    if (inb(DATA_PORT_PS2) != 0x55) {
        send_string(SERIAL_COM1, "[+]: Erreur lors du test.\n");
    } else if (inb(DATA_PORT_PS2) != 0xFC) {}

    // Détermination du nombre de canaux.
    outb(COMMAND_REGISTER_PS2, READ_INTERNAL_RAM_0);
    if (inb(DATA_PORT_PS2) & 0x20) {
        
        controllers_port = 1;
        send_string(SERIAL_COM1, "[+]: 1 canal PS/2 detecte.\n");
    } else {
        controllers_port = 2;
    }
    // Test du premier canal PS/2.
    outb(COMMAND_REGISTER_PS2, TEST_PS2_FIRST_PORT);
    if (inb(DATA_PORT_PS2) == 0x00) send_string(SERIAL_COM1, "[+]: Test passe avec succes.\n");
    else return;

    // Activation des ports PS/2
    if (controllers_port == 1) {

        outb(COMMAND_REGISTER_PS2, WRITE_INTERNAL_RAM_0);
        outb(COMMAND_REGISTER_PS2, 0xA6);
        outb(COMMAND_REGISTER_PS2, ENABLE_FIRST_PS2);

    } else if (controllers_port == 2) {

        outb(COMMAND_REGISTER_PS2, WRITE_INTERNAL_RAM_0);
        outb(COMMAND_REGISTER_PS2, 0xE2);
        outb(COMMAND_REGISTER_PS2, ENABLE_FIRST_PS2);
        outb(COMMAND_REGISTER_PS2, ENABLE_SECOND_PS2);
    }
}
