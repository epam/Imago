if [ -z $1 ]; then
  echo "specify version";
  exit;
fi


wget http://scitouch.net/downloads/imago-jni-$1-windows.zip
wget http://scitouch.net/downloads/imago-jni-$1-linux.zip
wget http://scitouch.net/downloads/imago-jni-$1-osx.zip
unzip imago-jni-$1-windows.zip
unzip imago-jni-$1-linux.zip
unzip imago-jni-$1-osx.zip
mv imago-jni-$1-linux imago-jni-$1-universal
cp -r imago-jni-$1-osx/lib/* imago-jni-$1-universal/lib
cp -r imago-jni-$1-windows/lib/* imago-jni-$1-universal/lib
zip -r -9 imago-jni-$1-universal.zip imago-jni-$1-universal
rm imago-jni-$1-windows.zip
rm imago-jni-$1-linux.zip
rm imago-jni-$1-osx.zip
rm -r imago-jni-$1-windows
rm -r imago-jni-$1-osx
