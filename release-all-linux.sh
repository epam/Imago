#!/bin/sh
scons -j5 --target=x86 all
scons -j5 --target=x64 all

mkdir -p release/imago-$1-linux32
mkdir -p release/imago-$1-linux64
mkdir -p release/imago-jni-$1-linux/lib/Linux/x86
mkdir -p release/imago-jni-$1-linux/lib/Linux/x64
mkdir -p release/ego-$1-linux/lib/Linux/x86
mkdir -p release/ego-$1-linux/lib/Linux/x64
mkdir -p release/alter-ego-$1-linux32
mkdir -p release/alter-ego-$1-linux64

cp output/release/alter-ego/x86/alter_ego release/alter-ego-$1-linux32
cp output/release/alter-ego/x64/alter_ego release/alter-ego-$1-linux64
cp LICENSE.GPL release/alter-ego-$1-linux32/
cp LICENSE.GPL release/alter-ego-$1-linux64/

cp output/release/imago_c/x64/libimago_c_static.a release/imago-$1-linux64/libimago_c.a
cp output/release/imago_c/x64/libimago_c_shared.so release/imago-$1-linux64/libimago_c.so
cp output/release/imago_c/x86/libimago_c_static.a release/imago-$1-linux32/libimago_c.a
cp output/release/imago_c/x86/libimago_c_shared.so release/imago-$1-linux32/libimago_c.so
cp output/release/imago_c/x86/imago_c.h release/imago-$1-linux32/
cp output/release/imago_c/x64/imago_c.h release/imago-$1-linux64/
cp LICENSE.GPL release/imago-$1-linux32/
cp LICENSE.GPL release/imago-$1-linux32/

cp output/release/ego/ego.jar release/ego-$1-linux
cp output/release/ego/ego release/ego-$1-linux
cp output/release/ego/lib/imago.jar release/ego-$1-linux/lib
cp output/release/ego/lib/indigo-java.jar release/ego-$1-linux/lib
cp output/release/ego/lib/indigo-renderer-java.jar release/ego-$1-linux/lib
cp output/release/ego/lib/jai_codec.jar release/ego-$1-linux/lib
cp output/release/ego/lib/jai_core.jar release/ego-$1-linux/lib
cp output/release/ego/lib/PDFRenderer.jar release/ego-$1-linux/lib
cp output/release/ego/lib/Linux/x64/*.so release/ego-$1-linux/lib/Linux/x64
cp output/release/ego/lib/Linux/x86/*.so release/ego-$1-linux/lib/Linux/x86
cp LICENSE.GPL release/ego-$1-linux/

cp output/release/jimago/imago.jar release/imago-jni-$1-linux/
cp output/release/jimago/lib/Linux/x86/libimagojni.so release/imago-jni-$1-linux/lib/Linux/x86
cp output/release/jimago/lib/Linux/x64/libimagojni.so release/imago-jni-$1-linux/lib/Linux/x64
cp LICENSE.GPL release/imago-jni-$1-linux/

cd release
zip -9 -r imago-$1-linux32.zip imago-$1-linux32
zip -9 -r imago-$1-linux64.zip imago-$1-linux64
zip -9 -r alter-ego-$1-linux32.zip alter-ego-$1-linux32
zip -9 -r alter-ego-$1-linux64.zip alter-ego-$1-linux64
zip -9 -r imago-jni-$1-linux.zip imago-jni-$1-linux
zip -9 -r ego-$1-linux.zip ego-$1-linux
cd -

