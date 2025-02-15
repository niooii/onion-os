TARGET = kernel
BUILD_DIR = ../build
INCLUDE_DIR = ../include

LD = $(TOOLCHAIN_DIR)/i686-elf-ld

ALL_OBJS = $(ENTRY_OBJ) $(C_OBJS) $(ASM_OBJS)

.PHONY: all clean cargo_build

KMAIN_LIB = $(BUILD_DIR)/$(TARGET)/liboos_kernel.a

all: $(KMAIN_LIB)

$(KMAIN_LIB): cargo_build
	cp target/i686/debug/liboos_kernel.a $(BUILD_DIR)/liboos_kernel.a

cargo_build:
	cargo build

clean:
	rm -rf $(BUILD_DIR)/$(TARGET)
	cargo clean