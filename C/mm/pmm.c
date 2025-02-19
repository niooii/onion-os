#include <mm/alloc.h>
#include <mm/mem.h>

#include "pmm.h"

#define FRAME_SIZE     0x1000
#define FRAME_FREE_BIT 1
#define FRAME_USED_BIT 0

struct pmm {
    /*
     * OPT! a linear search through this will inevitably become quite slow.
     * we should maybe use a secondary bitmap where every bit corresponds to
     * one uint64_t in the original bitmap, and shows whether it has a free
     * frame or not for O(log(n))
     */
    uint64_t* bitmap;
    // The address where the bitmap starts logically representing frames
    uint64_t start_addr;
    /*
     * OPT! save where the last valid region of memory ends, then cut out map off there.
     * No point in looking past that region.
     */
    uint64_t total_frames;
    uint64_t used_frames;
};

static struct pmm pmm;
extern char       kernel_end[];

typedef multiboot_memory_map_t mm_entry;

/*
 * FATAL! this entire function is wrong lol
 * instead of incrementing, (beause multiboot does not guarentee each entry
 * describes sequential and contiguous memory relative to the previous), we
 * need to directly calculate the offset in the bitmap, and memset from there. the bitmap
 * is now guarenteed to contain everything. (BUT THERE MAY BE GAPS after the iterations,
 * these must be accounted for by setting those pages to FRAME_BIT_USED)
 */
bool pmm_init(multiboot_info_t* mbi)
{
    /*
     * Grab the kernel's end address so we can place
     * our bitmap there
     * BUG! What if there isnt enough memory after the kernel?
     * If the rest of the free region where the kernel is isn't large enough?
     * handle later
     */
    unsigned char* bm = (unsigned char*)(&kernel_end);
    pmm.bitmap        = (uint64_t*)bm;

    // The leftover bits from the last iteration of the loop
    // TODO! unused for now figure out nuanced implementation details
    uint32_t  prev_leftover = 0;
    bool      first         = true;
    mm_entry* entry         = (mm_entry*)mbi->mmap_addr;
    size_t    mmap_end      = mbi->mmap_addr + mbi->mmap_length;

    // BUG! does this miss/skip an entry by any chance??
    // i just fixed it but idk maybe its missing more
    while ((size_t)entry < mmap_end) {
        // Start and end are aligned to frame boundaries
        uint64_t start = ALIGN_UP(entry->addr, FRAME_SIZE);
        uint64_t end   = ALIGN_DOWN(start + entry->len, FRAME_SIZE);

        // too small, discard
        if (end <= start)
            goto next_entry;

        if (first) {
            first          = false;
            pmm.start_addr = start;
        }

        uint32_t num_frames = (end - start) >> __builtin_ctz(FRAME_SIZE);
        // divide by 8 bc 8 frames can be stored in 1 bit
        uint32_t bytes_to_use = num_frames >> 3;

        if (prev_leftover == 0) {
            uint32_t leftover = num_frames % 8;

            int status =
                entry->type == MULTIBOOT_MEMORY_AVAILABLE ? FRAME_FREE_BIT : FRAME_USED_BIT;

            // TODO! account for carry
            memset(bm, status, bytes_to_use);
            // account for carry here with some bit magic
            bm += bytes_to_use;
            prev_leftover = leftover;
        } else {
        }

        pmm.total_frames += num_frames;

    // TODO!
    next_entry:
        entry = (mm_entry*)((size_t)entry + entry->size + sizeof(entry->size));
    }

    // TODO! set the frames occupied by the frame bitmap to used

    return true;
}

void* pmm_alloc_page()
{
    return NULL;
}

void pmm_free_page(void* page)
{
}