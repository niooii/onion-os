#include <idt.h>
#include <drivers/vga.h>

void cinit()
{
    vga_clear();
    vga_cset(true);
    vga_print("Hello world..");

    idt_init();
    idt_load();
}