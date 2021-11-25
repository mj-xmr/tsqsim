#!/bin/bash -e

if [ "$(uname)" == "Darwin" ]; then
	HOMEBREW_NO_AUTO_UPDATE=1 brew install boost openssl ccache gnuplot eigen unittest gsl armadillo
else
	sudo apt -y install build-essential cmake ccache gnuplot libssl-dev libeigen3-dev libunittest++-dev libgsl-dev libarmadillo-dev libboost-system-dev libboost-filesystem-dev libboost-iostreams-dev libboost-serialization-dev libboost-program-options-dev libboost-date-time-dev
fi
# TODO: implement MinGW

