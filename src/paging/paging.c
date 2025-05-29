#include <stdint.h>
#include "page_table.h"
#include "klibc/string.h"


uint8_t paging_enabled = 0;
page_directory_t page_directories[1024] __attribute__((aligned(4096)));
page_table_t first_page_table[1024] __attribute__((aligned(4096)));


void fill_page_table(void) {

    for (uint16_t i = 0; i < 1024; i++) {

        first_page_table[i].present = 1;
        first_page_table[i].read_write = 1;
        first_page_table[i].user_supervisor = 0;
        first_page_table[i].address = i;
    }
    
    // first_page_table[i] = (i * 0x1000) | 0x3;
    return;
}

void fill_page_directory(void) {

    for (uint16_t i = 0; i < 1024; i++) {
        
        page_directories[i].present = 0;
        page_directories[i].read_write = 0;
        page_directories[i].user_supervisor = 0;
        page_directories[i].write_trought = 0;
        page_directories[i].cache_disable = 0;
        page_directories[i].accessed = 0;
        page_directories[i].avl1 = 0;
        page_directories[i].page_size = 0;
        page_directories[i].avl2 = 0;
        page_directories[i].address = 0;
    }
    // page_directories[i] = 0x00000000;
    return;
}

void init_paging(void) {

    fill_page_table();
    fill_page_directory();

    page_directories[0].present = 1;
    page_directories[0].read_write = 1;
    page_directories[0].user_supervisor = 0;
    page_directories[0].address = ((uint32_t)&first_page_table) >> 12;

    load_page_directory((uint32_t *)page_directories);
    enable_paging();
    paging_enabled = 1;
}

void map_address(void *physical_address, void *virtual_address) {

    uint32_t page_directory_index = PAGE_DIRECTORY_INDEX((uint32_t)virtual_address);
    uint32_t page_table_index = PAGE_TABLE_INDEX((uint32_t)virtual_address);

    page_table_t *pt = (page_table_t *)(page_directories[page_directory_index].address << 12);
    pt[page_table_index].present = 1;
    pt[page_table_index].read_write = 1;
    pt[page_table_index].address = (uint32_t)physical_address >> 12;
    __flush_tlb(virtual_address);
}
