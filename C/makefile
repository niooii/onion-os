TARGET = ckernel
BUILD_DIR = ../build
INCLUDE_DIR = ../include

CC = $(TOOLCHAIN_DIR)/i686-elf-gcc
OBJCOPY = $(TOOLCHAIN_DIR)/i686-elf-objcopy
CFLAGS = -I$(INCLUDE_DIR) \
 -ffreestanding \
 -falign-jumps \
 -falign-functions \
 -falign-labels \
 -falign-loops \
 -fstrength-reduce \
 -finline-functions \
 -fdata-sections \
 -fdata-sections \
 -ffunction-sections \
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

# Source files
ENTRY_SRC := ./entry.s
C_SRCS := $(shell find . -name '*.c')
ASM_SRCS := $(shell find . -name '*.s' -not -name 'entry.s')

# Objects
ENTRY_OBJ := $(ENTRY_SRC:./%.s=$(BUILD_DIR)/$(TARGET)/%.s.o)
C_OBJS := $(C_SRCS:./%.c=$(BUILD_DIR)/$(TARGET)/%.c.o)
ASM_OBJS := $(ASM_SRCS:./%.s=$(BUILD_DIR)/$(TARGET)/%.s.o)

ALL_OBJS = $(ENTRY_OBJ) $(C_OBJS) $(ASM_OBJS)

.PHONY: all clean

all: $(BUILD_DIR)/cobjs.o

$(BUILD_DIR)/cobjs.o: $(ALL_OBJS)
	$(LD) -g -relocatable $(ALL_OBJS) -o $@

$(BUILD_DIR)/$(TARGET)/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET)/%.s.o: %.s
	@mkdir -p $(dir $@)
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf $(BUILD_DIR)/$(TARGET)