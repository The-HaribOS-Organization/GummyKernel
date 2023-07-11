/* Contient tous le prototypes de fonctions
ainsi que les macros nécéssaires à l'utilisation du PIC.*/

#ifndef _PIC_
#define _PIC_

#include <stdint.h>
#include <stdbool.h>
#include <idt/irq/irq.h>


#define PIC1_COMMAND 0x20
#define PIC2_COMMAND 0xA0
#define PIC1_DATA 0x21
#define PIC2_DATA 0xA1
#define PIC1_START_INTERRUPT 0x20
#define PIC2_START_INTERRUPT 0x28

#define PIC_EOI 0x20
#define ICW1_ICW4 0x01
#define ICW1_SINGLE 0x02
#define ICW1_INTERVAL4 0x04
#define ICW1_LEVEL 0x08
#define ICW1_INIT 0x10

#define ICW4_8086 0x01
#define ICW4_AUTO 0x02
#define ICW4_BUF_SLAVE 0x08
#define ICW4_BUF_MASTER 0x0C
#define ICW4_SFNM 0x10

void PICremap(uint8_t offset_master, uint8_t offset_slave);
bool disable_PIC();
bool enable_PIC();
bool mask_IRQ(uint8_t irq);
bool unmask_IRQ(uint8_t irq);
void PIC_endOfInterrupt(uint8_t interrupt);

#endif
