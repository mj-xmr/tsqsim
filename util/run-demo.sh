#!/bin/bash -e

COMPILER="gcc"
DIR=""

if [ ! -z $1 ]; then
	COMPILER="$1"
fi

if [ ! -z $2 ]; then
	DIR="-static"
fi

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:lib

pushd "build/$COMPILER$DIR/bin"
	./tsqsim --help
	./tsqsim
popd


