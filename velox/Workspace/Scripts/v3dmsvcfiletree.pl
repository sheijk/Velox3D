#!/usr/bin/env perl

# Copyright 2002-2006 Velox Development Team. This file is licenced under the
# revised BSD licence. See licence_bsd.txt in the root of the Velox 
# distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
# complete licence text

sub printfiles {
	for(<*.h>) {
		print($_ . "\n");
	}
}

sub scandir {
	my $dir = $_[0];
	my $indent = $_[1];
	my $relpath = $_[2];

	if( $dir !~ /.*\..*$/ ) {
#		print("${indent}$dir\n");
		print("${indent}<Filter Name=\"${dir}\" Filter=\"\">\n");

		chdir($dir);

		for(<*>) {
			scandir($_, "${indent}  ", "${relpath}\\${dir}");
		}

		for(<*>) {
			if( /\.(h|cpp|inl)$/ ) {
				print("${indent}  <File RelativePath=\"${relpath}\\${dir}\\$_\" />\n");
			}
		}

		chdir("..");

		print("${indent}</Filter>\n");
	}
	else {
#		print("${indent}<File RelativePath=\"${relpath}\\${dir}\" />\n");
#		print("${indent}File $_\n");
	}
}

print("<Files>\n");

for(@ARGV) {
	scandir($_, "  ", "..\\..");
}

print("</Files>\n");


