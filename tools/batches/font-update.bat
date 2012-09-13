cd "%~dp0\..\..\font_generator\"
.\Release\font_generator.exe -D symbols\base -O ..\imago\src\imago.font
.\Release\font_generator.exe -D symbols\handwritten -O ..\imago\src\imago_handwritten.font
cd ..
CMake .
pause