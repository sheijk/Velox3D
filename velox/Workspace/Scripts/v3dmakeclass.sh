#!/bin/bash

name=$1
namespace=$2
templatedir=`v3dgetdir.sh`/Workspace/Templates

v3dmakeinterface.sh $1 $2

cp ${templatedir}/VeloxClass.cpp ${name}.cpp

# lieber leser, wenn du jetzt meinst das kann man besser machen:
# kann man. tu es und committe das ganze :)
sed -e "s#%%classname%%#$name#" ${name}.cpp > ${name}.temp
sed -e "s#%%classname%%#$name#" ${name}.temp > ${name}.cpp
sed -e "s#%%namespace%%#$namespace#" ${name}.cpp > ${name}.temp

mv ${name}.temp ${name}.cpp
mv ${name}.cpp "`v3dsourcedir.pl`"

