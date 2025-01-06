[org 0x7c00]

KERNEL_LOC equ 0x1000

BOOT_DISK: db 0
mov [BOOT_DISK], dl

mov bx, readingDiskMsg
call printBios



mov bx, enteringProtectedMsg
call printBios

; set offset constants
CODE_SEG equ code_descriptor - GDT_START
DATA_SEG equ data_descriptor - GDT_START

cli
lgdt [GDT_Descriptor]
; set cr0 to 1
mov eax, cr0
or eax, 1
mov cr0, eax
jmp CODE_SEG:start_protected_mode

printBios: ; string ptr should be in bx register
    push bx
    push ax
    mov ah, 0x0e

pb_loop:
    mov al, [bx]
    cmp al, 0
    je pb_done
    int 0x10
    inc bx
    jmp pb_loop

pb_done:
    mov al, 0xa ; newline
    int 0x10
    mov al, 0xd ; carriage return
    int 0x10
    pop ax
    pop bx

    ret

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
    dd GDT_START

[bits 32]
start_protected_mode:
    mov al, 'A'
    mov ah, 0x0f
    mov [0xb8000], ax
    jmp $

enteringProtectedMsg:
    db "Entering protected mode...", 0

readingDiskMsg:
    db " Reading disk...", 0

times 510-($-$$) db 0
db 0x55, 0xAA