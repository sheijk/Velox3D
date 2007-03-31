#!/usr/bin/env perl

# Copyright 2002-2006 Velox Development Team. This file is licenced under the
# revised BSD licence. See licence_bsd.txt in the root of the Velox 
# distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
# complete licence text


# inserts stdin into the files section of a Jamfile target
# takes the jamfile and the target name as parameters
# this is ugly

# read Jamfile from cmdline
$jamfile = $ARGV[0];
# read project
$project = $ARGV[1];

# read stdin
#@in = <STDIN>;



# check for jamfile
if (!$jamfile) {
    print "No Jamfile given\n";
    exit(0);
}

# open file
open(JAM, $jamfile) || die("unable to open file: $jamfile");

#state -> 0 = before target, 1 = in target, 2 = in files, 3 = after target
$state = 0;

$before = $target = $after = '';

# iterate over lines
while ($line = <JAM>) {
    if ($state == 0 ) { $before .= $line; }
    if ($state == 3) { $after .= $line; }
    if ($line =~ /[a-z]{3,3} $project$/ ) { $state = 1; }
    if ($state == 2 && $line =~ /.*(;|:|stop-sync).*/ ) { $state = 3; $after.= $line}
    if ($state == 1 && $line =~ /.*:.*/ ) {$state = 2; }
}

# close file
close(JAM);

# write new file
$newfile = $jamfile.'.new';
open(NF, ">$newfile") || die("unable to open file for output: $newfile");


print NF $before;
# write stdin, get rid of newlines
if ($state) {
    while ($ln = <STDIN>) {
        if ($ln !~ m/^[ ]*$/) {
            print NF $ln;
        }
    }
    print NF "\n"
}
#$state && print NF @in;
print NF $after;

close(NF);

#swap files
unlink($jamfile);
rename($newfile, $jamfile);


