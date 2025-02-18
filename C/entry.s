[BITS 32]

; stupid multiboot2 stuff
MULTIBOOT_MAGIC    equ  0x1BADB002
; bit 1 aligns stuff on pages, bit 2 requests mem info, 
; bit 12 requests video and framebuffer info
MULTIBOOT_FLAGS equ (1 << 1) | (1 << 2) | (1 << 12)
MULTIBOOT_CHECKSUM equ  -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)  ; checksum

section .multiboot
align 4 
multiboot_header:
    dd MULTIBOOT_MAGIC 
    dd MULTIBOOT_FLAGS   
    dd MULTIBOOT_CHECKSUM  

extern c_entry
CODE_SEG equ 0x8 
DATA_SEG equ 0x10 

global entry

entry:
    ; setup segments and the stack
    ; multiboot spec guarentees this
    ; mov ax, DATA_SEG
    ; mov ds, ax
    ; mov ss, ax
    ; mov es, ax
    ; mov fs, ax
    ; mov gs, ax

    ; fast a20 gate thing
    ; multiboot spec also guarentees this
    ; in al, 0x92 
    ; or al, 2
    ; out 0x92, al

    mov ebp, 0x90000
    and ebp, 0xFFFFFFF0
    mov esp, ebp

    push ebx ; multiboot info struct pointer
    push eax  ; 0x2BADB002
    ; map master PIC
    mov al, 00010001b
    out 0x20, al
    mov al, 0x20 ; master ISR start at 0x20
    out 0x21, al

    mov al, 00000001b
    out 0x21, al

    call c_entry

    hlt
    jmp $

times 512-($ - $$) db 0