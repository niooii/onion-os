export PREFIX="/usr/local/i386elfcc"
TARGET=i386-elf
export PATH="$PREFIX/bin:$PATH"
CURRDIR=$(pwd)

sudo mkdir -p "$PREFIX"
sudo chown -R $USER:$USER "$PREFIX"
mkdir -p ./tmp/src

# binutils
if ! [ -f "$PREFIX/bin/i386-elf-ld" ]; then
  cd ./tmp/src || exit 1
  rm -rf ./binutils-build
  curl -O http://ftp.gnu.org/gnu/binutils/binutils-2.39.tar.gz || exit 1
  tar xf binutils-2.39.tar.gz || exit 1
  mkdir binutils-build && cd binutils-build || exit 1
  ../binutils-2.39/configure --target=$TARGET --enable-interwork --enable-multilib --disable-nls --disable-werror --prefix=$PREFIX || exit 1
  make -j 8 || exit 1
  sudo make install || exit 1
  sudo chown -R $USER:$USER "$PREFIX"
fi

# gcc
if ! [ -f "$PREFIX/bin/i386-elf-gcc" ]; then
  cd "$CURRDIR" || exit 1
  cd ./tmp/src || exit 1
  rm -rf ./gcc-build
  curl -O https://ftp.gnu.org/gnu/gcc/gcc-12.2.0/gcc-12.2.0.tar.gz || exit 1
  tar xf gcc-12.2.0.tar.gz || exit 1
  mkdir gcc-build && cd gcc-build || exit 1
  
  ../gcc-12.2.0/configure --target=$TARGET \
    --prefix="$PREFIX" \
    --disable-nls \
    --disable-libssp \
    --enable-languages=c,c++ \
    --without-headers || exit 1
    
  make -j 8 all-gcc || exit 1
  sudo make install-gcc || exit 1
  make -j 8 all-target-libgcc || exit 1
  sudo make install-target-libgcc || exit 1
  sudo chown -R $USER:$USER "$PREFIX"
fi

ls "$PREFIX/bin"
