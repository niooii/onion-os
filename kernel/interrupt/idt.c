#include <idt.h>
#include <mem.h>
#include <vga.h>
#include <io.h>

struct idt_entry entries[OOS_INTS_MAX];
struct idt_descriptor descriptor;

extern void int21h();

void on_keypress()
{
    vga_print("BLUH bluh ");
    // outb(0x20, 0x20);
    vga_print("finishh bluh");
}

// TODO!
uint8_t mk_type_attr_int(enum GATE_TYPE gate_type)
{
    return 0;
}

void divide_zero_err() {
    vga_print("DIV ZERO??");
}

void idt_set(int i, void* addr) 
{
    struct idt_entry* entry = &entries[i];
    entry->offset_low = (uint32_t) addr & 0x0000ffff;
    entry->offset_high = (uint32_t) addr >> 16;
    entry->selector = CODE_SELECTOR;
    entry->type_attr = 0xEE;
}

void idt_init() 
{
    memset(entries, 0, sizeof(entries));
    descriptor.limit = sizeof(entries) - 1;
    descriptor.base = (uint32_t) entries;

    idt_set(0, divide_zero_err);
    idt_set(0x20, on_keypress);
    idt_set(0x21, on_keypress);

    // load idt
    ASM("lidt %0" : : "m"(descriptor));
}