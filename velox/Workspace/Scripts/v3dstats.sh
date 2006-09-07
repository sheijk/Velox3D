#!/bin/bash

# Copyright 2002-2006 Velox Development Team. This file is licenced under the
# revised BSD licence. See licence_bsd.txt in the root of the Velox 
# distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
# complete licence text

cd `v3dgetdir.sh`

veloxLines=`cat \`/bin/find API/ Source/ -regex ".*\.\(h\|cpp\|inl\)"\` | wc -l`
editorLines=`cat \`/bin/find Editor/EclipsePlugin/ -regex ".*\.java"\` | wc -l`
exampleLines=`cat \`/bin/find Examples/ -regex ".*\.\(h\|cpp\|inl\)"\` | wc -l`

echo Total lines in velox: $veloxLines
echo Total lines in editor: $editorLines
echo Total lines in examples: $exampleLines 
echo Total lines: `expr ${veloxLines} + ${editorLines} + ${exampleLines}`


