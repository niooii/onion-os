// Doesn't work when declared globally.. interesting
// volatile char* cursor_pos = (volatile char*)0xb8000;

void print(const char* str);

void main() {
    volatile char* cursor_pos = (volatile char*)0xb8000;
    const char *str = "Hello FROMAWF KERNEL YIPPEEEE";
    while (*str) {
        *cursor_pos++ = *str++;
        *cursor_pos++ = 0x0f; 
    }
    while (1);
}

void print(const char* str) {
    
}