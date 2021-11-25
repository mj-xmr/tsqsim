#!/bin/bash -e

COMPILER="gcc"

if [ ! -z $1 ]; then
	COMPILER="$1"
fi

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:lib

pushd "build/$COMPILER/bin"
	./tsqsim --help
	./tsqsim
popd


