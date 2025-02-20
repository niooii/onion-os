#include <idt.h>
#include <drivers/vga.h>
#include <multiboot.h>
#include "mm/pmm.h"

extern void kernel_main();

void kinit(uint32_t magic, struct multiboot_info* mbi)
{
    vga_clear();
    vga_cset(true);

    if (magic != 0x2BADB002) {
        vga_println("OS was not booted by a multiboot 1 compliant bootloader, stop.");
        return;
    }

    if (!(mbi->flags & MULTIBOOT_INFO_MEM_MAP)) {
        vga_println("Failed to obtain memory map, stop.");
        return;
    }

    vga_println("Init memory.");
    if (!pmm_init(mbi))
        return;
    vga_println("Finish.");
    // framebuffer stuff later

    idt_init();
    idt_load();

    kernel_main();
}