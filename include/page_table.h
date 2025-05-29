#ifndef _PAGE_TABLE_H
#define _PAGE_TABLE_H


#include <stdint.h>

#define PAGE_DIRECTORY_INDEX(x) (x >> 22)
#define PAGE_TABLE_INDEX(x) ((x >> 12) & 0x03FF)


typedef struct {

    uint32_t present : 1;
    uint32_t read_write : 1;
    uint32_t user_supervisor : 1;
    uint32_t write_trought : 1;
    uint32_t cache_disable : 1;
    uint32_t accessed : 1;
    uint32_t avl1 : 1;
    uint32_t page_size : 1;
    uint32_t avl2 : 4;
    uint32_t address : 20;
} __attribute__((packed)) page_directory_t;


typedef struct {

    uint32_t present : 1;
    uint32_t read_write : 1;
    uint32_t user_supervisor : 1;
    uint32_t write_trought : 1;
    uint32_t cache_disable : 1;
    uint32_t accessed : 1;
    uint32_t dirty : 1;
    uint32_t pat : 1;
    uint32_t global : 1;
    uint32_t available : 3;
    uint32_t address : 20;
} __attribute__((packed)) page_table_t;


static inline void __flush_tlb(void *address) {

    asm volatile("invlpg (%0)" :: "r"(address) : "memory");
}


void fill_page_table(void);
void fill_page_directory(void);
void init_paging(void);

void map_address(void *physical_address, void *virtual_address);

extern void load_page_directory(uint32_t*);
extern void enable_paging(void);

extern page_directory_t page_directories[1024] __attribute__((aligned(4096)));
extern page_table_t first_page_table[1024] __attribute__((aligned(4096)));
extern uint8_t paging_enabled;


#endif
