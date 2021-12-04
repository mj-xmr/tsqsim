#!/bin/bash -e

if [ "$(uname)" == "Darwin" ]; then
	#HOMEBREW_NO_AUTO_UPDATE=1 brew install qt5
	#brew link -v qt5 --force
	HOMEBREW_NO_AUTO_UPDATE=1 brew install boost openssl ccache gnuplot eigen unittest gsl armadillo unittest-cpp
	# TODO: armadillo should be replaced with Eigen (at URT)
	# TODO: install qt instead of qt5, after moving to latest QCustomPlot. Then the "--prefix" and "link" aren't needed.
else
	sudo apt update; sudo apt -y install build-essential cmake ccache gnuplot libssl-dev libeigen3-dev libunittest++-dev libgsl-dev libarmadillo-dev libboost-system-dev libboost-filesystem-dev libboost-iostreams-dev libboost-serialization-dev libboost-program-options-dev libboost-date-time-dev libboost-atomic-dev qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools
fi
# TODO: implement MinGW

