#include <stdint.h>
#include <def.h>

#define OOS_MAX_INTS 512

enum GATE_TYPE {
    GATE_TYPE_TASK_32 = 0x5,
    GATE_TYPE_INT_16 = 0x6,
    GATE_TYPE_TRAP_16 = 0x7,
    GATE_TYPE_INT_32 = 0xE,
    GATE_TYPE_TRAP_32 = 0xF
};

struct idt_entry {
    uint16_t offset_low;    // lower 16 bits of handler address
    uint16_t selector;      // kernel segment selector
    uint8_t zero;           // unused
    uint8_t type_attr;      // type and attributes
    uint16_t offset_high;   // upper 16 bits of handler address
} __attribute__((packed));

struct idt_descriptor {
    uint16_t limit;        // size of IDT - 1
    uint32_t base;         // base address of IDT
} __attribute__((packed));

void idt_set(int i, void* addr);
void idt_init();