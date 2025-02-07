set -e
BUILDDIR="build"
if !([ -d "$BUILDDIR" ];) then
  echo "$BUILDDIR directory does not exist. Try running ./build.sh first"
  exit 1
fi

if [ "$1" = "debug" ]; then
  echo Starting debug environment...
  gdb -x debug.gdb
  exit 0
fi
qemu-system-x86_64 -drive format=raw,file="build/os.bin",index=0,if=floppy, -m 128M
