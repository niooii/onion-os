.POSIX:
.PHONY: all clean

SRCDIR = src
BUILDDIR = build
SOURCE = boot.asm
TARGET = boot.bin

ASM = nasm 

all: $(TARGET)

$(TARGET): $(SRCDIR)/$(SOURCE)
	mkdir -p $(BUILDDIR)
	$(ASM) -f bin $(SRCDIR)/$(SOURCE) -o $(TARGET)
	mv $(TARGET) $(BUILDDIR)

clean:
	rm -rf $(BUILDDIR)
