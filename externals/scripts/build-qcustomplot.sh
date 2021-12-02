#!/bin/bash -e

set -e # Exit on any failure

VER=1.3.2
if [ -z $1 ]; then PROC=1; else PROC=$1; fi

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

DIR_DLOAD=dload
mkdir -p build/deps/$DIR_DLOAD && cd build/deps

# TODO: Check sha256 hash
ARCHIVE_LIB=QCustomPlot-sharedlib.tar.gz
ARCHIVE_SRC=QCustomPlot-source.tar.gz

pushd $DIR_DLOAD
	if [ ! -f ${ARCHIVE_LIB} ]; then
		wget https://www.qcustomplot.com/release/${VER}/${ARCHIVE_LIB}
	fi
	if [ ! -f ${ARCHIVE_SRC} ]; then
		wget https://www.qcustomplot.com/release/${VER}/${ARCHIVE_SRC}
	fi
popd

tar -xvf $DIR_DLOAD/QCustomPlot-sharedlib.tar.gz
tar -xvf $DIR_DLOAD/QCustomPlot-source.tar.gz
mv qcustomplot-source/* .
#Patch!
patch < "$DIR"/qcustomplot/slow-drag-1.3.2/qcustomplot.cpp.patch
patch < "$DIR"/qcustomplot/slow-drag-1.3.2/qcustomplot.h.patch

pushd qcustomplot-sharedlib/sharedlib-compilation

export PATH=/usr/lib/ccache:$PATH
export CFLAGS="-O3 -mtune=generic"
export CXXFLAGS=$CFLAGS

echo "QMAKE_CXXFLAGS += $CXXFLAGS" >> sharedlib-compilation.pro

qmake
make -j $PROC release || make release
sudo mv libqcustomplot* /usr/lib
popd
sudo mv qcustomplot.h /usr/include

