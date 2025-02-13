target remote | qemu-system-i386 -hda build/os.bin -S -gdb stdio

add-symbol-file build/kernel.o 0x100000