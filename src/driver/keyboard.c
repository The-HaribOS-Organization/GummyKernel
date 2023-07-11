#include <stdint.h>
#include <stdbool.h>
#include <keyboard/keyboard.h>
#include <io/cursor.h>
#include <io/pic.h>
#include <libs/stdio.h>
#include <io/serial_port.h>
#include <idt/irq/irq.h>
#include <video/vga_text.h>


uint8_t scancode_set = 0;
bool keyboard_status_enable = false;

char *characters[] = {
        "", "", "1", "2", "3", "4", "5", "6", "7", "8", "9",
        "0", "-", "=", "", "", "q", "w", "e", "r",
        "t", "y", "u", "i", "o", "p", "[", "]", "\n", "",
        "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "'", "`", "",
        "'\'", "z", "x", "c", "v", "b", "n", "m", ",", ".", "/", "", 
        "*", "", " ", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "7",
        "8", "9", "-", "4", "5", "6", "+", "1", "2", "3", "0", ".", "", ""
};

static void keyboard_callback(registers_t *regs) {
    if (get_keyboard_status() & KEYBOARD_OUTPUT_BUFFER_STAT) {
        uint8_t code = keyboard_enc_read_buffer();
        serial_print("[+]: Touche pressé !!!!\n", SERIAL_COM1_PORT);
        serial_print(get_ascii_char(code), SERIAL_COM1_PORT);
        printf(get_ascii_char(code));
    }
}

void init_keyboard() {

    printf("[+]: Initialisation du clavier PS/2.\n");

    send_command(KEYBOARD_WRITE_COMMAND_BYTE);
    send_command(0x55);

    uint8_t interface_test_status = keyboard_interface_test();
    terminal_setcolor(VGA_LIGHT_MAGENTA);

    if (interface_test_status == 0)
        printf("[-]: Succes, aucune erreur.\n");
    else if (interface_test_status == 1)
        printf("[-]: La ligne d'horloge est bloque au niveau bas.\n");
    else if (interface_test_status == 2)
        printf("[-]: La ligne d'horloge est bloque a un niveau eleve.\n");
    else if (interface_test_status == 3)
        printf("[-]: La ligne d'horloge est bloque en haut.\n");
    else if (interface_test_status == 255)
        printf("[-]: Erreur generale.\n");

    scancode_set = set_scan_code(KEYBOARD_SCANCODE_1);
    if (scancode_set == KEYBOARD_SCANCODE_1) {
        terminal_setcolor(VGA_LIGHT_GREEN);
        printf("[+]: Scancode was set.\n");
        terminal_setcolor(VGA_WHITE);
    } else {
        terminal_setcolor(VGA_RED);
        printf("[+]: Scancode was not set.\n");
        terminal_setcolor(VGA_WHITE);
    }
    
    register_interrupt_handler(1, keyboard_callback);
    
    terminal_setcolor(VGA_GREEN);
    printf("[+]: Clavier PS/2 initialise.\n");
    terminal_setcolor(VGA_WHITE);
}

uint8_t get_keyboard_status() {
    return inb(KEYBOARD_CONTROLLER_READ);
}

void send_command(uint8_t command) {

    while (true) {
        if ((get_keyboard_status() & KEYBOARD_OUTPUT_BUFFER_STAT) == 0) {
            break;
        }
    }

    outb(KEYBOARD_CONTROLLER_WRITE, command);
}

uint8_t keyboard_enc_read_buffer() {
    return inb(KEYBOARD_ENCODER_READ_INPUT_BUFFER);
}


char *get_ascii_char(uint8_t scancode) {

    return characters[scancode];
}

uint8_t keyboard_interface_test() {
    
    send_command(KEYBOARD_INTERFACE_TEST);
    return keyboard_enc_read_buffer();
}

uint8_t enable_keyboard() {

    if (keyboard_status_enable == false) {
        send_command(KEYBOARD_ENABLE_KYBR);
        keyboard_status_enable = true;
        return 0;
    } else {
        return 1;
    }
}

uint8_t disable_keyboard() {
    if (keyboard_status_enable == true) {
        send_command(KEYBOARD_DISABLE_KYBR);
        keyboard_status_enable = false;
        return 0;
    } else {
        return 1;
    }
}

int8_t set_scan_code(uint8_t scancode) {

    int8_t value = 0;
    outb(KEYBOARD_ENCODER_SEND_COMMAND, KEYBOARD_SET_ATLERNATE_SCAN_CODE);
    outb(KEYBOARD_ENCODER_SEND_COMMAND, scancode);
    
    uint8_t result = inb(KEYBOARD_CONTROLLER_READ);
    if (result == KEYBOARD_ACK_COMMAND)
        value = scancode;
    else if (result == KEYBOARD_RESEND_LAST_RESULT)
        value = -1;
    
    return value;
}
