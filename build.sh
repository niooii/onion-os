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
cat boot.bin kernel.bin > os.bin

echo "FINISH."
