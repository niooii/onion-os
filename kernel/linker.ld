ENTRY(kernel_main)
OUTPUT_FORMAT(binary)
SECTIONS
{
    . = 0x1000;
    .text : ALIGN(16) {
        *(.text.kernel_main)
        *(.text)
    }
    .rodata ALIGN(16) : {
        *(.rodata*)
    }
    .data ALIGN(16) : {
        *(.data*)
    }
    .bss ALIGN(16) : {
        *(COMMON)
        *(.bss*)
    }
    .asm ALIGN(16) : {
        *(.asm)
    }
}