#ifndef _PMM_H
#define _PMM_H

#include <stdint.h>
#include <stddef.h>

#define HEAP_BASE (void *)&_kernel_end
#define ALIGN_UP(x) (((uintptr_t)x + 0xFFF) & ~0xFFF)


typedef struct kheap_block_header {
    struct kheap_block_header *next;
    uint32_t size;
    uint32_t is_free;
    uint32_t bsize;
    uint32_t lfb;
} kheap_block_header;

typedef struct {
    kheap_block_header *fblock;
} k_heap_header_t;


extern k_heap_header_t kheap;

inline void set_k_heap_zero(k_heap_header_t *kheap) {
    kheap->fblock = 0;
}

inline uint8_t k_heap_generate_nid(uint8_t a, uint8_t b) {

    uint8_t c;
    for (c = a + 1; c == b || c == 0; c++);
    return c;
}


void init_k_heap(void);
void k_heap_add_block(k_heap_header_t *heap, uintptr_t address, uint64_t size, uint64_t base_size);
void *k_malloc(k_heap_header_t *kheap, uint32_t size);
void k_free(k_heap_header_t *kheap, void *ptr);


extern uint32_t _kernel_end;

#endif
