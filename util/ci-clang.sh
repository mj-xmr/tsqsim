#!/bin/bash

MAKE=make
GEN="CodeBlocks - Unix Makefiles"
BUILD_DIR="build/clang"

GCC_PREFIX=clang
CMAKE_C_COMPILER="${GCC_PREFIX}"
CMAKE_CXX_COMPILER="${GCC_PREFIX}++"

mkdir -p $BUILD_DIR && cd $BUILD_DIR

cmake -G "${GEN}" ../.. \
-DCMAKE_C_COMPILER="${CMAKE_C_COMPILER}" \
-DCMAKE_CXX_COMPILER="${CMAKE_CXX_COMPILER}" \
-DUSE_STATIC="ON" \
-DUSE_UNITY="ON" \
&& ${MAKE} -j `nproc` || ${MAKE} && ${MAKE} -j `nproc` install
