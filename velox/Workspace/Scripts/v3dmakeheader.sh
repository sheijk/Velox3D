#!/bin/bash

name=$1
veloxdir=`v3dgetdir.sh`

# copy velox template to temp file
cp ${veloxdir}/Workspace/Templates/VeloxFile.h ./$name.temp

# generate file header info
V3D_FD=`v3dgetheader.sh ${name}`

# remove placeholder in file
sed -e "s#/\*filename\*/#$V3D_FD#" $name.temp > $name.h
rm $name.temp

