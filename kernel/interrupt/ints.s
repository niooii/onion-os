section .text

%macro NEW_HW_INT 1
global %1%+_iasm
extern %1%+_ihandler
%1%+_iasm:
    cli
    pushad
    call %1%+_ihandler
    popad
    sti
    iret
%endmacro

NEW_HW_INT timer
NEW_HW_INT keypress
NEW_HW_INT unimplemented
