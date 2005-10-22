#!/bin/bash

if ! [ $1 ]
then
 echo $0 name
 echo Creates a file name.vcproj which will invoke the bjam target name
 echo
 echo This script creates a new project to invoke an bjam target
 echo
 echo The project will always be created in \`v3dgetdir.sh\`/Workspace/BoostBuild
 exit
fi

targetname=$1
projectid=`date +%Y%m%d-0000-0000-0000-000%N`

cd `v3dgetdir.sh`
cd "Workspace/BoostBuild"

cp ../Templates/bjam.vcproj ${targetname}.vcproj
v3dreplace.sh ${targetname}.vcproj "%%name%%" ${targetname}
v3dreplace.sh ${targetname}.vcproj "%%projectid%%" ${projectid}

