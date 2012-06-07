cd "%~dp0\..\..\font_generator\"
.\Release\font_generator.exe -D symbols -O ..\imago\src\imago.font
cd ..
CMake .
pause