/* Cet en-tête définie les fonctions utiles à l'affichage des caractères tapés à l'écran
On récupère le code de la touche pressé et on regarde à quel caractère ASCII celle-ci correspond

ce code utilise un clavier QWERTY. Il faudra donc l'adapter afin de pouvoir l'utiliser sur un clavier AZERTY
*/

#ifndef _KEYBOARD_
#define _KEYBOARD_

#include <stdint.h>
#include <idt/irq/irq.h>


enum keyboard_encoder_io {
    KEYBOARD_ENCODER_READ_INPUT_BUFFER = 0x60,
    KEYBOARD_ENCODER_SEND_COMMAND = 0x60
};

enum keyboard_controller_io {
    KEYBOARD_CONTROLLER_READ = 0x64,
    KEYBOARD_CONTROLLER_WRITE = 0x64
};

enum keyboard_controller_stats {
    KEYBOARD_OUTPUT_BUFFER_STAT = 0x01,
    KEYBOARD_INPUT_BUFFER_STAT = 0x02,
    KEYBOARD_SYSTEM_FLAG = 0x04,
    KEYBOARD_COMMAND_DATA = 0x08,
    KEYBOARD_LOCKED = 0x10,
    KEYBOARD_AUX_OUTPUT_BUFFER_FULL = 0x20,
    KEYBOARD_TIMEOUT = 0x40,
    KEYBOARD_PARITY_ERROR = 0x80
};

enum keyboard_encoder_command {
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
};

enum keyboard_scan_code {
    KEYBOARD_SCANCODE_1 = 0x02,
    KEYBOARD_SCANCODE_2 = 0x04,
    KEYBOARD_SCANCODE_4 = 0x08
};

enum keyboard_return_codes {
    KEYBOARD_LEFT_SHIFT_MAKE_CODE = 0xAA,
    KEYBOARD_ECHO_COMMAND_RESULT = 0xEE,
    KEYBOARD_ACK_COMMAND = 0xFA,
    KEYBOARD_RESEND_LAST_COMMAND = 0xFE,
    KEYBOARD_ERROR = 0xFF
};

enum keyboard_controller_command {
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
};

void init_keyboard();
uint8_t get_keyboard_status();
uint8_t keyboard_enc_read_buffer();
void send_command(uint8_t command);
char *get_ascii_char(uint8_t scancode);
uint8_t keyboard_interface_test();
uint8_t enable_keyboard();
uint8_t disable_keyboard();
int8_t set_scan_code(uint8_t scancode);

#endif
