ENTRY(kernel_main)
OUTPUT_FORMAT(binary)
SECTIONS
{
    . = 0x1000;
    .text : ALIGN(16) {
        *(.text)
    }
    .data : ALIGN(16) {
        *(.data)
    }
    .bss : ALIGN(16) {
        *(.bss)
    }
}