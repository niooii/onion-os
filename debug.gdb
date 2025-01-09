target remote | qemu-system-x86_64 -drive format=raw,file=build/os.bin,index=0,if=floppy -m 128M -S -gdb stdio

add-symbol-file build/ksymbols.o 0x1000
