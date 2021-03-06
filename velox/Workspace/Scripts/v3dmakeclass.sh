#!/bin/bash

# Copyright 2002-2006 Velox Development Team. This file is licenced under the
# revised BSD licence. See licence_bsd.txt in the root of the Velox 
# distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
# complete licence text

name=$1
namespace=$2
templatedir=`v3dgetdir.sh`/Workspace/Templates

if [ ! $1 ] || [ ! $2 ]
then
	echo Usage: v3dmakeclass.sh ClassName NamespaceName
	exit
fi

v3dmakeinterface.sh $1 $2

cp ${templatedir}/VeloxClass.cpp ${name}.cpp

# YES, this can be done better. If you do so, don't hesitate to
# commit / send us the file :)
sed -e "s#%%classname%%#$name#" ${name}.cpp > ${name}.temp
sed -e "s#%%classname%%#$name#" ${name}.temp > ${name}.cpp
sed -e "s#%%namespace%%#$namespace#" ${name}.cpp > ${name}.temp

mv ${name}.temp ${name}.cpp
mv ${name}.cpp `v3dsourcedir.pl`/

