#include <io/serial_port.h>
#include <io/cursor.h>
#include <libs/stdio.h>
#include <libs/strings.h>
#include <stddef.h>

void set_bauds_speed_rate(uint16_t com, uint16_t divisor) {
    
    outb(SERIAL_LINE_CONTROL(com), SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_COM_PORT(com), (divisor >> 8) & 0x00FF);
    outb(SERIAL_COM_PORT(com), divisor & 0x00FF);
}

void configure_line(unsigned short com) {
    outb(SERIAL_LINE_CONTROL(com), 0x03);
}

uint8_t check_if_fifo_empty(uint16_t com) {
    /* Retourne 0 si la file FIFO n'est pas vide
    Retourne 1 si la file FIFO est vide*/
    return inb(SERIAL_LINE_STATE(com)) & 0x20;
}

uint16_t check_if_received_ok(uint16_t com) {
    return inb(SERIAL_LINE_STATE(com)) & 1;
}

char serial_read(uint16_t com) {
    while (check_if_received_ok(com) == 0);
    return inb(com);
}

void serial_putchar(unsigned char character, uint16_t com) {
    while (check_if_fifo_empty(com) == 0);
    if(character == '\n')
        outb(com, '\r');
    outb(com, character);
}

void serial_print(const char *string, uint16_t com) {
    
    uint16_t len = strlen(string);
    for (uint16_t i = 0; i < len; i++) {
        serial_putchar(string[i], SERIAL_COM_PORT(com));
    }
}
