#pragma once

#include <stddef.h>
#include <stdint.h>

typedef uint8_t bool;

#define true          1
#define false         0
#define ASM           __asm__ volatile
#define CODE_SELECTOR 0x8
#define DATA_SELECTOR 0x10

struct test_thing {
    int field;
};