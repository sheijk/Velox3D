#!/bin/bash

cd `v3dgetdir.sh`

veloxLines=`cat \`/bin/find API/ Source/ -regex ".*\.\(h\|cpp\|inl\)"\` | wc -l`
editorLines=`cat \`/bin/find Editor/EclipsePlugin/ -regex ".*\.java"\` | wc -l`
exampleLines=`cat \`/bin/find Examples/ -regex ".*\.\(h\|cpp\|inl\)"\` | wc -l`

echo Total lines in velox: $veloxLines
echo Total lines in editor: $editorLines
echo Total lines in examples: $exampleLines 
echo Total lines: `expr ${veloxLines} + ${editorLines} + ${exampleLines}`

