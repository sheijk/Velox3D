#!/bin/perl

$currentdir = $ENV{'PWD'};

$newdir = $currentdir;
$newdir =~ s#(.*velox)/Source(.*)#\1/API/V3d\2#i ;

print("${newdir}\n");


