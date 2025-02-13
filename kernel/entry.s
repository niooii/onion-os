[BITS 32]

extern kernel_main
CODE_SEG equ 0x8 
DATA_SEG equ 0x10 

global entry

entry:
    ; setup segments and the stack
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ebp, 0x90000
    mov esp, ebp

    ; fast a20 gate thing
    in al, 0x92 
    or al, 2
    out 0x92, al

    ; map master PIC
    mov al, 00010001b
    out 0x20, al
    mov al, 0x20 ; master ISR start at 0x20
    out 0x21, al

    mov al, 00000001b
    out 0x21, al

    sti
    call kernel_main

    jmp $

; stupid alignment issues
times 512-($ - $$) db 0