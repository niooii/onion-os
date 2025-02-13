TARGET = kernel
BUILD_DIR = ../build
INCLUDE_DIR = ../include

# Tools and flags
CC = $(TOOLCHAIN_DIR)/i686-elf-gcc
CFLAGS = -I$(INCLUDE_DIR) \
	-ffreestanding \
	-falign-jumps \
	-falign-functions \
	-falign-labels \
	-falign-loops \
	-fstrength-reduce \
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
	-march=i686 \
	-g \
	-c \
	-mno-red-zone

ASM = nasm
ASMFLAGS = -f elf -g
LD = $(TOOLCHAIN_DIR)/i686-elf-ld
LDFLAGS = -T linker.ld -nostdlib

# Source files
ENTRY_SRC := ./entry.s
C_SRCS := $(shell find . -name '*.c')
ASM_SRCS := $(shell find . -name '*.s' -not -name 'entry.s')

ENTRY_OBJ := $(ENTRY_SRC:./%.s=$(BUILD_DIR)/$(TARGET)/%.o)
C_OBJS := $(C_SRCS:./%.c=$(BUILD_DIR)/$(TARGET)/%.o)
ASM_OBJS := $(ASM_SRCS:./%.s=$(BUILD_DIR)/$(TARGET)/%.o)
ALL_OBJS = $(ENTRY_OBJ) $(C_OBJS) $(ASM_OBJS)

.PHONY: all clean

all: $(BUILD_DIR)/kernel.o

$(BUILD_DIR)/kernel.o: $(ALL_OBJS) linker.ld
	@mkdir -p $(BUILD_DIR)
	$(LD) -static -g -relocatable $(ALL_OBJS) ../build/liboos_kernel.a -o $(BUILD_DIR)/kernel.o

$(BUILD_DIR)/$(TARGET)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET)/%.o: %.s
	@mkdir -p $(dir $@)
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -f $(BUILD_DIR)/kernel.bin $(BUILD_DIR)/ksymbols.o
	rm -rf $(BUILD_DIR)/kernel
