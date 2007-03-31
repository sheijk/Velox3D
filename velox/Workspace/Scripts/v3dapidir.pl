#!/usr/bin/env perl

# Copyright 2002-2006 Velox Development Team. This file is licenced under the
# revised BSD licence. See licence_bsd.txt in the root of the Velox 
# distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
# complete licence text

$currentdir = $ENV{'PWD'};

$newdir = $currentdir;
$newdir =~ s#(.*velox)/Source(.*)#\1/API/V3d\2#i ;

print("${newdir}\n");



