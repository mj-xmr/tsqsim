#!/bin/bash -e

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:lib

pushd build/gcc/bin
	./tsqsim --help
	./tsqsim
popd


