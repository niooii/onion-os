#include <def.h>
#include <mm/alloc.h>

#include "pmm.h"

#define SIZE_CLASS_1 128
#define SIZE_CLASS_2 512
#define SIZE_CLASS_3 4096

// Header and footer of a block will be this structure.
struct block_info {
    size_t size;
    bool   free;
};

void* malloc(size_t size)
{
    return NULL;
}

void* realloc(void* block, size_t new)
{
    return NULL;
}

void free(void* block)
{
}