#include <drivers/vga.h>
#include <io.h>
volatile char* cursor_pos = (volatile char*)0xb8000;

void vga_print(const char* str) 
{
    while (*str) 
    {
        *cursor_pos++ = *str++;
        *cursor_pos++ = 0x0f; 
    }
}

void vga_putchar(const char c) 
{
    *cursor_pos++ = c;
    *cursor_pos++ = 0x0f; 
}

void vga_set_cursor(bool active)
{
    if (active) 
    {
        outb(0x3D4, 0x0A);
        outb(0x3D5, (insb(0x3D5) & 0xC0) | 0);

        outb(0x3D4, 0x0B);
        outb(0x3D5, (insb(0x3D5) & 0xE0) | 15);
    } 
    else 
    {

    }
}
