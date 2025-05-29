#ifndef _SERIAL_
#define _SERIAL_

#include <stdint.h>
#include <stdbool.h>


#define SERIAL_COM1 0x3F8
#define SERIAL_COM2 0x2F8
#define SERIAL_COM3 0x3E8
#define SERIAL_COM4 0x2E8
#define SERIAL_COM5 0x5F8
#define SERIAL_COM6 0x4F8
#define SERIAL_COM7 0x5E8
#define SERIAL_COM8 0x4E8

#define SERIAL_TRANSMIT(x) (x+0)
#define SERIAL_INTERRUPT_ENABLE_REGISTER(x) (x+1)
#define SERIAL_FIFO_CONTROL_REGISTER(x) (x+2)
#define SERIAL_LINE_CONTROL_REGISTER(x) (x+3)
#define SERIAL_MODEM_CONTROL_REGISTER(x) (x+4)
#define SERIAL_LINE_STATUS_REGISTER(x) (x+5)
#define SERIAL_MODEM_STATUS_REGISTER(x) (x+6)
#define SERIAL_SCRATCH_REGISTER(x) (x+7)


bool init_serial(uint16_t com_port);
void send_string(uint16_t com_port, char *string, ...);
void send_char(uint16_t com_port, char character);
char *recv_data(uint16_t com_port);

#endif
