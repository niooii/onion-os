export PREFIX="/usr/local/i386elfcc"
TARGET=i386-elf
export PATH="$PREFIX/bin:$PATH"

CURRDIR=$(pwd)

mkdir -p ./tmp/src

if ! [ -f "$PREFIX/bin/i386-elf-ld" ]; then
  cd ./tmp/src
  sudo rm -rf ./binutils-build
  curl -O http://ftp.gnu.org/gnu/binutils/binutils-2.39.tar.gz
  tar xf binutils-2.39.tar.gz
  mkdir binutils-build
  cd binutils-build
  ../binutils-2.39/configure --target=$TARGET --enable-interwork --enable-multilib --disable-nls --disable-werror --prefix=$PREFIX 2>&1 | tee configure.log
  sudo make -j 8 all install 2>&1 | tee make.log
fi

if ! [ -f "$PREFIX/bin/i386-elf-gcc" ]; then
  cd "$CURRDIR"
  cd ./tmp/src
  sudo rm -rf ./gcc-build
  curl -O https://ftp.gnu.org/gnu/gcc/gcc-12.2.0/gcc-12.2.0.tar.gz
  tar xf gcc-12.2.0.tar.gz
  mkdir gcc-build
  cd gcc-build
  echo Configure: . . . . . . .
  ../gcc-12.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --disable-libssp --enable-language=c,c++ --without-headers
  echo MAKE ALL-GCC:
  sudo make -j 8 all-gcc
  echo MAKE ALL-TARGET-LIBGCC:
  sudo make -j 8 all-target-libgcc
  echo MAKE INSTALL-GCC:
  sudo make -j 8 install-gcc
  echo MAKE INSTALL-TARGET-LIBGCC:
  sudo make -j 8 install-target-libgcc
fi

echo WE GOOD:
ls "$PREFIX"/bin

