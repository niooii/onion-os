%include "consts.inc"

section .text.stage1

BITS 16

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
mov bp, 0x9000
mov sp, bp

; clear screen
mov ah, 0x0
mov al, 0x3
int 0x10

xor ax, ax
mov es, ax
mov bx, STAGE2_LOCATION  
mov ah, 0x02       
mov al, 1        
mov ch, 0         
mov cl, 2      
mov dh, 0      
mov dl, 0x80    
int 0x13
jc disk_error     

; jump to second stage
jmp 0:STAGE2_LOCATION

disk_error:
    ; Add your error handling here
    cli
    hlt
    jmp $


times 510-($-$$) db 0
db 0x55, 0xAA