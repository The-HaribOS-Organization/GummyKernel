#include <stdint.h>
#include <stdbool.h>
#include "keyboard.h"
#include "interrupt/8259PIC.h"
#include "interrupt/irq_handler.h"
#include "io.h"
#include "libc/stdio.h"


char *scan_code_set_1[] = {
    "", "[ESC]", "1", "2", "3", "4", "5", "6", "7", "8", "9",
    "0", "-", "=", "[BCKSPCE]", "[TAB]", "Q", "W", "E", "R", "T",
    "Y", "U", "I", "O", "P", "[", "]", "[ENTER]", "[LCTRL]", "A",
    "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", "[LSHIFT]",
    "\"", "Z", "X", "C", "V", "B", "N", "M", ",", ".", "/", "[RSHIFT]",
    "*", "[LALT]", " ", "[CAPSLOCK]", "[F1]", "[F2]", "[F3]", "[F4]",
    "[F5]", "[F6]", "[F7]", "[F8]", "[F9]", "[F10]", "[NUMBERLOCK]",
    "[SCROLLLOCK]", "7", "8", "9", "-", "4", "5", "6", "+", "1", "2",
    "3", "0", ".", "", "", "", "[F11]", "[F12]", "", "", "", ""};


char *scan_code_set_2[] = {
    "", "[F9]", "", "[F5]", "[F3]", "[F1]", "[F2]", "[F12]", "",
    "[F10]", "[F8]", "[F6]", "[F4]", "[TAB]", "`", "", "", "[LALT]",
    "[LSHIFT]", "", "[LCTRL]", "Q", "1", "", "", "", "Z", "S", "A",
    "W", "2", "", "", "C", "X", "D", "E", "4", "3", "", "", " ", "V",
    "F", "T", "R", "5", "", "", "N", "B", "H", "G", "Y", "6", "", "", "",
    "M", "J", "U", "7", "8", "", "", ",", "K", "I", "O", "0", "9", "", "",
    ".", "/", "L", ";", "P", "-", "", "", "", "'", "", "[", "=", "", "", "[CAPSLOCK]",
    "[RSHIFT]", "[ENTER]", "]", "", "\"", "", "", "", "", "", "", "", ""};


void init_kboard(void) {

    outb(COMMAND_REGISTER_KBOARD, 0x55);
    pic_clear_mask(1);
}

void kboard_handler(isr_frame *frame) {

    irq_stack_state = frame;
    if (inb(COMMAND_REGISTER_KBOARD) & 0x01) {

        uint8_t scan_code = inb(DATA_PORT);
        printf("\x1b[125;125;255m%s", scan_code_set_1[scan_code]);
    }
}