section .text

extern int21_handler

global int21h

extern int21h:
    cli
    pushad
    call int21_handler
    popad
    sti
    iret