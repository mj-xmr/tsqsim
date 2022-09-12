#!/bin/bash -e

echo "Building dependencies"

if [[ "$OSTYPE" == linux* ]]; then
	echo "$OSTYPE"
	externals/scripts/build-qcustomplot.sh
	externals/scripts/build-qcustomplot-2.sh
elif [[ "$OSTYPE" == darwin* ]]; then
	echo "$OSTYPE"
	externals/scripts/build-qcustomplot.sh
	externals/scripts/build-qcustomplot-2.sh
# Other dependencies here...
elif [[ "$OSTYPE" == cygwin* ]]; then
	echo "$OSTYPE"
        # POSIX compatibility layer and Linux environment emulation for Windows
elif [[ "$OSTYPE" == msys* ]]; then
	echo "$OSTYPE"
        # Lightweight shell and GNU utilities compiled for Windows (part of MinGW)
elif [[ "$OSTYPE" == win32* ]]; then
	echo "$OSTYPE"        
	# I'm not sure this can happen.
elif [[ "$OSTYPE" == freebsd* ]]; then
  echo "$OSTYPE"      # ...
else
	echo "Unknown OS: $OSTYPE"
        # Unknown.
fi


#fi
#elif [ "$(uname)" == "MinGw" ]; then
#	echo "TODO: install deps"	
#else
