#include <stdint.h>
typedef unsigned int size_t;
typedef unsigned char uchar;
typedef unsigned short ushort;

#define ASM __asm__ volatile
#define KERNEL_CODE_SELECTOR 0x8
#define KERNEL_DATA_SELECTOR 0x10
