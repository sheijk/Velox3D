#!/bin/bash

if ! [ $1 ]
then
	echo v3d-make-source-backup.sh tagname
	echo
	echo Creates a backup of all source files in `v3dgetdir.sh`/Local/Backups/%Date\\ tagname
	exit
fi

cd `v3dgetdir.sh`
cd Local/Backups

bkdir="`date +%Y-%m-%d` $@"
echo Creating backup in ${bkdir}

mkdir "${bkdir}"
echo Backing up API dir...
cp -r ../../API "${bkdir}/"
echo Backing up Doc dir...
cp -r ../../Doc "${bkdir}/"
echo Backing up Editor dir...
cp -r ../../Editor "${bkdir}/"
echo Backing up Examples dir...
cp -r ../../Examples "${bkdir}/"
echo Backing up Source dir...
cp -r ../../Source "${bkdir}/"
echo Backing up Workspace dir...
cp -r ../../Workspace "${bkdir}/"
echo Backing up info.txt...
cp ../../info.txt "${bkdir}/"

cd "${bkdir}"
echo Removing .svn files...
v3d-remove-svn-files.sh
echo Removing .dll .ncb .suo files...
rm -rdf `find Editor -name "*.dll"`
rm -rdf `find Examples Workspace -name "*.ncb"`
rm -rdf `find Examples Workspace -name "*.suo"`
echo Removing java binaries and glue code...
rm -rdf Editor/EclipsePlugin/bin
rm -rdf Editor/NativeBindings/GlueCode
rm -rdf Editor/SourceV3d
