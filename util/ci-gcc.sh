#!/bin/bash -e

MAKE=make
GEN="CodeBlocks - Unix Makefiles"
BUILD_DIR="build/gcc"

mkdir -p $BUILD_DIR && cd $BUILD_DIR
mkdir -p bin

cmake -G "${GEN}" ../.. \
 \
 \
-DUSE_STATIC="OFF" \
-DUSE_UNITY="ON" \
-DBUILD_BOOST="ON" \
&& ${MAKE} -j `nproc` || ${MAKE} && ${MAKE} -j `nproc` install
ctest --output-on-failure -j `nproc`
