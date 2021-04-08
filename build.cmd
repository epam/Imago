@echo off

if not exist build\nul (
    mkdir build
)
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cd ..
if "%~1" == "" (
    cmake --build build --config Release
) else (
    cmake --build build --config Release --target %1
)
