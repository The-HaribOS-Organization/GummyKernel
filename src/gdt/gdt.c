#include <stdint.h>
#include "gdt.h"


gdt_entry_t entries;
segment_descriptor_t descriptors[5];


void initGDT(void) {

    entries.size = sizeof(segment_descriptor_t) * 5 - 1;
    entries.offset = (uint32_t)&descriptors;

    encodeGDTEntry(0, 0, 0, 0, 0);
    encodeGDTEntry(1, 0, 0xFFFFFFFF, 0xCF, 0x9A);
    encodeGDTEntry(2, 0, 0xFFFFFFFF, 0xCF, 0x92);
    encodeGDTEntry(3, 0, 0xFFFFFFFF, 0xCF, 0xFA);
    encodeGDTEntry(4, 0, 0xFFFFFFFF, 0xCF, 0xF2);

    setGDT((uint32_t)&entries);
}

void encodeGDTEntry(uint8_t index, uint32_t base, uint32_t limit, uint8_t flags, uint8_t access_byte) {

    descriptors[index].base_low = (base & 0xFFFF);
    descriptors[index].base_middle = ((base >> 16) & 0xFF);
    descriptors[index].base_high = ((base >> 24) & 0xFF);

    descriptors[index].limit_low = (limit & 0xFFFF);
    descriptors[index].flags = (flags & 0xF0) | ((limit >> 16) & 0x0F);
    descriptors[index].access_byte = access_byte;
}
