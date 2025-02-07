extern kernel_main

global entry

entry:
    ; fast a20 gate thing
    in al, 0x92 
    or al, 2
    out 0x92, al
    ; map master PIC
    mov al, 00010001b
    out 0x20, al
    mov al, 0x20 ; master ISR start at 0x20
    out 0x21, al

    mov al, 00000001b
    out 0x21, al
    call kernel_main

