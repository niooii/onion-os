BUILD_DIR = build
LD = $(TOOLCHAIN_DIR)/i686-elf-ld
LDFLAGS = -static -T kernel/linker.ld -nostdlib

.PHONY: all clean run debug loader kernel

all: $(BUILD_DIR)/os.bin

$(BUILD_DIR)/os.bin: loader kernel
	@mkdir -p $(BUILD_DIR)
	rm -rf $@
	dd if=$(BUILD_DIR)/loader.bin >> $@
	dd if=$(BUILD_DIR)/kernel.bin >> $@
	dd if=/dev/zero bs=512 count=100 >> $@

loader:
	$(MAKE) -C loader

kernel:
	$(MAKE) -C kernel
	# $(MAKE) -C rs-kernel
	$(LD) $(LDFLAGS) $(BUILD_DIR)/kernel.o -o $(BUILD_DIR)/kernel.bin

clean:
	$(MAKE) -C loader clean
	$(MAKE) -C kernel clean
	# $(MAKE) -C rust clean
	rm -rf $(BUILD_DIR)

run: $(BUILD_DIR)/os.bin
	qemu-system-i386 -hda $<

debug: $(BUILD_DIR)/os.bin
	gdb -x debug.gdb
