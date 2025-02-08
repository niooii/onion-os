.PHONY: all clean run debug

# Directories
KERNEL_DIR = kernel
BUILD_DIR = build
INCLUDE_DIR = include

# Tools and flags
TOOLCHAIN_DIR = /usr/local/i386elfcc/bin
CC = $(TOOLCHAIN_DIR)/i386-elf-gcc
CFLAGS = -I$(INCLUDE_DIR) \
	-ffreestanding \
	-falign-jumps \
	-falign-functions \
	-falign-labels \
	-falign-loops \
	-fstrength-reduce \
	-fomit-frame-pointer \
	-finline-functions \
	-Wno-unused-functions \
	-fno-builtin \
	-Werror \
	-Wno-unused-label \
	-Wno-cpp \
	-Wno-unused-parameter \
	-nostdlib \
	-nostartfiles \
	-nodefaultlibs \
	-Wall \
	-O0 \
	-m32 \
	-g \
	-c \
	-mno-red-zone

ASM = nasm
ASMFLAGS = -f elf -g
ASMBIN_FLAGS = -f bin -g
LD = $(TOOLCHAIN_DIR)/i386-elf-ld
LDFLAGS = -T $(KERNEL_DIR)/linker.ld -nostdlib

KERNEL_C_SRCS := $(shell find $(KERNEL_DIR) -name '*.c')
KERNEL_ASM_SRCS := $(shell find $(KERNEL_DIR) -name '*.s')

KERNEL_C_OBJS := $(KERNEL_C_SRCS:$(KERNEL_DIR)/%.c=$(BUILD_DIR)/%.o)
KERNEL_ASM_OBJS := $(KERNEL_ASM_SRCS:$(KERNEL_DIR)/%.s=$(BUILD_DIR)/%.o)

ALL_OBJS = $(KERNEL_C_OBJS) $(KERNEL_ASM_OBJS)

# Rules start
all: $(BUILD_DIR)/os.bin

$(BUILD_DIR)/os.bin: $(BUILD_DIR)/boot.bin $(BUILD_DIR)/kernel.bin
	dd if=$(BUILD_DIR)/boot.bin >> $@
	dd if=$(BUILD_DIR)/kernel.bin >> $@
	dd if=/dev/zero bs=512 count=100 >> $@

$(BUILD_DIR)/boot.bin: loader/boot.s
	@mkdir -p $(dir $@)
	$(ASM) $(ASMBIN_FLAGS) $< -o $@

$(BUILD_DIR)/kernel.bin: $(ALL_OBJS) $(KERNEL_DIR)/linker.ld
	@mkdir -p $(dir $@)
	$(LD) -g -relocatable $(ALL_OBJS) -o $(BUILD_DIR)/ksymbols.o
	$(LD) $(LDFLAGS) $(BUILD_DIR)/ksymbols.o -o $@

$(BUILD_DIR)/%.o: $(KERNEL_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: $(KERNEL_DIR)/%.s
	@mkdir -p $(dir $@)
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf $(BUILD_DIR)

run: $(BUILD_DIR)/os.bin
	qemu-system-x86_64 -drive format=raw,file=$<,index=0,if=floppy -m 128M

debug: $(BUILD_DIR)/os.bin
	gdb -x debug.gdb