%ifndef SHARED_INC 
%define SHARED_INC

KERNEL_LOC equ 0x100000
STAGE2_LOCATION equ 0x7e00

CODE_SEG equ code_descriptor - GDT_START
DATA_SEG equ data_descriptor - GDT_START

section .data.gdt  
GDT_START:
    null_descriptor:
        dd 0
        dd 0 ; 8 bytes for empty descriptor
    code_descriptor:
        dw 0xffff ; first 16 bits of limit (0xfffff)

        dw 0
        db 0 ; first 24 bits of base (0)
        ; present, privilige, type, then type flags (1001 1010)
        db 0b10011010
        ; last 4 bits of flags and last 4 bits of limit
        db 0b11001111
        db 0 ; last 8 bits of base
    data_descriptor:
        dw 0xffff ; first 16 bits of limit (0xfffff)

        dw 0
        db 0 ; first 24 bits of base (0)
        ; present, privilige, type, then type flags (1001 0010)
        db 0b10010010
        ; last 4 bits of flags and last 4 bits of limit
        db 0b11001111
        db 0 ; last 8 bits of base
GDT_END:

GDT_Descriptor:
    dw GDT_END - GDT_START - 1 ; gdt size
%endif