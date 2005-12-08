#!/bin/perl

sub countlines {
	my $filename = $_[0];

	open(FILE, $filename) || return 0;

	my $count = 0;
	while($line = <FILE>) {
		$count = $count + 1;
	}

	close(FILE);

	return $count;
}

sub dirstat {
	my $initialdir = $_[0];
	my $indent = $_[1];

#	print("scanning $initialdir\n");

	if( ! chdir($initialdir) ) {
		return;
	}
	
	my $dirlines = 0;

	for(<*>) {
		my $filename = $_;

#		print("${indent}${filename}\n");

		if( $filename =~ /.*\..+/ ) {
			my $count = countlines($filename);
			$dirlines += $count;
			print("${count}\t${indent}$_\n");
			#system("cat ${filename} | wc -l");
#			exec("pwd");
		}
		else {
			print("\t${indent}${filename}\n");
			$dirlines += dirstat($filename, "${indent}\t");
		}
	}

	print("${indent}Total lines: ${dirlines}\n");

	chdir("..");
	return $dirlines;
}

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

$totallines = 0;

for(@ARGV) {
	$totallines += dirstat($_, "\t");
}

print("\n--- Total ${totallines} ---\n");


