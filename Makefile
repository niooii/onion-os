bin:
	nasm -f bin src/boot.asm -o build/boot.bin

run_bin:
	qemu-system-x86_64 -hda build/boot.bin