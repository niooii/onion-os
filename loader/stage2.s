%include "consts.inc"

section .text

BITS 16

cli
xor ax, ax
mov ds, ax
mov es, ax
mov ss, ax
mov bp, 0x9000
mov sp, bp

mov ah, 0x0e
mov al, 'B'
int 0x10

; do some physical memory stuff
; protected mode stuff
lgdt [GDT_Descriptor]
mov eax, cr0
or eax, 1
mov cr0, eax
    ; jmp $ < for testing
jmp dword CODE_SEG:start_protected_mode

[bits 32]
start_protected_mode:
    jmp $
    mov eax, 2
    mov ecx, 100
    mov edi, KERNEL_LOC
    call ata_lba_read
    jmp CODE_SEG:KERNEL_LOC

    cli
    hlt
    jmp $

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

; HATE. LET ME TELL YOU HOW MUCH I'VE COME TO HATE YOU, SINCE I'VE BEGAN TO LIVE.
ata_lba_read:
    mov ebx, eax,
    shr eax, 24
    or eax, 0xE0 
    mov dx, 0x1F6
    out dx, al

    mov eax, ecx
    mov dx, 0x1F2
    out dx, al

    mov eax, ebx
    mov dx, 0x1F3
    out dx, al

    mov dx, 0x1F4
    mov eax, ebx
    shr eax, 8
    out dx, al

    mov dx, 0x1F5
    mov eax, ebx 
    shr eax, 16
    out dx, al

    mov dx, 0x1f7
    mov al, 0x20
    out dx, al

.next_sector:
    push ecx

.try_again:
    mov dx, 0x1f7
    in al, dx
    test al, 8
    jz .try_again

    mov ecx, 256
    mov dx, 0x1F0
    rep insw
    pop ecx
    loop .next_sector
    ret