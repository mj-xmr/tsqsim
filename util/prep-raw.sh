#!/bin/bash -e

cd externals/transactions-export-mj
mkdir -p build && cd build
pwd
if ! cmake .. ; then
	echo "Is your 'monero' directory symlinked to $HOME and master built with 'make'?"
	exit 1
fi

make
