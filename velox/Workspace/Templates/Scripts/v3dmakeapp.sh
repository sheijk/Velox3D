#!/bin/bash

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

