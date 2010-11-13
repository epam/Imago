if [ -z $1 ]; then
  echo "specify version";
  exit;
fi


wget http://scitouch.net/downloads/ego-$1-windows.zip
wget http://scitouch.net/downloads/ego-$1-linux.zip
wget http://scitouch.net/downloads/ego-$1-osx.zip
unzip ego-$1-windows.zip
unzip ego-$1-linux.zip
unzip ego-$1-osx.zip
mv ego-$1-linux ego-$1-universal
cp -r ego-$1-osx/lib/* ego-$1-universal/lib
cp -r ego-$1-windows/lib/* ego-$1-universal/lib
zip -r -9 ego-$1-universal.zip ego-$1-universal
rm ego-$1-windows.zip
rm ego-$1-linux.zip
rm ego-$1-osx.zip
rm -r ego-$1-windows
rm -r ego-$1-osx
