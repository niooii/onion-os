#include <kernel.h>
#include <idt.h>
#include <vga.h>
#include <io.h>

extern void div_zero();
void kernel_main() 
{
    vga_print("Hello world..");

    idt_init();
    // div_zero();

    for (int i = 0; i < 200; i++) {
        vga_print("a ");
    }

    while (1);
}
