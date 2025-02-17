#include <idt.h>
#include <drivers/vga.h>
#include <multiboot.h>

extern void kernel_main();

void c_entry(uint32_t magic, struct multiboot_info* mbi)
{
    vga_clear();
    vga_cset(true);

    if (magic != 0x2BADB002) {
        vga_println("OS was not booted by a multiboot 1 compliant bootloader, stopping.");
        return;
    }

    if (!(mbi->flags & MULTIBOOT_BIT_MEM_MAP)) {
        vga_println("Failed to obtain memory map, stopping.");
        return;
    }

    uint64_t mem = (mbi->mem_upper << 32) | mbi->mem_lower;
    // framebuffer stuff later

    idt_init();
    idt_load();

    kernel_main();
}