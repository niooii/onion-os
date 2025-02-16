#pragma once
#include <def.h>

// TODO! try to optimize
void* memset(void* dest, int c, size_t n);
// Handles overlapping regions.
void* memmove(void* dest, const void* src, size_t n);
// Copying into an overlapping region is undefined behavior.
void* memcpy(void* dest, const void* src, size_t n);