#include <kernel.h>
#include <oos/idt.h>
#include <oos/vga.h>

extern void div_zero();
void kernel_main() 
{
    vga_print("Hello world..");

    idt_init();

    // TODO! THIS DOTN WORK!! infinite loop and stuff..
    div_zero();

    while (1);
}
