mkdir build
cd build
cmake -G "Visual Studio 12 2013 Win64" ..
cmake --build . --config Release
cmake -P cmake_install.cmake