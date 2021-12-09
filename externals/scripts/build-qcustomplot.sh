#!/bin/bash -e

set -e # Exit on any failure

VER=1.3.2
if [ -z $1 ]; then PROC=1; else PROC=$1; fi

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

DIR_DLOAD=dload
mkdir -p build/deps/$DIR_DLOAD && cd build/deps


dload_file() {
	FILE=$1
	if [ -f ${FILE} ]; then
		echo "Already downloaded: ${FILE}"
	else
		wget https://www.qcustomplot.com/release/${VER}/${FILE}
	fi	
}

dload() {
	ARCHIVE_LIB=QCustomPlot-sharedlib.tar.gz
	ARCHIVE_SRC=QCustomPlot-source.tar.gz
	pushd $DIR_DLOAD
		dload_file $ARCHIVE_LIB
		dload_file $ARCHIVE_SRC
	popd
	tar -xvf $DIR_DLOAD/$ARCHIVE_LIB
	tar -xvf $DIR_DLOAD/$ARCHIVE_SRC
	
}

copy() {
	cp -vr "$DIR/../QCustomPlot/$VER" .
	cd $VER
}

#dload # Older and unsafe method
copy

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
DIR_TGT=/usr
if [ "$(uname)" == "Darwin" ]; then
	DIR_TGT=/usr/local
fi
SUDO=""
if [[ "$(uname)" == "Linux"  || "$(uname)" == "Darwin" ]]; then
	SUDO=sudo
	$SUDO mv libqcustomplot* $DIR_TGT/lib
	popd
	$SUDO mv qcustomplot.h $DIR_TGT/include
else
	$SUDO mv release/*qcustomplot* $DIR_TGT/lib
	popd
	#ls $DIR_TGT/include
	$SUDO mv qcustomplot.h $DIR_TGT/include
	ls $DIR_TGT/include
fi
#$SUDO mv libqcustomplot* $DIR_TGT/lib
#popd
#$SUDO mv qcustomplot.h $DIR_TGT/include

