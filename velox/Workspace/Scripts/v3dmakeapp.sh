#!/bin/bash

# Copyright 2002-2006 Velox Development Team. This file is licenced under the
# revised BSD licence. See licence_bsd.txt in the root of the Velox 
# distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
# complete licence text

if [ $1 ] && [ -e $1 ]; then
	echo Directory $1 already exists, aborting
	exit
fi

if ! [ $1 ] || ! [ $2 ]
then
	echo "v3dmakeapp.sh AppName AppType"
	echo
	echo "For a list of app types see `v3dgetdir.sh`/Workspace/Templates/Scripts/ and look for directories containing an Application.vcproj file. Use the dir name as app type"
	cd `v3dgetdir.sh`/Workspace/Templates/
	pwd
	echo Available templates:
	echo *App
	exit
fi

# get parameters and generate subsitution strings
appname=$1
apptype=$2
veloxdir=`v3dgetdir.sh`
projectid=`date +%Y%m%d-0000-0000-0000-000%N`

# get relative path from new app dir to velox dir
# default to ../..
if [ $3 ]
then
	relpath=$3
else
	relpath="../.."
fi

# create app dir and copy template files there
mkdir ${appname}
cp ${veloxdir}/Workspace/Templates/${apptype}/* ./${appname}
cd ${appname}

# replace strings in vc project file
mv Application.vcproj ${appname}.vcproj
v3dreplace.sh ${appname}.vcproj "%%name%%" ${appname}
v3dreplace.sh ${appname}.vcproj "%%projectid%%" ${projectid}
v3dreplace.sh ${appname}.vcproj "%%relpath%%" "${relpath}"

# replace strings in cpp file
mv Application.cpp ${appname}.cpp
v3dreplace.sh ${appname}.cpp "%%name%%" ${appname}


