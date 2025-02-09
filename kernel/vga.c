#include <drivers/vga.h>

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
