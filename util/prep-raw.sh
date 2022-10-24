#!/bin/bash -e

# Uses the Monero blockchain itself to extract the raw data.
# Warning! It needs a lot of disk space to do this. Expect even ~100 GB.

pushd $HOME/monero 
	make -j2
popd

cd externals/transactions-export-mj
mkdir -p build && cd build
pwd
if ! cmake .. ; then
	echo "Is your 'monero' directory symlinked to $HOME and master built with 'make'?"
	exit 1
fi

make
