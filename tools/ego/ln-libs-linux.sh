mkdir -p lib/Linux/x64
mkdir -p lib/Linux/x86
cd lib/Linux/x64
ln -sf ../../../../build/jimago/jni/libimagojni.so .
cd ../x86
ln -sf ../../../../build/jimago/jni/libimagojni.so .
cd ../../../
