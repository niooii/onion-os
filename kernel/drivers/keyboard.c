#include <drivers/keyboard.h>
#include <drivers/vga.h>

void handle_scancode(uint8_t sc) 
{
    vga_putchar(sc);
}