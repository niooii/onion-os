#include <kernel.h>
volatile char* cursor_pos = (volatile char*)0xb8000;

void kernel_main() {
    // volatile char* cursor_pos = (volatile char*)0xb8000;
    print("Hello FROMAasWF KERNEL YIPPEEEE");
    print(" hello again");
    print(" hello again");
    print(" hello again");
    print(" hello again");
    print(" hello again");
    
    while (1);
}

void print(const char* str) {
    while (*str) {
        *cursor_pos++ = *str++;
        *cursor_pos++ = 0x0f; 
    }
}