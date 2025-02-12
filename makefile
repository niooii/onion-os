BUILD_DIR = build

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

clean:
	$(MAKE) -C loader clean
	$(MAKE) -C kernel clean
	rm -rf $(BUILD_DIR)

run: $(BUILD_DIR)/os.bin
	qemu-system-i386 -hda $<

debug: $(BUILD_DIR)/os.bin
	gdb -x debug.gdb
