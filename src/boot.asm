ORG 0
BITS 16

_start:
    jmp short fakestart
    nop

; some empty space so the bios can override some shit and not MY shit
times 33 db 0

fakestart:
    jmp 0x7c0:start

start:
    cli ; clear interrupt
    mov ax, 0x7c0
    mov ds, ax ; cannot directly move a value into segment registers
    mov es, ax
    mov ax, 0x00
    mov ss, ax
    mov sp, 0x7c00 ; sp grows downwards 
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

