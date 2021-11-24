#!/bin/bash -e

DATA_FILE=TX-TS.csv.gz
DATA_URL=http://cryptog.hopto.org/monero/data/$DATA_FILE
DATA_DIR=build/data/data/txt

mkdir -p $DATA_DIR
pushd $DATA_DIR
	mkdir -p xmr
	pushd xmr
		if [ -f "$DATA_FILE" ]; then
			echo "Already exists: '`pwd`/$DATA_FILE'"
		else
			wget "$DATA_URL"
		fi
	popd
popd


