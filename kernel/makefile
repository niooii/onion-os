.POSIX:
.PHONY: all clean

SRCDIR = src
BUILDDIR = build
TARGET = onion_os.bin

CC = i386-elf-gcc \
	-Isrc \
	-ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops \
	-fstrength-reduce -fomit-frame-pointer -finline-functions \
	-Wno-unused-functions -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter \
	-nostdlib -nostartfiles -nodefaultlibs -Wall \
	-O0 \
	-m32 \
	-g \
	-c \
	-mno-red-zone 

LD = i386-elf-ld
LDFLAGS = -T linker.ld -nostdlib

KERNEL_SOURCES = $(wildcard src/*.c)
KERNEL_OBJECTS = $(patsubst src/%.c,$(BUILDDIR)/%.o,$(KERNEL_SOURCES))

all: kernel.bin

kernel.bin: $(KERNEL_OBJECTS)
	$(LD) $(LDFLAGS) $(KERNEL_OBJECTS) -o $(BUILDDIR)/kernel.bin

$(BUILDDIR)/%.o: src/%.c
	mkdir -p $(BUILDDIR)
	$(CC) $< -o $@


clean:
	rm -rf $(BUILDDIR)
