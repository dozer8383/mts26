#!/bin/bash
mkdir -p build
cd build
cmake ..
cmake --build .
if [ $? -ne 0 ]; then
    echo "Build failed"
    exit 1
fi
echo "Build succeeded"
cd ..
mkdir -p package
cp build/bin/* package/
cp -r assets package/
exec package/mts26-0.1.0