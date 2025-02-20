#pragma once

#include <def.h>
#include <multiboot.h>

// TODO! concurrency safety

// Initialize with the multiboot memory map.
// Returns false if failed for whatever reason.
bool pmm_init(multiboot_info_t* mboot_info);
// Allocate a single page
void* pmm_alloc_frame();
// Free a single page
void pmm_free_frame(void* page);