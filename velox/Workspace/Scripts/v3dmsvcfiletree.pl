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

#	print("${indent}Entering ${dir}\n");

	if( $dir !~ /\.(h|cpp|inl)$/ ) {
		print("${indent}<Filter name=\"${dir}\" Filter=\"\">\n");

		chdir($dir);

		for(<*>) {
			scandir($_, "${indent}  ", "${relpath}\\${dir}");
		}

		print("${indent}</Filter>\n");
	}
	else {
		print("${indent}<File RelativePath=\"${relpath}\\${dir}\" />\n");
#		print("${indent}File $_\n");
	}
}

print("<Files>\n");

for(@ARGV) {
	scandir($_, "  ", "..\\..");
}

print("</Files>\n");

