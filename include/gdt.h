#ifndef _GDT_
#define _GDT_

#include <stdint.h>


typedef struct {

    uint16_t size;
    uint32_t offset;
} __attribute__((packed)) gdt_entry_t;


typedef struct {

    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access_byte;
    uint8_t flags;
    uint8_t base_high;
} __attribute__((packed)) segment_descriptor_t;


void initGDT(void);
void encodeGDTEntry(uint8_t index, uint32_t base, uint32_t limit, uint8_t flags, uint8_t access_byte);

extern void setGDT(uint32_t);

#endif

