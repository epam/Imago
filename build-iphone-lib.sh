#!/bin/bash

if [ "" == "$1" ]
then
echo "Usage:"
echo "	$0 <output-build-dir>"
exit
fi

BUILD_DIR="$1"
SOURCE_DIR=$(pwd)

mkdir -p $BUILD_DIR
cd $BUILD_DIR
/opt/local/bin/cmake -DIPHONE=ON -DEMBED_FONT=OFF -G Xcode $SOURCE_DIR
cd -
