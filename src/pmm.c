#include <stdint.h>
#include "pmm.h"


k_heap_header_t kheap;

void init_k_heap(void) {

    set_k_heap_zero(&kheap);
    k_heap_add_block(&kheap, ALIGN_UP(HEAP_BASE), 0x100000, 16);
}

void k_heap_add_block(k_heap_header_t *heap, uintptr_t address, uint64_t size, uint64_t base_size) {

    kheap_block_header *b = (kheap_block_header *)address;
    b->size = size - sizeof(k_heap_header_t);
    b->bsize = base_size;

    b->next = heap->fblock;
    heap->fblock = b;

    // Calcul du nombre de sous-bloc.
    uint32_t b_count = b->size / b->bsize;
    uint8_t *bitmap = (uint8_t *)&b[1];

    for (uint32_t x = 0; x < b_count; x++) bitmap[x] = 0;

    b_count = (b_count / base_size) * base_size < b_count ? b_count / base_size + 1 : b_count / base_size;
    for (uint32_t x = 0; x < b_count; x++) bitmap[x] = 5;

    b->lfb = b_count - 1;
    b->is_free = b_count;
    return;
}

void *k_malloc(k_heap_header_t *kheap, uint32_t size) {

    kheap_block_header *b;
    uint32_t b_count, x, y, z, b_need;
    uint8_t *bm, nid;

    for (b = kheap->fblock; b; b = b->next) {

        if (b->size - (b->is_free * b->bsize) >= size) {

            b_count = b->size / b->bsize;
            b_need = (size / b->bsize) * b->bsize < size ? size / b->bsize + 1 : size / b->bsize;
            bm = (uint8_t *)&b[1];

            for (x = (b->lfb + 1 >= b_count ? 0 : b->lfb +1); x < b->lfb; x++) {

                if (x >= b_count) x = 0;

                if (bm[x] == 0) {

                    for (y = 0; bm[x + y] == 0 && y < b_need && (x + y) < b_count; y++);
                    if (y == b_need) {

                        nid = k_heap_generate_nid(bm[x - 1], bm[x + y]);
                        for (z = 0; z < y; z++) bm[x + z] = nid;

                        b->lfb = (x + b_need) - 2;
                        b->is_free += y;

                        return (void *)(x * b->bsize + (uintptr_t)&b[1]);
                    }

                    x += (y - 1);
                    continue;
                }
            }
        }
    }

    return NULL;
}

void k_free(k_heap_header_t *kheap, void *ptr) {

    kheap_block_header *b;
    uintptr_t ptroff;
    uint32_t bi, x, max;
    uint8_t *bm, id;


    for (b = kheap->fblock; b; b = b->next) {

        if ((uintptr_t)ptr > (uintptr_t)b && (uintptr_t)ptr < (uintptr_t)b + sizeof(kheap_block_header) + b->size) {

            ptroff = (uintptr_t)ptr - (uintptr_t)&b[1];
            bi = ptroff / b->bsize;
            bm = (uint8_t *)&b[1];
            id = bm[bi];

            max = b->size / b->bsize;
            for (x = bi; bm[x] == id && x < max; x++) bm[x] = 0;

            b->is_free -= x - bi;
            return;
        }
    }

    return;
}
