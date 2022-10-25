#!/bin/bash -e

# Uses the Monero blockchain itself to extract the raw data.
# Warning! It needs a lot of disk space to do this. Expect even ~100 GB.



NPROC=2

sudo apt update
echo "Installing 'transactions-export' dependencies..."
sudo apt install libcurl4-gnutls-dev

echo "Installing 'monero' dependencies..."
sudo apt install build-essential cmake pkg-config libssl-dev libzmq3-dev libunbound-dev libsodium-dev libunwind8-dev liblzma-dev libreadline6-dev libexpat1-dev libpgm-dev libhidapi-dev libusb-1.0-0-dev libprotobuf-dev protobuf-compiler libudev-dev libboost-chrono-dev libboost-date-time-dev libboost-filesystem-dev libboost-locale-dev libboost-program-options-dev libboost-regex-dev libboost-serialization-dev libboost-system-dev libboost-thread-dev python3 ccache

pushd $HOME
	if [ ! -d monero ]; then
		git clone --recursive https://github.com/monero-project/monero.git
	fi
	pushd monero
		git checkout master
		git submodule init && git submodule update --remote; git submodule sync && git submodule update
		make -j$NPROC
	popd
popd


cd externals/transactions-export-mj
mkdir -p build && cd build
pwd
if ! cmake .. ; then
	echo "Is your 'monero' directory symlinked to $HOME and master built with 'make'?"
	exit 1
fi
make -j$NPROC
ls 

echo "Now synchronize the (full) blockchain and use the 'xmr2csv' executable."

