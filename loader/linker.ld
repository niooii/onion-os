OUTPUT_FORMAT("binary")
SECTIONS
{
    . = 0x7c00;
    .stage1 : {
        *(.text.stage1)
    }
    . = 0x7e00;
    .text : {
        *(.text)
    }
    .rodata : {
        *(.rodata)
    }
    .data : {
        *(.data)
    }
    .bss : {
        *(COMMON)
        *(.bss)
    }
}