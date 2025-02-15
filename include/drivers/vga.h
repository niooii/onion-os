#pragma once

#include <def.h>

#define VGA_WIDTH  80
#define VGA_HEIGHT 25

void vga_print(const char* str);
void vga_putchar(const char c);
void vga_delchar();

void vga_clear();
// Activate or deactivate the blinking cursor.
void vga_cset(bool active);
// Set the cursor's position.
void vga_cpos(uint8_t x, uint8_t y);