#include <kernel.h>
#include <oos/idt.h>
#include <oos/vga.h>
#include <oos/io/io.h>

extern void div_zero();
void kernel_main() 
{
    vga_print("Hello world..");

    idt_init();

    outb(0x60, 0xff);
    vga_print("PLUH?..");

    while (1);
}
