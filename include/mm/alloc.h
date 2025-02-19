#pragma once

#include <def.h>

// If alignment is not a power of 2, the behavior is undefined.
uint64_t FORCEINLINE ALIGN_UP(uint64_t addr, uint64_t alignment)
{
    return (addr & ~(alignment - 1)) + alignment;
}

// If alignment is not a power of 2, the behavior is undefined.
uint64_t FORCEINLINE ALIGN_DOWN(uint64_t addr, uint64_t alignment)
{
    return addr & ~(alignment - 1);
}

void* malloc(size_t size);
void* realloc(void* block, size_t new);
void  free(void* block);