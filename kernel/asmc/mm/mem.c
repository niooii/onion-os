#include <mm/mem.h>

void* memset(void* dest, i32 c, usize n)
{
    u8* d = (u8*)dest;

    for (usize i = 0; i < n; i++) {
        d[i] = (u8)c;
    }

    return dest;
}