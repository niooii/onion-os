BUILDDIR="build"

if !([ -d "$BUILDDIR" ];) then
  echo "$BUILDDIR directory does not exist. Try running ./build.sh first"
  exit 1
fi

qemu-system-x86_64 -drive if=pflash,format=raw,readonly=on,file=/usr/share/ovmf/x64/OVMF.4m.fd -drive format=raw,file=fat:rw:./build/ -net none
