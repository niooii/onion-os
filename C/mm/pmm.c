#include "pmm.h"

#define PAGE_SIZE 4096

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

    // calculate the kernel's end address so we can place
    // our bitmaps there
    uint64_t* bm = (uint64_t*)(&kernel_end);
    pmm.bitmap   = bm;

    while ((size_t)entry < mmap_end) {
        entry = (multiboot_memory_map_t*)((size_t)entry + entry->size + sizeof(entry->size));
        if (entry->type != MULTIBOOT_MEMORY_AVAILABLE)
            continue;
        uint64_t addr = entry->addr;
        uint64_t len  = entry->len;
        // TODO!
    }

    return true;
}

void* pmm_alloc_page()
{
    return NULL;
}

void pmm_free_page(void* page)
{
}