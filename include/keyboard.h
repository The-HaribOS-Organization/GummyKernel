#ifndef _KEYBOARD_H
#define _KEYBOARD_H


#include <stdint.h>
#include "interrupt/irq_handler.h"

// Octects de commande du clavier PS/2

#define LED_SETTING_COMMAND 0xED
#define ECHO_COMMAND 0xEE
#define SET_SCAN_CODE_COMMAND 0xF0
#define IDENTIFY_KBOARD_COMMAND 0xF2
#define DELAY_COMMAND 0xF3
#define ENABLING_SCANNING_COMMAND 0xF4
#define DISABLING_SCANNING_COMMAND 0xF5
#define SET_DEFAULT_PARAMETER 0xF6
#define AUTOREAPEAT_COMMAND 0xF7
#define KEYS_RELEASE_COMMAND 0xF8
#define RESEND_LAST_BYTE_COMMAND 0xFE
#define RESET_COMMAND 0xFF

// Octects de réponses du contrôleur du clavier.

#define ACK_KBOARD 0xFA
#define RESEND_COMMAND 0xFE
#define KEY_DETECTION_ERROR 0x00
#define KBOARD_POWER_UP 0xAA
#define ECHO_COMMAND_RESPONSE 0xEE
#define INTERNAL_BUFFER_OVERRUN 0xFF

// I/O Port du clavier PS/2

#define DATA_PORT 0x60
#define COMMAND_REGISTER_KBOARD 0x64

// Octects de contrôle du clavier PS/2
#define CONTROLLER_CONFIG_BYTE 0x20


void init_kboard(void);
void kboard_handler(isr_frame *frame);

#endif
