#!/bin/bash

# Copyright 2002-2006 Velox Development Team. This file is licenced under the
# revised BSD licence. See licence_bsd.txt in the root of the Velox 
# distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
# complete licence text

name=$1.cpp
header=$1.h
veloxdir=`v3dgetdir.sh`

cp ${veloxdir}/Workspace/Templates/VeloxFile.cpp $1.temp

sed -e "s#/\*filename\*/#$1#" $1.temp > $name
rm $1.temp


