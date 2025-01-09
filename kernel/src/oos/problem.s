[BITS 32]
global div_zero

section .text
    div_zero:
        mov eax, 0xDEADBEEF
        mov ebx, 0
        div ebx
        ret