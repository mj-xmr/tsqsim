#!/bin/bash -e

set -e # Exit on any failure

VER=1.3.2
if [ -z $1 ]; then PROC=1; else PROC=$1; fi

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

mkdir -p build && cd build

# TODO: Check sha256 hash
wget https://www.qcustomplot.com/release/${VER}/QCustomPlot-sharedlib.tar.gz
wget https://www.qcustomplot.com/release/${VER}/QCustomPlot-source.tar.gz
tar -xvf QCustomPlot-sharedlib.tar.gz
tar -xvf QCustomPlot-source.tar.gz
mv qcustomplot-source/* .
#Patch!
#patch < "$DIR"/contrib/qcustomplot/slow-drag-1.3.2/qcustomplot.cpp.patch
#patch < "$DIR"/contrib/qcustomplot/slow-drag-1.3.2/qcustomplot.h.patch

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

