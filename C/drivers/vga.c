#include <drivers/vga.h>
#include <io.h>
#include <mm/mem.h>
#include <drivers/keyboard.h>

#define VGA_BASE                 0xB8000
#define VGA_WIDTH                80
#define VGA_HEIGHT               25
#define VGA_MAX_OFFSET           (80 * 25)
#define VGA_MAX_ADDR             (VGA_BASE) + VGA_MAX_OFFSET * 2
#define VGA_LAST_LINE_START_ADDR (VGA_MAX_ADDR - (VGA_WIDTH * 2));

static volatile uint16_t* cpos = (uint16_t*)VGA_BASE;

static inline void set_cpos_current()
{
    size_t offset = ((size_t)cpos - VGA_BASE) / 2;
    vga_cpos(offset % VGA_WIDTH, offset / VGA_WIDTH);
}

// Shifts the entire visible buffer upwards one line, overwriting the first line
void shift()
{
    // length of buffer minus one row
    const int n = (size_t)(VGA_MAX_OFFSET - VGA_WIDTH) * 2;
    // memmove the buffer from the second row to the start of the buffer
    memmove((void*)VGA_BASE, (void*)(VGA_BASE + (VGA_WIDTH * 2)), n);
    memset((void*)VGA_BASE + n, 0, n);
}

// Moves the cursor to the start of the next line
void newline()
{
    const int curr_row = (((size_t)cpos - VGA_BASE) / (VGA_WIDTH * 2));
    const int next_row = curr_row + 1;

    const uint16_t* new_pos = (const uint16_t*)(VGA_BASE + next_row * (VGA_WIDTH * 2));

    if ((int)new_pos >= VGA_MAX_ADDR) {
        shift();
        cpos = (uint16_t*)VGA_LAST_LINE_START_ADDR;
    } else {
        cpos = (uint16_t*)new_pos;
    }
}

void vga_clear()
{
    for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        cpos[i] = 0x0;
    }
}

// Horribly unoptimized but hopefully we wont have to use it for long
void vga_print(const char* str)
{
    while (*str) {
        vga_putchar(*str++);
    }
    set_cpos_current();
}

void vga_println(const char* str)
{
    vga_print(str);
    newline();
}

void vga_putchar(const char c)
{
    switch (c) {
    case ASCII_ENTER:
    case ASCII_NEWLINE:
        newline();
        return;
    case ASCII_BACKSPACE:
        vga_delchar();
        return;
    case ASCII_TAB:
        vga_print("    ");
        return;
    default:
    }

    unsigned char col = 0x0f;
    *cpos++           = (col << 8) | c;

    if ((int)cpos >= VGA_MAX_ADDR) {
        shift();
        cpos = (uint16_t*)VGA_LAST_LINE_START_ADDR;
    }
}

void vga_delchar()
{
    if ((size_t)cpos > VGA_BASE) {
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
