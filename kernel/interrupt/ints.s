section .text

extern on_keypress
extern on_unimplemented

global int21h
global int_unimplemented

int21h:
    cli
    pushad
    call on_keypress
    popad
    sti
    iret

int_unimplemented:
    cli
    pushad
    call on_unimplemented
    popad
    sti
    iret