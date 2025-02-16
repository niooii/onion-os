#include <mm/mem.h>

void* memset(void* dest, int c, size_t n)
{
    unsigned char* d = (unsigned char*)dest;

    for (size_t i = 0; i < n; i++) {
        d[i] = (unsigned char)c;
    }

    return dest;
}

void* memmove(void* dest, const void* src, size_t n)
{
    if (dest == src)
        return dest;

    unsigned char*       d = dest;
    const unsigned char* s = src;
    if (d < s) {
        while (n--) {
            *d++ = *s++;
        }
    } else {
        d += n;
        s += n;
        while (n--) {
            *d-- = *s--;
        }
    }
    return dest;
}

void* memcpy(void* dest, const void* src, size_t n)
{
    if (dest == src)
        return dest;

    unsigned char*       d = dest;
    const unsigned char* s = src;
    while (n--) {
        *d++ = *s++;
    }
    return dest;
}
