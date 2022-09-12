#!/bin/bash -e

echo "Building dependencies"
# externals/URT/build/build-urt.sh # Not needed anymore. Using CMakeLists.txt
if [ "$(uname)" == "Linux" ]; then
	externals/scripts/build-qcustomplot.sh
	externals/scripts/build-qcustomplot-2.sh
#fi
#elif [ "$(uname)" == "MinGw" ]; then
#	echo "TODO: install deps"	
#else
elif [ "$(uname)" == "Dawrin" ]; then
	externals/scripts/build-qcustomplot-2.sh
fi
# Other dependencies here...


