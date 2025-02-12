#pragma once

#include <stdint.h>
typedef unsigned int   size_t;
typedef unsigned char  uchar;
typedef unsigned short ushort;
#define bool  uint8_t
#define true  1
#define false 0

#define ASM           __asm__ volatile
#define CODE_SELECTOR 0x8
#define DATA_SELECTOR 0x10
