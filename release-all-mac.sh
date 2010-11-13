#!/bin/sh
/opt/local/bin/scons --macosx=10.5 all
/opt/local/bin/scons --macosx=10.6 all

mkdir -p release/imago-$1-osx-10.5
mkdir -p release/imago-$1-osx-10.6
mkdir -p release/imago-jni-$1-osx/lib/Mac/10.5
mkdir -p release/imago-jni-$1-osx/lib/Mac/10.6
mkdir -p release/ego-$1-osx/lib/Mac/10.5
mkdir -p release/ego-$1-osx/lib/Mac/10.6
mkdir -p release/alter-ego-$1-osx-10.5
mkdir -p release/alter-ego-$1-osx-10.6

cp output/release/alter-ego/universal_10.5/alter_ego release/alter-ego-$1-osx-10.5
cp output/release/alter-ego/universal_10.6/alter_ego release/alter-ego-$1-osx-10.6
cp LICENSE.GPL release/alter-ego-$1-osx-10.5/
cp LICENSE.GPL release/alter-ego-$1-osx-10.6/

cp output/release/imago_c/universal_10.5/libimago_c_static.a release/imago-$1-osx-10.5/libimago_c.a
cp output/release/imago_c/universal_10.5/libimago_c_shared.dylib release/imago-$1-osx-10.5/libimago_c.so

cp output/release/imago_c/universal_10.6/libimago_c_static.a release/imago-$1-osx-10.6/libimago_c.a
cp output/release/imago_c/universal_10.6/libimago_c_shared.dylib release/imago-$1-osx-10.6/libimago_c.so

cp output/release/imago_c/universal_10.6/imago_c.h release/imago-$1-osx-10.6/
cp output/release/imago_c/universal_10.5/imago_c.h release/imago-$1-osx-10.5/

cp LICENSE.GPL release/imago-$1-osx-10.5/
cp LICENSE.GPL release/imago-$1-osx-10.6/

cp output/release/ego/ego release/ego-$1-osx
cp output/release/ego/ego.jar release/ego-$1-osx
cp output/release/ego/lib/imago.jar release/ego-$1-osx/lib
cp output/release/ego/lib/indigo-java.jar release/ego-$1-osx/lib
cp output/release/ego/lib/indigo-renderer.jar release/ego-$1-osx/lib
cp output/release/ego/lib/jai_codec.jar release/ego-$1-linux/lib
cp output/release/ego/lib/jai_core.jar release/ego-$1-linux/lib
cp output/release/ego/lib/PDFRenderer.jar release/ego-$1-linux/lib

cp output/release/ego/lib/Mac/10.5/*.dylib release/ego-$1-osx/lib/Mac/10.5
cp output/release/ego/lib/Mac/10.6/*.dylib release/ego-$1-osx/lib/Mac/10.6
cp LICENSE.GPL release/ego-$1-osx/

cp output/release/jimago/imago.jar release/imago-jni-$1-osx/
cp output/release/jimago/lib/Mac/10.5/libimagojni.dylib release/imago-jni-$1-osx/lib/Mac/10.5
cp output/release/jimago/lib/Mac/10.6/libimagojni.dylib release/imago-jni-$1-osx/lib/Mac/10.6
cp LICENSE.GPL release/imago-jni-$1-osx/

cd release
zip -9 -r imago-$1-osx-10.5.zip imago-$1-osx-10.5
zip -9 -r imago-$1-osx-10.6.zip imago-$1-osx-10.6
zip -9 -r alter-ego-$1-osx-10.5.zip alter-ego-$1-osx-10.5
zip -9 -r alter-ego-$1-osx-10.6.zip alter-ego-$1-osx-10.6
zip -9 -r imago-jni-$1-osx.zip imago-jni-$1-osx
zip -9 -r ego-$1-osx.zip ego-$1-osx
cd -

