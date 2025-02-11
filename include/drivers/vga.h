#pragma once

#include <def.h>

#define VGA_WIDTH  80
#define VGA_HEIGHT 25

void vga_print(const char* str);
void vga_putchar(const char c);

void vga_set_cursor(bool active);