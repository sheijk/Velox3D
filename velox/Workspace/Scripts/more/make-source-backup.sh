#!/bin/bash

bkdir="`date +%Y-%m-%d` $@"
echo Creating backup in ${bkdir}

mkdir "${bkdir}"
cp -r ../../API "${bkdir}/"
cp -r ../../Doc "${bkdir}/"
cp -r ../../Editor "${bkdir}/"
cp -r ../../Examples "${bkdir}/"
cp -r ../../Source "${bkdir}/"
cp -r ../../Workspace "${bkdir}/"
cp ../../info.txt "${bkdir}/"

cd "${bkdir}"
../remove-svn-files.sh
rm -rdf `find Editor -name "*.dll"`
rm -rdf `find Examples Workspace -name "*.ncb"`
rm -rdf `find Examples Workspace -name "*.suo"`
rm -rdf Editor/EclipsePlugin/bin
rm -rdf Editor/NativeBindings/GlueCode
rm -rdf Editor/SourceV3d
