#!/bin/bash

cd `v3dgetdir.sh`
cd Workspace/MSVC71

v3dsynch.sh vc2mb ../mbuild.xml

cd ../BoostBuild

cp Jamfile Jamfile_preupdate
v3dsynch.sh mb2bj ../mbuild.xml Jamfile

