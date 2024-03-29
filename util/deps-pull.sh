#!/bin/bash -e

if [ "$(uname)" == "Darwin" ]; then
	if xcode-select -p; then 
		echo "xcode already installed." 
	else 
		xcode-select --install
	fi
	HOMEBREW_NO_AUTO_UPDATE=1 brew install boost ccache gnuplot eigen gsl unittest-cpp wxwidgets r qt5 # openssl zmq
	brew link -v qt5 --force
	# echo 'export PATH="/usr/local/opt/qt@5/bin:$PATH"' >> /Users/runner/.bash_profile
	# TODO: install qt instead of qt5, after moving to latest QCustomPlot. Then the "--prefix" and "link" aren't needed.
	# Expose R_HOME path:
	# TODO:
	Rscript src/tsqsim-lib/static/scripts/r-path.R
elif [ "$(uname)" == "Linux" ]; then
	sudo apt update; sudo apt -y install build-essential cmake ccache gnuplot libeigen3-dev libunittest++-dev libgsl-dev libboost-system-dev libboost-filesystem-dev libboost-iostreams-dev libboost-serialization-dev libboost-program-options-dev libboost-date-time-dev libboost-atomic-dev libwxgtk3.0-gtk3-dev qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools r-base-dev python3-statsmodels  #  libssl-dev
else
	echo "TODO: install deps"	
	# TODO: implement MinGW	
fi

