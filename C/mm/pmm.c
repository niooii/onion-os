#include <mm/alloc.h>
#include <mm/mem.h>
#include <drivers/vga.h>
#include "pmm.h"

// Must be a power of 2
#define FRAME_SIZE        0x1000
#define FRAME_FREE_BIT    1
#define FRAME_USED_BIT    0
#define FRAME_NUM_INVALID UINT64_MAX

struct pmm {
    /*
     * OPT! a linear search through this will inevitably become quite slow.
     * we should maybe use a secondary bitmap where every bit corresponds to
     * one uint64_t in the original bitmap, and shows whether it has a free
     * frame or not for O(log(n))
     */
    uint64_t* bitmap;
    // The address where the bitmap starts logically representing frames
    // TODO! starts at 0 for now. This is unused.
    uint64_t start_addr;
    /*
     * OPT! save where the last valid region of memory ends, then cut out map off there.
     * No point in looking past that region.
     * ORRRR... also do that for the beginning and set the start addr accordingly.
     */
    // The total complete frames.
    uint64_t total_frames;
    uint64_t used_frames;
};

static struct pmm pmm;
extern char       kernel_end[];

typedef multiboot_memory_map_t mm_entry;

// Status must be either FRAME_FREE_BIT or FRAME_USED_BIT
// frame num 0 corresponds to the first bit in the bitmap
void set_frame_bit(uint64_t frame_num, int status)
{
    pmm.bitmap[frame_num >> 6] |= ((uint64_t)status << (frame_num % 64));
}

// Status must be either FRAME_FREE_BIT or FRAME_USED_BIT
// Start and end inclusive
void set_frame_bits(uint64_t start_frame, uint64_t end_frame, int status)
{
    if (start_frame > end_frame)
        return;

    uint64_t start_idx = start_frame >> 6;
    uint64_t end_idx   = end_frame >> 6;

    // if they are in the same bitmap element
    if (start_idx == end_idx) {
        uint64_t mask = 0;
        mask = ((1ULL << (end_frame % 64 - start_frame % 64 + 1)) - 1) << (start_frame % 64);

        if (status == FRAME_FREE_BIT)
            pmm.bitmap[start_idx] |= mask;
        else
            pmm.bitmap[start_idx] &= ~mask;

        return;
    }

    // for the first partial uint64_t
    {
        uint64_t mask = ~0ULL << (start_frame % 64);
        if (status == FRAME_FREE_BIT)
            pmm.bitmap[start_idx] |= mask;
        else
            pmm.bitmap[start_idx] &= ~mask;
    }

    // for all the complete elements
    for (uint64_t idx = start_idx + 1; idx < end_idx; idx++) {
        pmm.bitmap[idx] = (status == FRAME_FREE_BIT) ? ~0ULL : 0;
    }

    // for the end partial uint64_t
    {
        uint64_t mask = ~0ULL >> (63 - (end_frame % 64));
        if (status == FRAME_FREE_BIT)
            pmm.bitmap[start_idx] |= mask;
        else
            pmm.bitmap[start_idx] &= ~mask;
    }
}

// Returns the frame number. Returns FRAME_NUM_INVALID if nothing was found.
uint64_t first_free_frame()
{
    uint64_t i = 0;
    // round up the iteration count to handle the partially filled bitmap element
    // since it should be zeroed past the end anyways it should be fine.
    for (; i < (pmm.total_frames + 63) >> 6; i++) {
        // TODO! bro is this safe or nah idk
        // https://github.com/microsoft/compiler-rt/blob/master/lib/builtins/ffsdi2.c
        // holy shit
        uint64_t pos = __builtin_ffsll(pmm.bitmap[i]);
        if (pos != 0) {
            return (i * 64) + (pos - 1);
        }
    }

    return FRAME_NUM_INVALID;
}

bool pmm_init(multiboot_info_t* mbi)
{
    /*
     * Grab the kernel's end address so we can place
     * our bitmap there
     * BUG! What if there isnt enough memory after the kernel?
     * If the rest of the free region where the kernel is isn't large enough?
     * handle later
     */
    uint64_t* bm = (uint64_t*)(&kernel_end);
    pmm.bitmap   = bm;

    size_t mmap_end = mbi->mmap_addr + mbi->mmap_length;
    // End of memory (addr) according to the mem map entries
    uint64_t mem_end = 0;

    // BUG! does this miss/skip an entry by any chance??
    // i just fixed it but idk maybe its missing more
    // first run to find end address
    for (mm_entry* e = (mm_entry*)mbi->mmap_addr; (size_t)e < mmap_end;
         e           = (mm_entry*)((size_t)e + e->size + sizeof(e->size))) {
        uint64_t end = ALIGN_DOWN(e->addr + e->len, FRAME_SIZE);
        // find the end address
        // beyond this point there is NO COMPLETE FRAME.
        if (end > mem_end)
            mem_end = end;
    }
    // frame size trailing zeroes
    int ftz = __builtin_ctz(FRAME_SIZE);

    uint64_t num_frames = mem_end >> ftz;
    // divide by 64 bc 64 frames can be stored in 1 uint64_t (and also round up)
    uint64_t  bm_size = (num_frames + 63) >> 6;
    uint64_t* bm_end  = bm + bm_size;
    memset(bm, 0, (bm_end - bm) * sizeof(uint64_t));
    // second run to set bits
    for (mm_entry* e = (mm_entry*)mbi->mmap_addr; (size_t)e < mmap_end;
         e           = (mm_entry*)((size_t)e + e->size + sizeof(e->size))) {
        // Start and end are aligned to frame boundaries
        uint64_t start = ALIGN_UP(e->addr, FRAME_SIZE);
        uint64_t end   = ALIGN_DOWN(start + e->len, FRAME_SIZE);

        // either too small for our needs or not a good type
        if (end <= start || e->type != MULTIBOOT_MEMORY_AVAILABLE)
            continue;

        uint64_t start_frame = start >> ftz;
        uint64_t last_frame  = (end >> ftz) - 1;

        set_frame_bits(start_frame, last_frame, FRAME_FREE_BIT);
    }

    // TODO! set the frames occupied by the frame bitmap to used

    uint64_t first_free = first_free_frame();

    int iafasf = 0;

    return true;
}

void* pmm_alloc_frame()
{
    return NULL;
}

void pmm_free_frame(void* frame)
{
}