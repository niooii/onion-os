#include <drivers/vga.h>
#include <io.h>

static volatile uint16_t* cpos = (uint16_t*)0xB8000;

static inline void set_cpos_current()
{
    size_t offset = ((size_t)cpos - 0xB8000) / 2;
    vga_cpos(offset % VGA_WIDTH, offset / VGA_WIDTH);
}

void vga_clear()
{
    for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        cpos[i] = 0x0;
    }
}

void vga_print(const char* str)
{
    unsigned char col = 0x0f;
    while (*str) {
        *cpos++ = (col << 8 | (*str++));
    }
    set_cpos_current();
}

void vga_putchar(const char c)
{
    unsigned char col = 0x0f;
    *cpos++           = (col << 8) | c;
    set_cpos_current();
}

void vga_delchar()
{
    if ((size_t)cpos > 0xB8000) {
        // TODO! order matters for the cursor apparently
        *--cpos = 0x0;
        // *cpos-- = 0x0;
        set_cpos_current();
    }
}

void vga_cset(bool active)
{
    if (active) {
        outb(0x3D4, 0x0A);
        outb(0x3D5, (inb(0x3D5) & 0xC0) | 0);

        outb(0x3D4, 0x0B);
        outb(0x3D5, (inb(0x3D5) & 0xE0) | 15);
    } else {
        outb(0x3D4, 0x0A);
        outb(0x3D5, 0x20);
    }
}

void vga_cpos(unsigned char x, unsigned char y)
{
    uint16_t pos = y * VGA_WIDTH + x;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char)((pos >> 8) & 0xFF));
}