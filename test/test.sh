#!/bin/bash

TEST=$(OC_OPEN_COUNT=1 LD_PRELOAD=./liboc.so cat test/1 test/2 2>/dev/null) 
ERR=$?
if [ "$TEST" != "1" ]; then
	echo "$TEST result is '$TEST' should be '1'" 
	exit 1
fi
