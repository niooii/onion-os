set -e

export PREFIX="/usr/local/i386elfcc"
TARGET=i386-elf
export PATH="$PREFIX/bin:$PATH"
CURRDIR=$(pwd)

sudo mkdir -p "$PREFIX"
sudo chown -R $USER:$USER "$PREFIX"
mkdir -p ./tmp/src

# binutils
if ! [ -f "$PREFIX/bin/i386-elf-ld" ]; then
  cd ./tmp/src
  rm -rf ./binutils-build
  curl -O http://ftp.gnu.org/gnu/binutils/binutils-2.39.tar.gz
  tar xf binutils-2.39.tar.gz
  mkdir binutils-build && cd binutils-build
  ../binutils-2.39/configure --target=$TARGET --enable-interwork --enable-multilib --disable-nls --disable-werror --prefix=$PREFIX
  make -j 8
  sudo make install
  sudo chown -R $USER:$USER "$PREFIX"
fi

# gcc
if ! [ -f "$PREFIX/bin/i386-elf-gcc" ]; then
  cd "$CURRDIR"
  cd ./tmp/src
  rm -rf ./gcc-build
  curl -O https://ftp.gnu.org/gnu/gcc/gcc-12.2.0/gcc-12.2.0.tar.gz
  tar xf gcc-12.2.0.tar.gz
  mkdir gcc-build && cd gcc-build
  
  ../gcc-12.2.0/configure --target=$TARGET \
    --prefix="$PREFIX" \
    --disable-nls \
    --disable-libssp \
    --enable-languages=c,c++ \
    --without-headers
    
  make -j 8 all-gcc
  sudo make install-gcc
  make -j 8 all-target-libgcc
  sudo make install-target-libgcc
  sudo chown -R $USER:$USER "$PREFIX"
fi

ls "$PREFIX/bin"
