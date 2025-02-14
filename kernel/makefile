TARGET = kernel
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
ENTRY_SRC := ./asmc/entry.s
C_SRCS := $(shell find asmc -name '*.c')
ASM_SRCS := $(shell find asmc -name '*.s' -not -name 'entry.s')

# Objects
ENTRY_OBJ := $(BUILD_DIR)/$(TARGET)/$(notdir $(ENTRY_SRC:.s=.o))
C_OBJS := $(patsubst asmc/%.c,$(BUILD_DIR)/$(TARGET)/%.o,$(C_SRCS))
ASM_OBJS := $(patsubst asmc/%.s,$(BUILD_DIR)/$(TARGET)/%.o,$(ASM_SRCS))

ALL_OBJS = $(ENTRY_OBJ) $(C_OBJS) $(ASM_OBJS)

.PHONY: all clean cargo_build

all: $(BUILD_DIR)/kernel.bin

$(BUILD_DIR)/kernel.bin: $(BUILD_DIR)/kernel.elf
	# extract binary
	$(OBJCOPY) -O binary $< $@

$(BUILD_DIR)/kernel.elf: linker.ld $(ALL_OBJS) $(BUILD_DIR)/liboos_kernel.a
	$(LD) -T linker.ld -nostdlib --build-id=none -Map=$(BUILD_DIR)/kernel.map $(ALL_OBJS) $(BUILD_DIR)/liboos_kernel.a -o $@

$(BUILD_DIR)/$(TARGET)/%.o: asmc/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET)/%.o: asmc/%.s
	@mkdir -p $(dir $@)
	$(ASM) $(ASMFLAGS) $< -o $@

$(BUILD_DIR)/liboos_kernel.a: cargo_build
	cp target/i686/debug/liboos_kernel.a $(BUILD_DIR)/liboos_kernel.a

cargo_build:
	cargo build

clean:
	rm -rf $(BUILD_DIR)/$(TARGET)
	cargo clean