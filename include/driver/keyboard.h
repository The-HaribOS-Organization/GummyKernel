/*
    File    : keyboard.h
    Utility : The keyboard driver
 */

#ifndef KERNEL_KEYBOARD_H_INCLUDED
#define KERNEL_KEYBOARD_H_INCLUDED

// #include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "apic/pic.h"
#include "driver/serial_port.h"

/////////////////////////
//  Constants & types  //
/////////////////////////

typedef enum {
    KEYBOARD_ENCODER_READ_INPUT_BUFFER = 0x60,
    KEYBOARD_ENCODER_SEND_COMMAND = 0x60
} KeyboardEncoderIO;

typedef enum {
    KEYBOARD_CONTROLLER_READ = 0x64,
    KEYBOARD_CONTROLLER_WRITE = 0x64
} KeyboardControllerIO;

typedef enum {
    KEYBOARD_OUTPUT_BUFFER_STAT = 0x01,
    KEYBOARD_INPUT_BUFFER_STAT = 0x02,
    KEYBOARD_SYSTEM_FLAG = 0x04,
    KEYBOARD_COMMAND_DATA = 0x08,
    KEYBOARD_LOCKED = 0x10,
    KEYBOARD_AUX_OUTPUT_BUFFER_FULL = 0x20,
    KEYBOARD_TIMEOUT = 0x40,
    KEYBOARD_PARITY_ERROR = 0x80
} KeyboardControllerStats;

typedef enum {
    KEYBOARD_SET_LED = 0xED,
    KEYBOARD_ECHO_COMMAND = 0xEE,
    KEYBOARD_SET_ATLERNATE_SCAN_CODE = 0xF0,
    KEYBOARD_SEND_2_NEXT_BYTES= 0xF2,
    KEYBOARD_REPEAT_RATE = 0xF3,
    KEYBOARD_ENABLE = 0xF4,
    KEYBOARD_RESET_WAIT_ENABLING = 0xF5,
    KEYBOARD_RESET_BEGIN_SCANNING = 0xF6,
    KEYBOARD_SET_AUTOREPEAT = 0xF7,
    KEYBOARD_SET_KEY_BREAK_MAKE_CODE = 0xF8,
    KEYBOARD_GENERATE_MAKE_CODE = 0xF9,
    KEYBOARD_ALL_KEYS_AUTOREPEAT_SEND_MAKE_BREAK = 0xFA,
    KEYBOARD_SET_SINGLE_KEY_AUTOREPEAT = 0xFB,
    KEYBOARD_SET_SINGLE_KEY_MAKE_BREAK = 0xFC,
    KEYBOARD_SET_SINGLE_KEY_BREAK = 0xFD,
    KEYBOARD_RESEND_LAST_RESULT = 0xFE,
    KEYBOARD_RESET_KEYBOARD = 0xFF
} KeyboardEncoderCommand;

typedef enum {
    KEYBOARD_SCANCODE_1 = 0x02,
    KEYBOARD_SCANCODE_2 = 0x04,
    KEYBOARD_SCANCODE_4 = 0x08
} KeyboardScanCode;

typedef enum {
    KEYBOARD_LEFT_SHIFT_MAKE_CODE = 0xAA,
    KEYBOARD_ECHO_COMMAND_RESULT = 0xEE,
    KEYBOARD_ACK_COMMAND = 0xFA,
    KEYBOARD_RESEND_LAST_COMMAND = 0xFE,
    KEYBOARD_ERROR = 0xFF
} KeyboardReturnCodes;

typedef enum {
    KEYBOARD_READ_COMMAND_BYTE = 0x20,
    KEYBOARD_WRITE_COMMAND_BYTE = 0x60,
    KEYBOARD_SELF_TEST = 0xAA,
    KEYBOARD_INTERFACE_TEST = 0xAB,
    KEYBOARD_DISABLE_KYBR = 0xAD,
    KEYBOARD_ENABLE_KYBR = 0xAE,
    KEYBOARD_READ_INPUT_PORT = 0xC0,
    KEYBOARD_READ_OUTPUT_PORT = 0xD0,
    KEYBOARD_WRITE_OUTPUT_PORT = 0xD1,
    KEYBOARD_READ_TEST_INPUT = 0xE0,
    KEYBOARD_SYSTEM_RESET = 0xFE,
    KEYBOARD_DISABLE_MOUSE_PORT = 0xA7,
    KEYBOARD_ENABLE_MOUSE_PORT = 0xA8,
    KEYBOARD_TEST_MOUSE_PORT = 0xA9,
    KEYBOARD_WRITE_TO_MOUSE = 0xD4
} KeyboardControllerCommand;

/////////////////
//  Functions  //
/////////////////

uint8_t enable_keyboard();
uint8_t disable_keyboard();

void keyboard_init();
uint8_t keyboard_getStatus();
uint8_t keyboard_EncReadBuffer();
void keyboard_sendCommand(uint8_t command);
char *keyboard_getAsciiWithScancode(uint8_t scancode);
int8_t keyboard_setScanCode(uint8_t scancode);

#endif // KERNEL_KEYBOARD_H_INCLUDED
