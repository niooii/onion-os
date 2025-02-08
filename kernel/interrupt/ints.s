section .text

extern on_keypress

global int21h

extern int21h:
    cli
    pushad
    call on_keypress
    popad
    sti
    iret