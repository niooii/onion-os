SECTIONS
{
    . = 1M;

    .text : ALIGN(4096) {
        *(.text)
    }

    .rodata : ALIGN(4096) {
        *(.rodata)
    }

    .data : ALIGN(4096) {
        *(.data)
        *(.data.*)
    }

    .bss (NOLOAD) : ALIGN(4096) {
        *(COMMON)
        *(.bss)
    }
}