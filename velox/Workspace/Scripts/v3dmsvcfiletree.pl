#!/bin/perl

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

