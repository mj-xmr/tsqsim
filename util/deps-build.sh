#!/bin/bash -e

echo "Building dependencies"
# externals/URT/build/build-urt.sh # Not needed anymore. Using CMakeLists.txt
if [ "$(uname)" != "Darwin" ]; then
	externals/scripts/build-qcustomplot.sh
fi
#elif [ "$(uname)" == "MinGw" ]; then
#	echo "TODO: install deps"	
#else
#elif [ "$(uname)" == "Dawrin" ]; then

# Other dependencies here...


