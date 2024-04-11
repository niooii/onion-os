ORG 0x7c00 ; ORG 0
BITS 16

start:
    cli ; clear interrupt
    ; setup memory segmentation and descriptor table
    ; segment size
    mov di, 0x77CC

    sti ; enable interrupt handling

    mov si, message
    call print
    jmp $

print:
    ; bios print combo
    mov ah, 0eh
    mov bx, 0
.loop:
    lodsb
    cmp al, 0
    je .done
    call print_char
    jmp .loop

.done:
    ret

print_char:
    int 0x10
    ret

message: db 'Hello World!'

times 510-($ - $$) db 0
dw 0xAA55

