.POSIX:
.PHONY: all clean

SRCDIR = src
BUILDDIR = build
TARGET = onion_os.bin

CC = i386-elf-gcc \
	-ffreestanding \
	-m32 \
	-g \
	-c \
	-mno-red-zone 

LD = i386-elf-ld
LDFLAGS = --entry=main -nostdlib

KERNEL_SOURCES = $(wildcard src/*.c)
KERNEL_OBJECTS = $(patsubst src/%.c,$(BUILDDIR)/%.o,$(KERNEL_SOURCES))

all: kernel.bin

kernel.bin: $(KERNEL_OBJECTS)
	$(LD) -Ttext 0x1000 $(LDFLAGS) $(KERNEL_OBJECTS) -o $(BUILDDIR)/kernel.bin --oformat binary

$(BUILDDIR)/%.o: src/%.c
	mkdir -p $(BUILDDIR)
	$(CC) $< -o $@


clean:
	rm -rf $(BUILDDIR)
