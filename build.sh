set -e
source ./export_envs

cd loader
make
cd ..
mkdir -p ./build
cp -r ./loader/build/boot.bin ./build/
cd kernel && make
cd ..
cp ./kernel/build/kernel.bin ./build/
cp ./kernel/build/ksymbols.o ./build/
cd ./build
dd if=boot.bin >> os.bin
dd if=kernel.bin >> os.bin
dd if=/dev/zero bs=512 count=50 >> os.bin
cat boot.bin kernel.bin > os.bin

echo "FINISH."
