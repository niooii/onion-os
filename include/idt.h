#pragma once

#include <stdint.h>
#include <def.h>

#define OOS_MAX_INTS 512

enum GATE_TYPE {
    GATE_TYPE_TASK_32 = 0x5,
    GATE_TYPE_INT_16  = 0x6,
    GATE_TYPE_TRAP_16 = 0x7,
    GATE_TYPE_INT_32  = 0xE,
    GATE_TYPE_TRAP_32 = 0xF
};

// Declare a new hardware interrupt.
#define DECLARE_HW_INT(name) \
    void        name##_ihandler(); \
    extern void name##_iasm();

// Implement the new hardware interrupt.
#define DEFINE_HW_INT(name, code) \
    void name##_ihandler() \
    { \
        code outb(0x20, 0x20); \
    }

struct idt_entry {
    uint16_t offset_low; // lower 16 bits of handler address
    uint16_t selector;   // kernel segment selector
    uint8_t  zero;       // unused

    // amazing bit field syntax
    uint8_t gate_type   : 4;
    uint8_t storage_seg : 1;
    uint8_t dpl         : 2;
    uint8_t present     : 1;

    uint16_t offset_high; // upper 16 bits of handler address
} __attribute__((packed));

struct idt_descriptor {
    uint16_t limit; // size of IDT - 1
    uint32_t base;  // base address of IDT
} __attribute__((packed));

void do_thing(struct test_thing t);

void idt_set(int i, void* addr);
void idt_init();
void idt_load();

void disable_interrupts();
void enable_interrupts();