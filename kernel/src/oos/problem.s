[BITS 32]
global div_zero

section .asm
    div_zero:
        mov eax, 0
        div eax

        jmp $