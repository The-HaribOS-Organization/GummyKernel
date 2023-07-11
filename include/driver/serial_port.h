/* Le fichier contient toutes les fonctions nécessaires
à l'envoie de donnée en sortie sur le port série.
*/
#ifndef _SERIAL_PORT_
#define _SERIAL_PORT_

#include <stdint.h>

enum serial_ports {
    SERIAL_COM1_PORT = 0x3F8,
    SERIAL_COM2_PORT = 0x2F8,
    SERIAL_COM3_PORT = 0x3E8,
    SERIAL_COM4_PORT = 0x2E8,
    SERIAL_COM5_PORT = 0x5F8,
    SERIAL_COM6_PORT = 0x4F8,
    SERIAL_COM7_PORT = 0x5E8,
    SERIAL_COM8_PORT = 0x4E8
};

#define SERIAL_COM_PORT(base) (base)
#define SERIAL_ACTIVATION_INTERRUPT(base) (base+1)
#define SERIAL_ACTIVATION_INTERRUPT_FIFO(base) (base+2)
#define SERIAL_LINE_CONTROL(base) (base+3)
#define SERIAL_MODEM_CONTROL(base) (base+4)
#define SERIAL_LINE_STATE(base) (base+5)
#define SERIAL_MODEM_STATE(base) (base+6)
#define SERIAL_GRAB_REGISTER(base) (base+7)

#define SERIAL_LINE_ENABLE_DLAB 0x80

void set_bauds_speed_rate(
    uint16_t com, uint16_t divisor);

void configure_line(unsigned short com);
uint8_t check_if_fifo_empty(uint16_t com);
uint16_t check_if_received_ok(uint16_t com);
char serial_read(uint16_t com);

void serial_putchar(unsigned char character, uint16_t com);
void serial_print(const char *string, uint16_t com);

#endif
