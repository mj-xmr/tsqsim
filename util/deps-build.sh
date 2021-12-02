#!/bin/bash -e

echo "Building dependencies"
# externals/URT/build/build-urt.sh # Not needed anymore. Using CMakeLists.txt
externals/scripts/build-qcustomplot.sh

# Other dependencies here...


