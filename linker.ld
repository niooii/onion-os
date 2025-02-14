ENTRY(entry)
OUTPUT_FORMAT(elf32-i386)
SECTIONS
{
    . = 1M;
    .text : ALIGN(4096) {
        *(.multiboot)   
        *(.text)
        *(.text.*)
    }

    .rodata : ALIGN(4096) {
        *(.rodata)
    }

    .data : ALIGN(4096) {
        *(.data)
        *(.data.*)
    }

    .bss : ALIGN(4096) {
        *(COMMON)
        *(.bss)
    }
}