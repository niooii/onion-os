[org 0x7c00]

KERNEL_LOC equ 0x1000
; set offset constants
CODE_SEG equ code_descriptor - GDT_START
DATA_SEG equ data_descriptor - GDT_START

BOOT_DISK: db 0
mov [BOOT_DISK], dl

; stack stuff
mov bp, 0x8000
mov sp, bp

mov bx, readingDiskMsg
call printBios

xor ax, ax
; zero segment registers
mov es, ax
mov ds, ax

mov bx, KERNEL_LOC
mov ah, 0x02 ; read sectors
mov al, 4    ; num to read
mov ch, 0x00 ; cylinder num
mov dh, 0x00 ; head num
mov cl, 0x02 ; start sector num (from 1)
mov dl, [BOOT_DISK] ; drive num
int 0x13

jnc disk_read_done

disk_error:
    mov bx, diskReadErrorMsg
    call printBios
    jmp $

disk_read_done:
    mov bx, enteringProtectedMsg
    call printBios

; clear screen
mov ah, 0x0
mov al, 0x3
int 0x10
; protected mode stuff
cli
lgdt [GDT_Descriptor]
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
    ; setup segments and the stack
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ebp, 0x90000
    mov esp, ebp
    jmp KERNEL_LOC

    cli
    hlt
    jmp $

    
enteringProtectedMsg:
    db "Entering protected mode...", 0

readingDiskMsg:
    db "Reading disk...", 0

diskReadErrorMsg:
    db "Disk read failed!", 0

times 510-($-$$) db 0
db 0x55, 0xAA