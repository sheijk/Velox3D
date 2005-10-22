#!/bin/bash

# first parameter is a command which reads from stdin
# the rest of the parameters are sent via stdout to
# the give command

command="$1"
params=`echo "$@" | sed -e "s/$1\s//"`
#params="$@"

echo command = $command
echo params = "$params"

echo "${params}" | $command


