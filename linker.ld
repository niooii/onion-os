ENTRY(entry)
OUTPUT_FORMAT(elf32-i386)
SECTIONS
{
    . = 1M;
    
    .multiboot ALIGN(4096) : {
        KEEP(*(.multiboot))
    }
    
    .text ALIGN(4096) : {
        *(.text)
        *(.text.*)
    }

    .rodata ALIGN(4096) : {
        *(.rodata)
        *(.rodata.*)
    }

    .data ALIGN(4096) : {
        *(.data)
        *(.data.*)
    }

    .bss ALIGN(4096) : {
        *(.bss)
        *(.bss.*)
        *(COMMON)
    }

    kernel_end = .;
}