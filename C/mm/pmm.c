#include "pmm.h"

struct pmm {
    uint64_t* bitmap;
    uint64_t  total_frames;
    uint64_t  used_frames;
};

static struct pmm pmm;
extern char       kernel_end[];

bool pmm_init(multiboot_info_t* mbi)
{
    multiboot_memory_map_t* entry    = (multiboot_memory_map_t*)mbi->mmap_addr;
    size_t                  mmap_end = mbi->mmap_addr + mbi->mmap_length;

    while ((size_t)entry < mmap_end) {
        entry = (multiboot_memory_map_t*)((size_t)entry + entry->size + sizeof(entry->size));
    }

    // calculate the kernel's end address so we can place
    // our bitmaps there
    uint32_t* free = (uint32_t*)&kernel_end;

    return true;
}

void* pmm_alloc_page()
{
    return NULL;
}

void pmm_free_page(void* page)
{
}