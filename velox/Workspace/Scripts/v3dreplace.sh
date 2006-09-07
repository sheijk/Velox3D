# Copyright 2002-2006 Velox Development Team. This file is licenced under the
# revised BSD licence. See licence_bsd.txt in the root of the Velox 
# distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
# complete licence text

filename=$1
old=$2
new=$3

sed -e ":start" -e "s#${old}#${new}#" -e "t start" ${filename} > ${filename}.temp
mv ${filename}.temp ${filename}

