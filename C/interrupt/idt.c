#include <idt.h>
#include <mm/mem.h>
#include <drivers/vga.h>
#include <drivers/keyboard.h>
#include <io.h>

struct idt_entry      entries[OOS_MAX_INTS];
struct idt_descriptor descriptor;

DECLARE_HW_INT(unimplemented);
DEFINE_HW_INT(unimplemented, {});

DECLARE_HW_INT(keypress);
DEFINE_HW_INT(keypress, {
    uint8_t sc = inb(0x60);
    handle_scancode(sc);
});

DECLARE_HW_INT(timer);
DEFINE_HW_INT(timer, {});

// TODO!
uint8_t mk_type_attr_int(enum GATE_TYPE gate_type)
{
    return 0;
}

void on_div_zero()
{
    vga_print("DIV ZERO??");
}

void idt_set(int i, void* addr)
{
    struct idt_entry* entry = &entries[i];
    entry->offset_low       = (uint32_t)addr & 0x0000ffff;
    entry->offset_high      = (uint32_t)addr >> 16;
    entry->selector         = CODE_SELECTOR;

    entry->gate_type   = GATE_TYPE_INT_32;
    entry->storage_seg = false;
    entry->dpl         = 3;
    entry->present     = 1;
}

void idt_init()
{
    memset(entries, 0, sizeof(entries));
    descriptor.limit = sizeof(entries) - 1;
    descriptor.base  = (uint32_t)entries;

    for (int i = 0; i < OOS_MAX_INTS; i++) {
        idt_set(i, unimplemented_iasm);
    }

    idt_set(0, on_div_zero);

    idt_set(0x20, timer_iasm);
    idt_set(0x21, keypress_iasm);
}

void idt_load()
{
    ASM("lidt %0" : : "m"(descriptor));
    enable_interrupts();
}

void disable_interrupts()
{
    ASM("cli");
}

void enable_interrupts()
{
    ASM("sti");
}