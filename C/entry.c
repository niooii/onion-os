#include <idt.h>
#include <drivers/vga.h>
#include <multiboot.h>

extern void kernel_main();

void c_entry(uint32_t magic, struct multiboot_info* mbi)
{
    if (magic != 0x2BADB002) {
        // tf
        return;
    }

    // TODO! setup paging
    // and possilby framebuffer

    vga_clear();
    vga_cset(true);

    idt_init();
    idt_load();

    kernel_main();
}