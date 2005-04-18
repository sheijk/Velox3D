#!/bin/bash

# This script will install all velox scripts
# to the given path
# Call it like this:
#
# chmod uga+x install.sh
# ./install.sh %insert.someDirInPath%

if [ $1 ]
then
	echo Installing scripts to dir $1
	chmod uga+x v3d*.sh
	cp v3d*.sh $1
else
	echo Usage: ./install.sh installdir
fi

