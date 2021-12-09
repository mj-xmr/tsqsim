#!/bin/bash -e

uname

if [ "$(uname)" == "Darwin" ]; then
	if xcode-select -p; then 
		echo "xcode already installed." 
	else 
		xcode-select --install
	fi
	#HOMEBREW_NO_AUTO_UPDATE=1 brew install qt5
	#brew link -v qt5 --force
	HOMEBREW_NO_AUTO_UPDATE=1 brew install boost openssl ccache gnuplot eigen gsl unittest-cpp
	# TODO: install qt instead of qt5, after moving to latest QCustomPlot. Then the "--prefix" and "link" aren't needed.
elif [ "$(uname)" == "MinGw" ]; then
	echo "TODO: install deps"	
else
	sudo apt update; sudo apt -y install build-essential cmake ccache gnuplot libssl-dev libeigen3-dev libunittest++-dev libgsl-dev libboost-system-dev libboost-filesystem-dev libboost-iostreams-dev libboost-serialization-dev libboost-program-options-dev libboost-date-time-dev libboost-atomic-dev qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools
fi
# TODO: implement MinGW

