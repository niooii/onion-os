#include <kernel.h>
#include <oos/idt.h>
#include <oos/vga.h>
#include <oos/io/io.h>

extern void div_zero();
void kernel_main() 
{
    vga_print("Hello world..");

    idt_init();
    // div_zero();

    // outb(0x60, 0xff);
    for (int i = 0; i < 200; i++) {
        vga_print("a ");
    }

    while (1);
}
