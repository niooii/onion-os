#include <idt.h>
#include <drivers/vga.h>

extern void kernel_main();

void k_centry()
{
    vga_cset(true);
    vga_print("Hello world..");

    idt_init();
    idt_load();
    for (unsigned long long i = 0; i < 400000000; i++)
        ;

    // call the rust kernel main
    kernel_main();
}