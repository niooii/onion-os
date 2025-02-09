#include <idt.h>
#include <mem.h>
#include <vga.h>
#include <io.h>

struct idt_entry entries[OOS_MAX_INTS];
struct idt_descriptor descriptor;

extern void int21h();
extern void int_unimplemented();

// TODO!
uint8_t mk_type_attr_int(enum GATE_TYPE gate_type)
{
    return 0;
}

void on_div_zero() {
    vga_print("DIV ZERO??");
}

void on_keypress()
{
    vga_print("BLUH bluh ");
    vga_print("finishh bluh");
    outb(0x20, 0x20);
}

void on_unimplemented()
{
    outb(0x20, 0x20);
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

    for (int i = 0; i < OOS_MAX_INTS; i++)
    {
        idt_set(i, int_unimplemented);
    }

    idt_set(0, on_div_zero);
    idt_set(0x21, int21h);

    // load idt
    ASM("lidt %0" : : "m"(descriptor));
    ASM("sti");
}