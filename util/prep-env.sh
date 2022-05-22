#!/bin/bash -e

URL="http://cryptog.hopto.org/monero/data/"

dload () {
	DATA_FILE_BASE=$1
	if [[ "$(uname)" == "Linux"  || "$(uname)" == "Darwin" ]]; then
		DATA_FILE=$DATA_FILE_BASE.gz
	else
		#DATA_FILE=$DATA_FILE_BASE.zip
		DATA_FILE=$DATA_FILE_BASE
	fi
	
	DATA_URL=$URL/$DATA_FILE
	
	if [ -f "$DATA_FILE" ]; then
		echo "Already exists: '`pwd`/$DATA_FILE'"
	else
		wget "$DATA_URL"
	fi
}


DATA_DIR=build/data/data/txt
CFG_DIR=build/cfg
SCRIPTS_DIR=build/scripts

mkdir -pv $CFG_DIR
mkdir -pv $DATA_DIR
#mkdir -pv $SCRIPTS_DIR
pushd $DATA_DIR
	mkdir -p xmr
	pushd xmr
		dload "TXTS.csv"
		dload "TSDIFF.csv"
	popd
popd


