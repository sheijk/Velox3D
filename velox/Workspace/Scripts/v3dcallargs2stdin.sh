#!/bin/bash

# Copyright 2002-2006 Velox Development Team. This file is licenced under the
# revised BSD licence. See licence_bsd.txt in the root of the Velox 
# distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
# complete licence text

# first parameter is a command which reads from stdin
# the rest of the parameters are sent via stdout to
# the give command

command="$1"
params=`echo "$@" | sed -e "s/$1\s//"`
#params="$@"

echo command = $command
echo params = "$params"

echo "${params}" | $command



