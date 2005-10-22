#!/bin/bash

name=$1.cpp
header=$1.h
veloxdir=`v3dgetdir.sh`

cp ${veloxdir}/Workspace/Templates/VeloxFile.cpp $1.temp

sed -e "s#/\*filename\*/#$1#" $1.temp > $name
rm $1.temp

