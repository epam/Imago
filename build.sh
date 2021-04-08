#!/bin/sh
set -e
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cd ..

if [ -z "$1" ]; then
  cmake --build build --config Release
else
  cmake --build build --config Release --target $@
fi
