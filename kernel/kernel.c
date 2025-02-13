#include <kernel.h>
#include <idt.h>
#include <drivers/vga.h>
#include <io.h>

void kernel_main()
{
    vga_cset(true);
    vga_print("Hello world..");

    idt_init();

    idt_load();

    while (1) {
    }
}
