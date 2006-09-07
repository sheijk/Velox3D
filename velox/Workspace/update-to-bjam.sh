#!/bin/bash

cd `v3dgetdir.sh`
cd Workspace/BoostBuild

cp Jamfile Jamfile.bk
v3dsynch.sh mb2bj ../mbuild.xml Jamfile

