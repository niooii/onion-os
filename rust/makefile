BUILD_DIR = ../build

.PHONY: all clean cargo_build

all: $(BUILD_DIR)/liboos_kernel.a

$(BUILD_DIR)/liboos_kernel.a: cargo_build
	cp target/i686-elf/debug/liboos_kernel.a $(BUILD_DIR)/liboos_kernel.a

cargo_build: 
	cargo build

clean:
	cargo clean