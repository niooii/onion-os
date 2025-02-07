.POSIX:
.PHONY: all clean

SRCDIR = src
BUILDDIR = build
TARGET = onion_os.bin

CC = i386-elf-gcc \
	-Isrc \
	-Iinclude \
	-ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops \
	-fstrength-reduce -fomit-frame-pointer -finline-functions \
	-Wno-unused-functions -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter \
	-nostdlib -nostartfiles -nodefaultlibs -Wall \
	-O0 \
	-m32 \
	-g \
	-c \
	-mno-red-zone 
ASM = nasm -f elf -g 
LD = i386-elf-ld
LDFLAGS = -T linker.ld -nostdlib

ENTRY = entry.s
OOS_C_SOURCES = $(shell find src -name '*.c')
OOS_ASM_SOURCES = $(shell find src -name '*.s')

ENTRY_OBJ = $(BUILDDIR)/entry.o
OOS_C_OBJECTS = $(patsubst src/%.c,$(BUILDDIR)/%.c.o,$(OOS_C_SOURCES))
OOS_ASM_OBJECTS = $(patsubst src/%.s,$(BUILDDIR)/%.s.o,$(OOS_ASM_SOURCES))
ALL_OBJECTS = $(ENTRY_OBJ) $(OOS_C_OBJECTS) $(OOS_ASM_OBJECTS)

all: kernel.bin

kernel.bin: $(ALL_OBJECTS)
	$(LD) -g -relocatable $(ALL_OBJECTS) -o build/ksymbols.o
	$(LD) $(LDFLAGS) build/ksymbols.o -o $(BUILDDIR)/kernel.bin 

$(ENTRY_OBJ): $(ENTRY)
	mkdir -p $(dir $@)
	$(ASM) $< -o $@

$(BUILDDIR)/%.c.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $< -o $@

$(BUILDDIR)/%.s.o: src/%.s
	mkdir -p $(dir $@)
	$(ASM) $< -o $@

clean:
	rm -rf $(BUILDDIR)