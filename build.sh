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
exec bin/mts26-0.1.0