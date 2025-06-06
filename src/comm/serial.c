#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>
#include "io.h"
#include "comm/serial.h"
#include "klibc/stdio.h"


char *buffer;


bool init_serial(uint16_t com_port) {

    outb(SERIAL_INTERRUPT_ENABLE_REGISTER(com_port), 0x00);
    outb(SERIAL_LINE_CONTROL_REGISTER(com_port), 0x80);
    outb(SERIAL_TRANSMIT(com_port), 0x03);
    outb(SERIAL_INTERRUPT_ENABLE_REGISTER(com_port), 0x00);
    outb(SERIAL_LINE_CONTROL_REGISTER(com_port), 0x03);
    outb(SERIAL_FIFO_CONTROL_REGISTER(com_port), 0xC7);
    outb(SERIAL_MODEM_CONTROL_REGISTER(com_port), 0x0B);

    // Écriture d'un octect au hasard voir si tout est correctement initialisé.
    outb(SERIAL_TRANSMIT(com_port), 0xAE);
    if (inb(com_port) == 0xAE) return false;

    return true;
}


void send_string(uint16_t com_port, char *string, ...) {

    va_list va;
    va_start(va, string);

    for (int_fast32_t i = 0; string[i] != '\0'; i++) {

        if (string[i] == '%') {

            switch (string[i+1]) {
                case 'd':
                    send_string(com_port, itoa(va_arg(va, int32_t), 10));
                    break;
                case 'u':
                    send_string(com_port, itoa(va_arg(va, uint32_t), 10));
                    break;
                case 's':
                    send_string(com_port, va_arg(va, char *));
                    break;
                case 'x':
                    send_string(com_port, itoa(va_arg(va, int32_t), 16));
                    break;
                default:
                    break;
            }

            i += 2;
        }

        send_char(com_port, string[i]);
    }
}

void send_char(uint16_t com_port, char character) {

    while ((inb(SERIAL_LINE_STATUS_REGISTER(com_port) & 0x20)) == 0);
    outb(com_port, character);
}

char *recv_data(uint16_t com_port) {

    static char result[256];
    int i = 0;

    while (inb(SERIAL_LINE_STATUS_REGISTER(com_port) & 0x1) == 0) {

        result[i] = inb(SERIAL_TRANSMIT(com_port));
        i++;
    }

    return result;
}
