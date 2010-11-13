call scons -j5 --target=x86 all
call scons -j5 --target=x64 all

md release\imago-%1-win32
md release\imago-%1-win64
md release\imago-jni-%1-windows\lib\Win\x86
md release\imago-jni-%1-windows\lib\Win\x64
md release\ego-%1-windows\lib\Win\x86
md release\ego-%1-windows\lib\Win\x64
md release\alter-ego-%1-win32
md release\alter-ego-%1-win64

copy output\release\alter-ego\x86\alter_ego.exe release\alter-ego-%1-win32
copy output\release\alter-ego\x64\alter_ego.exe release\alter-ego-%1-win64
copy LICENSE.GPL release\alter-ego-%1-win32\
copy LICENSE.GPL release\alter-ego-%1-win64\

copy output\release\imago_c\x64\imago_c_static.lib release\imago-%1-win64\imago_c.lib
copy output\release\imago_c\x64\imago_c_shared.dll release\imago-%1-win64\imago_c.dll
copy output\release\imago_c\x86\imago_c_static.lib release\imago-%1-win32\imago_c.lib
copy output\release\imago_c\x86\imago_c_shared.dll release\imago-%1-win32\imago_c.dll
copy output\release\imago_c\x86\imago_c.h release\imago-%1-win32\
copy output\release\imago_c\x64\imago_c.h release\imago-%1-win64\
copy LICENSE.GPL release\imago-%1-win32\
copy LICENSE.GPL release\imago-%1-win64\

copy output\release\ego\ego.jar release\ego-%1-windows
copy output\release\ego\lib\imago.jar release\ego-%1-windows\lib
copy output\release\ego\lib\indigo-java.jar release\ego-%1-windows\lib
copy output\release\ego\lib\indigo-renderer-java.jar release\ego-%1-windows\lib
copy output\release\ego\lib\jai_codec.jar release\ego-%1-windows\lib
copy output\release\ego\lib\jai_core.jar release\ego-%1-windows\lib
copy output\release\ego\lib\PDFRenderer.jar release\ego-%1-windows\lib
copy output\release\ego\lib\Win\x64\*.dll release\ego-%1-windows\lib\Win\x64
copy output\release\ego\lib\Win\x86\*.dll release\ego-%1-windows\lib\Win\x86
copy LICENSE.GPL release\ego-%1-windows\

copy output\release\jimago\imago.jar release\imago-jni-%1-windows\
copy output\release\jimago\lib\Win\x86\imagojni.dll release\imago-jni-%1-windows\lib\Win\x86
copy output\release\jimago\lib\Win\x64\imagojni.dll release\imago-jni-%1-windows\lib\Win\x64
copy LICENSE.GPL release\imago-jni-%1-windows\

cd release
zip -r -9 imago-%1-win32.zip imago-%1-win32
zip -r -9 imago-%1-win64.zip imago-%1-win64
zip -r -9 alter-ego-%1-win32.zip alter-ego-%1-win32
zip -r -9 alter-ego-%1-win64.zip alter-ego-%1-win64
zip -r -9 imago-jni-%1-windows.zip imago-jni-%1-windows
zip -r -9 ego-%1-windows.zip ego-%1-windows
cd ..
