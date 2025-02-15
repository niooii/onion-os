BUILD_DIR = build
LD = $(TOOLCHAIN_DIR)/i686-elf-ld
LDFLAGS = -static -T kernel/linker.ld -nostdlib

KERNEL_ELF = $(BUILD_DIR)/kernel.elf

.PHONY: all clean run debug kernel

all: $(KERNEL_ELF)

$(KERNEL_ELF): linker.ld kernel
	$(LD) -static -T linker.ld -nostdlib \
	--build-id=none -Map=$(BUILD_DIR)/kernel.map \
	$(BUILD_DIR)/cobjs.o $(BUILD_DIR)/liboos_kernel.a -o $@

kernel:
	$(MAKE) -C C -j
	$(MAKE) -C kernel -j

clean:
	$(MAKE) -C C clean
	$(MAKE) -C kernel clean
	rm -rf $(BUILD_DIR)

run: $(KERNEL_ELF)
	qemu-system-i386 -kernel $<

debug: $(KERNEL_ELF)
	gdb -x debug.gdb
