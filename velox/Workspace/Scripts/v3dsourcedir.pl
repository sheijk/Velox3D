#!/bin/perl

$currentdir = $ENV{'PWD'};

$newdir = $currentdir;
$newdir =~ s/(.*velox)\/API\/(V3d|V3dLib)\/(.*)/\1\/Source\/$3/ ;

print("${newdir}\n");

