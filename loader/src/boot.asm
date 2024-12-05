mov ah, 0x0e
mov al, 'A'
mov bl, 32
for:
    cmp al, 'z'
    je done
    int 0x10
    add al, bl
    neg bl
    inc al
    jmp for

done:
    int 0x10
    jmp $

times 510-($-$$) db 0
db 0x55, 0xAA