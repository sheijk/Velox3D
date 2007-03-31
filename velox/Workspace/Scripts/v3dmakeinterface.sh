#!/bin/bash

# Copyright 2002-2006 Velox Development Team. This file is licenced under the
# revised BSD licence. See licence_bsd.txt in the root of the Velox 
# distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
# complete licence text

name=$1
namespace=$2
veloxdir=`v3dgetdir.sh`

if [ ! $1 ] || [ ! $2 ]
then
	echo Usage: v3dmakeinterface.sh InterfaceName NamespaceName
	exit
fi

# copy velox template to temp file
cp ${veloxdir}/Workspace/Templates/VeloxClass.h ./$name.temp

# generate file header info
V3D_FD=`v3dgetheader.sh ${name}`

# remove placeholder in file
sed -e "s#%%filename%%#$V3D_FD#" $name.temp > $name.h
sed -e "s#%%classname%%#$name#" $name.h > $name.temp
sed -e "s#%%namespace%%#$namespace#" $name.temp > $name.h
rm $name.temp


