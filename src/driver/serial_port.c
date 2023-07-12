#include "driver/serial_port.h"

void serial_setBaudsSpeedRate(uint16_t com, uint16_t divisor)
{
    // outb(SERIAL_LINE_CONTROL(com), SERIAL_LINE_ENABLE_DLAB);
    // outb(SERIAL_COM_PORT(com), (divisor >> 8) & 0x00FF);
    // outb(SERIAL_COM_PORT(com), divisor & 0x00FF);
}

void serial_configureLine(unsigned short com)
{
    // outb(SERIAL_LINE_CONTROL(com), 0x03);
}

uint8_t serial_isFIFOEmpty(uint16_t com)
{
    /* Retourne 0 si la file FIFO n'est pas vide
    Retourne 1 si la file FIFO est vide*/

    // TODO
    return 1; // inb(SERIAL_LINE_STATE(com)) & 0x20
}

uint16_t check_if_received_ok(uint16_t com)
{
    // TODO
    return 1; // inb(SERIAL_LINE_STATE(com)) & 1
}

char serial_read(uint16_t com)
{
    while (check_if_received_ok(com) == 0);

    // TODO
    return 1; // inb(com)
}

void serial_putchar(unsigned char character, uint16_t com)
{
    while (check_if_fifo_empty(com) == 0);
    
    // TODO
    // outb(com, character);
}

void serial_print(const char *string, uint16_t com)
{
    // TODO
    uint16_t len = 0; // strlen(string)
    for (uint16_t i = 0; i < len; ++i)
    {
        serial_putchar(string[i], SERIAL_COM_PORT(com));
    }
}