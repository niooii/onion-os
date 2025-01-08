// kernel.c
void kernel_main(); 

void _start() {
    kernel_main();
}

void kernel_main() {
    volatile char *video_memory = (volatile char *)0xb8000;
    const char *message = "Hello FROM KERNEL YIPPEEEE";
    while (*message) {
        *video_memory++ = *message++;
        *video_memory++ = 0x0f; 
    }

    while (1);
}