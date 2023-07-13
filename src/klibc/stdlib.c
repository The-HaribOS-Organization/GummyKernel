#include "klibc/stdlib.h"

////////////////////////////////////
//  Internal types and variables  //
////////////////////////////////////

// +-----------+
// |  Structs  |
// +-----------+

typedef struct {
    void *ptr;
    size_t size;
} HeapChunk;

typedef struct {
    size_t count;
    HeapChunk chunks[HEAP_ALLOCATED_CHUNKS_CAPACITY]
} HeapChunkList;

// +-------------+
// |  variables  |
// +-------------+

static uint8_t heap[HEAP_CAPACITY] = { 0 };

static HeapChunkList allocatedChunks = { 
    0
};

static HeapChunkList freeChunks = { 
    1,
    { 
        [0] = (HeapChunk){ heap, sizeof(heap) } 
    } 
};

///////////////////////////
//  Internals functions  //
///////////////////////////

static void addChunkList(HeapChunkList *list, void *ptr, size_t size)
{
    list->chunks[list->count] = (HeapChunk) {
        ptr,
        size
    };
}

static void removeChunkList(HeapChunkList *list, size_t index)
{
    assert(index < list->count);
    for (size_t i = index; i < list->count - 1; ++i)
    {
        list->chunks[i] = list->chunks[i + 1];
    }
    list->count -= 1;
}

static size_t findChunkList(HeapChunkList *list, void *ptr)
{
    for(size_t i = 0; i < list->count; ++i)
    {
        if(list->chunks[i].ptr == ptr)
        {
            return i;
        }
    }

    // If not found
    return UINT64_MAX;
}

// Sort and merge neighbors
static void cleanFreeChunkList()
{
    if(freeChunks.count == 1)
    {
        return;
    }

    // Bubble sort
    size_t n = freeChunks.count;

    for (int i = 0; i < n - 1; ++i)
    {
        bool isSorted = true;
        for (int j = 0; j < n - i - 1; j++)
        {
            if(freeChunks.chunks[j].ptr > freeChunks.chunks[j + 1].ptr)
            {
                HeapChunk tmpChunk = { freeChunks.chunks[j].ptr, freeChunks.chunks[j].size };
                freeChunks.chunks[j] = freeChunks.chunks[j + 1];
                freeChunks.chunks[j + 1] = tmpChunk;
                isSorted = false;
            }
        }

        if (isSorted == true)
        {
            break;
        }
    }

    // Merge
    bool isClean = false;
    while(!isClean)
    {
        isClean = true;
        
        for(size_t i = 0; i < freeChunks.count; ++i)
        {
            if(freeChunks.chunks[i].ptr + freeChunks.chunks[i].size == freeChunks.chunks[i + 1].ptr)
            {
                freeChunks.chunks[i].size += freeChunks.chunks[i + 1].size;
                removeChunkList(&freeChunks, i + 1);
                isClean = false;
            }
        }
    }
}

/////////////////
//  Functions  //
/////////////////

void *malloc(size_t memorySize)
{
    // Can't allocate more chunks
    if(allocatedChunks.count >= HEAP_ALLOCATED_CHUNKS_CAPACITY)
    {
        return NULL;
    }

    for(size_t i = 0; i < freeChunks.count; ++i)
    {
        if(freeChunks.chunks[i].size >= memorySize)
        {
            addChunkList(&allocatedChunks, freeChunks.chunks[i].ptr, memorySize);
            
            if(freeChunks.chunks[i].size != memorySize) // To not add a 0 byte long free chunk
            {
                addChunkList(&freeChunks, freeChunks.chunks[i].ptr + memorySize, freeChunks.chunks[i].size - memorySize);
            }

            removeChunkList(&freeChunks.chunks[i].ptr, i);

            return freeChunks.chunks[i].ptr;
        }
    }

    // If no adress has been found
    return NULL;
}

void *calloc(size_t elementCount, size_t elementSize)
{
    size_t realSize = elementCount * elementSize;
    
    void *ptr = malloc(realSize);
    memset(ptr, 0, realSize / sizeof(int));

    return ptr;
}

void *realloc(void *ptr, size_t memorySize)
{
    void *newPtr = malloc(memorySize);

    size_t chunkIndex = findChunkList(&allocatedChunks, ptr);
    if(chunkIndex != INT64_MAX)
    {
        // Copy the old data to the new buffer
        memcpy(newPtr, &allocatedChunks.chunks[chunkIndex], allocatedChunks.chunks[chunkIndex].size);
    }

    free(ptr);

    return newPtr;
}

void free(void *ptr)
{
    // Don't crash on free(NULL)
    if(ptr == NULL)
    {
        return;
    }

    size_t chunkIndex = findChunkList(&allocatedChunks, ptr);
    if(chunkIndex != INT64_MAX)
    {
        addChunkList(&freeChunks, allocatedChunks.chunks[chunkIndex].ptr, allocatedChunks.chunks[chunkIndex].size);
        removeChunkList(&allocatedChunks, chunkIndex);
        
        cleanFreeChunkList();
    }
}

/////////////////////////////
//  Non standard fucntion  //
/////////////////////////////

char *itoa(int num, char *str, int base)
{
    int i = 0;
    bool isNegative = false;

    // Special cases
    if(num == 0)
    {
        str[i++] = '0'; // str[0] but i is now 1
        str[i] = '\0';
        return str;
    }

    if(num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }

    // Conversion
    while(num != 0)
    {
        int modulo = num % base;
        str[i++] = (modulo > 9) ? (modulo - 10) + 'a' : modulo + '0';
        num = num / base;
    }

    if(isNegative)
    {
        str[i++] = '-';
    }

    str[i] = '\0';

    // Final reverse
    strrev(str);

    return str;
}