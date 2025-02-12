target remote | qemu-system-x86_64 -hda build/os.bin -S -gdb stdio

add-symbol-file build/ksymbols.o 0x100000