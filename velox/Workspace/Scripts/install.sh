#!/bin/bash

# Copyright 2002-2006 Velox Development Team. This file is licenced under the
# revised BSD licence. See licence_bsd.txt in the root of the Velox 
# distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
# complete licence text

# This script will install all velox scripts
# to the given path
# Call it like this:
#
# chmod uga+x install.sh
# ./install.sh %insert.someDirInPath%

if [ $1 ]
then
	echo Installing scripts to dir $1

	# make scripts executable
	chmod uga+x v3d*.sh
	chmod uga+x v3d*.pl

	# copy everything to destination dir
	cp v3d*.sh $1
	cp v3d*.pl $1
    cp -r  v3dsynch/ $1
    rm -rdf $1/v3dsynch/.svn

	# generate v3dgetdir.sh script
	cd ../..
	echo echo `pwd` > $1/v3dgetdir.sh
else
	echo Usage: ./install.sh installdir
fi


