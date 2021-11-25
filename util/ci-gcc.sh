#!/bin/bash -e

MAKE=make
GEN="CodeBlocks - Unix Makefiles"
BUILD_DIR="build/gcc"
USE_STATIC="OFF"

# TODO: accept a whole string of CMake options
if [ ! -z $1 ]; then
	echo "Building statically"
	USE_STATIC="ON"
fi

mkdir -p $BUILD_DIR && cd $BUILD_DIR
mkdir -p bin

cmake -G "${GEN}" ../.. \
 \
 \
-DUSE_STATIC="$USE_STATIC" \
-DUSE_UNITY="ON" \
-DBUILD_BOOST="ON" \
&& ${MAKE} -j `nproc` || ${MAKE} && ${MAKE} -j `nproc` install
ctest --output-on-failure -j `nproc`
