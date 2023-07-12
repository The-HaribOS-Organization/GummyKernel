#include "driver/keyboard.h"

uint8_t scancodeSet = 0;
bool isKeyboardStatusEnabled = false;

char *characters[] =
{
    "", "", "1", "2", "3", "4", "5", "6", "7", "8", "9",
    "0", "-", "=", "", "", "q", "w", "e", "r",
    "t", "y", "u", "i", "o", "p", "[", "]", "\n", "",
    "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "'", "`", "",
    "'\'", "z", "x", "c", "v", "b", "n", "m", ",", ".", "/", "",
    "*", "", " ", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "7",
    "8", "9", "-", "4", "5", "6", "+", "1", "2", "3", "0", ".", "", ""
};

static uint8_t keyboard_interfaceTest()
{
    keyboard_sendCommand(keyboard_interfaceTest);
    return keyboard_EncReadBuffer();
}

static void keyboard_callback(/* registers_t *regs */)
{
    if (keyboard_getStatus() & KEYBOARD_OUTPUT_BUFFER_STAT)
    {
        uint8_t code = keyboard_EncReadBuffer();
        //serial_print("[+]: Touche pressé !!!!\n", SERIAL_COM1_PORT);
        //serial_print(keyboard_getAsciiWithScancode(code), SERIAL_COM1_PORT);
        //printf(keyboard_getAsciiWithScancode(code));
    }
}

void keyboard_init()
{
    //printf("[+]: Initialisation du clavier PS/2.\n");

    keyboard_sendCommand(KEYBOARD_WRITE_COMMAND_BYTE);
    keyboard_sendCommand(0x55);

    uint8_t interface_test_status = keyboard_interfaceTest();
    //terminal_setcolor(VGA_LIGHT_MAGENTA);

    if (interface_test_status == 0)
    {
        printf("[-]: Succes, aucune erreur.\n");
    }
    else if (interface_test_status == 1)
    {
        printf("[-]: La ligne d'horloge est bloque au niveau bas.\n");
    }
    else if (interface_test_status == 2)
    {
        printf("[-]: La ligne d'horloge est bloque a un niveau eleve.\n");
    }
    else if (interface_test_status == 3)
    {
        printf("[-]: La ligne d'horloge est bloque en haut.\n");
    }
    else if (interface_test_status == 255)
    {
        printf("[-]: Erreur generale.\n");
    }

    scancodeSet = keyboard_setScanCode(KEYBOARD_SCANCODE_1);
    if (scancodeSet == KEYBOARD_SCANCODE_1)
    {
        // terminal_setcolor(VGA_LIGHT_GREEN);
        // printf("[+]: Scancode was set.\n");
        // terminal_setcolor(VGA_WHITE);
    }
    else
    {
        // terminal_setcolor(VGA_RED);
        // printf("[+]: Scancode was not set.\n");
        // terminal_setcolor(VGA_WHITE);
    }

    // register_interrupt_handler(1, keyboard_callback);

    // terminal_setcolor(VGA_GREEN);
    // printf("[+]: Clavier PS/2 initialise.\n");
    //terminal_setcolor(VGA_WHITE);
}

uint8_t keyboard_getStatus()
{
    // return inb(KEYBOARD_CONTROLLER_READ);
}

void keyboard_sendCommand(uint8_t command)
{
    while (true)
    {
        if ((keyboard_getStatus() & KEYBOARD_OUTPUT_BUFFER_STAT) == 0)
        {
            break;
        }
    }

    // outb(KEYBOARD_CONTROLLER_WRITE, command);
}

uint8_t keyboard_EncReadBuffer()
{
    // return inb(KEYBOARD_ENCODER_READ_INPUT_BUFFER);
}

char *keyboard_getAsciiWithScancode(uint8_t scancode)
{
    return characters[scancode];
}

uint8_t enable_keyboard()
{
    if (isKeyboardStatusEnabled == false)
    {
        keyboard_sendCommand(KEYBOARD_ENABLE_KYBR);
        isKeyboardStatusEnabled = true;
        return 0;
    }
    return 1;
}

uint8_t disable_keyboard()
{
    if (isKeyboardStatusEnabled == true)
    {
        keyboard_sendCommand(KEYBOARD_DISABLE_KYBR);
        isKeyboardStatusEnabled = false;
        return 0;
    }
    return 1;
}

int8_t keyboard_setScanCode(uint8_t scancode)
{
    // outb(KEYBOARD_ENCODER_keyboard_sendCommand, KEYBOARD_SET_ATLERNATE_SCAN_CODE);
    // outb(KEYBOARD_ENCODER_keyboard_sendCommand, scancode);

    uint8_t result /* = inb(KEYBOARD_CONTROLLER_READ) */;
    if (result == KEYBOARD_ACK_COMMAND)
    {
        return scancode;
    }
    else if (result == KEYBOARD_RESEND_LAST_RESULT)
    {
        return  -1;
    }
}
