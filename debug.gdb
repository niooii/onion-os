target remote | qemu-system-i386 -hda build/kernel.elf -S -gdb stdio
set disassembly-flavor intel
add-symbol-file build/kernel.elf 0x100000
