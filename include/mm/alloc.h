#pragma once

#include <def.h>

void* malloc(size_t size);
void* realloc(void* block, size_t new);
void  free(void* block);