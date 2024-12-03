.POSIX:
.PHONY: all clean

SOURCE = loader.c
TARGET = BOOTX64.EFI

CC = clang \
	-target x86_64-unknown-windows \
	-fuse-ld=lld-link \
	-Wl,-subsystem:efi_application \
	-Wl,-entry:efi_main

CFLAGS = \
	-std=c17 \
	-I/usr/include/efi/  \
	-Wall \
	-Wextra \
	-Wpedantic \
	-mno-red-zone \
	-ffreestanding \
	-nostdlib 

all: $(TARGET)
	

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $@ $<
	mkdir -p ./build/EFI/BOOT/
	mv $(TARGET) ./build/EFI/BOOT/

clean:
	rm -rf $(TARGET)
