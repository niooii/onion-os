# BUILD_DIR = ../build

# ASM = nasm
# ASMFLAGS = -f elf -g
# LD = $(TOOLCHAIN_DIR)/i386-elf-ld
# LDFLAGS = -T linker.ld -nostdlib

# # Source files
# LOADER_ASM_SRCS := $(shell find . -name '*.s')
# LOADER_ASM_OBJS := $(LOADER_ASM_SRCS:./%.s=$(BUILD_DIR)/loader/%.o)
# ALL_OBJS = $(LOADER_C_OBJS) $(LOADER_ASM_OBJS)

# .PHONY: all clean

# all: $(BUILD_DIR)/loader.bin

# $(BUILD_DIR)/loader.bin: $(ALL_OBJS) linker.ld
# 	@mkdir -p $(BUILD_DIR)
# 	$(LD) -g -relocatable $(ALL_OBJS) -o $(BUILD_DIR)/loader_symbols.o
# 	$(LD) $(LDFLAGS) $(BUILD_DIR)/loader_symbols.o -o $@

# $(BUILD_DIR)/loader/%.o: %.s
# 	@mkdir -p $(dir $@)
# 	$(ASM) $(ASMFLAGS) $< -o $@

# clean:
# 	rm -f $(BUILD_DIR)/loader.bin $(BUILD_DIR)/ksymbols.o
# 	rm -rf $(BUILD_DIR)/loader

# im aboutta fucking tweak oiut

BUILD_DIR = ../build

ASM = nasm
ASMBIN_FLAGS = -f bin -g

.PHONY: all clean

all: $(BUILD_DIR)/loader.bin

$(BUILD_DIR)/loader.bin: boot.s
	@mkdir -p $(dir $@)
	$(ASM) $(ASMBIN_FLAGS) $< -o $@