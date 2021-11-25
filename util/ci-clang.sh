#!/bin/bash

MAKE=make
GEN="CodeBlocks - Unix Makefiles"
BUILD_DIR="build/clang"

# TODO: Unify with ci-gcc

# TODO: accept a whole string of CMake options
if [ ! -z $1 ]; then
	echo "Building statically"
	USE_STATIC="ON"
fi

GCC_PREFIX=clang
CMAKE_C_COMPILER="${GCC_PREFIX}"
CMAKE_CXX_COMPILER="${GCC_PREFIX}++"

mkdir -p $BUILD_DIR && cd $BUILD_DIR
mkdir -p bin

cmake -G "${GEN}" ../.. \
-DCMAKE_C_COMPILER="${CMAKE_C_COMPILER}" \
-DCMAKE_CXX_COMPILER="${CMAKE_CXX_COMPILER}" \
-DUSE_STATIC="$USE_STATIC" \
-DUSE_UNITY="ON" \
-DBUILD_BOOST="ON" \
&& ${MAKE} -j `nproc` || ${MAKE} && ${MAKE} -j `nproc` install
ctest --output-on-failure -j `nproc`
