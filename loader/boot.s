ORG 0x7c00
BITS 16

KERNEL_LOC equ 0x100000
; set offset constants
CODE_SEG equ code_descriptor - GDT_START
DATA_SEG equ data_descriptor - GDT_START

jmp short start
nop
times 33 db 0  

start:
cli

; zero segment registers
xor ax, ax
mov ds, ax
mov es, ax
mov ss, ax
; stack stuff
mov bp, 0x7c00
mov sp, bp

; clear screen
mov ah, 0x0
mov al, 0x3
int 0x10

; TODO! read sector to location of stage2
mov ah, 0x2 ; command - read from drive
; apparently its set to the drive pc was booted from when system starts
; mov dl, 0x80 ; drive - 0x80 is first hda
mov al, 8, ; sectors to read
mov ch, 0, ; from cylinder 0
mov cl, 2 ; sector 2
mov dh, 0, ; head
; es is 0.
mov bx, stage2 ; load to address of stage2
int 0x13

jmp stage2

; boot header
times 510-($-$$) db 0
db 0x55, 0xAA

; we need to calculate where stage2 ends so we can start reading from hte correct sector
; when loading the kernel.
STAGE2_SIZE equ (stage2_end - stage2)
; rounded up integer division to calc how many sectors stage2 takes up
STAGE2_SECTORS equ (STAGE2_SIZE + 512 - 1) / 512
KERNEL_START_SECTOR equ STAGE2_SECTORS + 1

stage2:
; protected mode stuff
lgdt [GDT_Descriptor]
mov eax, cr0
or eax, 1
mov cr0, eax
jmp CODE_SEG:start_protected_mode

; TODO! port from real mode lol
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
    mov eax, KERNEL_START_SECTOR
    mov ecx, 50000
    mov edi, KERNEL_LOC
    call ata_lba_read
    jmp CODE_SEG:KERNEL_LOC

    cli
    hlt
    jmp $

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

stage2_end:

align 512