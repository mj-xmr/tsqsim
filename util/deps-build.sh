#!/bin/bash -e

echo "Building dependencies"
# externals/URT/build/build-urt.sh # Not needed anymore. Using CMakeLists.txt
if [ "$(uname)" != "Darwin" && "$(uname)" != "MinGw" ]; then
	externals/scripts/build-qcustomplot.sh
fi

# Other dependencies here...


