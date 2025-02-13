#include <kernel.h>
#include <idt.h>
#include <drivers/vga.h>
#include <io.h>

extern void div_zero();

void kernel_main()
{
    vga_print("Hello world..");

    idt_init();

    idt_load();

    while (1) {
    }
}
