BUILD_DIR = ../build
INCLUDE_DIR = ../include

# Tools and flags
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
LD = $(TOOLCHAIN_DIR)/i386-elf-ld
LDFLAGS = -T linker.ld -nostdlib

# Source files
KERNEL_C_SRCS := $(shell find . -name '*.c')
KERNEL_ASM_SRCS := $(shell find . -name '*.s')
KERNEL_C_OBJS := $(KERNEL_C_SRCS:./%.c=$(BUILD_DIR)/kernel/%.o)
KERNEL_ASM_OBJS := $(KERNEL_ASM_SRCS:./%.s=$(BUILD_DIR)/kernel/%.o)
ALL_OBJS = $(KERNEL_C_OBJS) $(KERNEL_ASM_OBJS)

.PHONY: all clean

all: $(BUILD_DIR)/kernel.bin

$(BUILD_DIR)/kernel.bin: $(ALL_OBJS) linker.ld
	@mkdir -p $(BUILD_DIR)
	$(LD) -g -relocatable $(ALL_OBJS) -o $(BUILD_DIR)/ksymbols.o
	$(LD) $(LDFLAGS) $(BUILD_DIR)/ksymbols.o -o $@

$(BUILD_DIR)/kernel/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/kernel/%.o: %.s
	@mkdir -p $(dir $@)
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -f $(BUILD_DIR)/kernel.bin $(BUILD_DIR)/ksymbols.o
	rm -rf $(BUILD_DIR)/kernel
