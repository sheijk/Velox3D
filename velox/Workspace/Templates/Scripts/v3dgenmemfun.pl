#!/bin/perl

$classname=$ARGV[0];
# remove trailing .h
$classname =~ s/(.*)\.h/$1/;
# replace with placeholder if it's empty
$classname =~ s/^$/REPL_CLASSNAME/;

# set new line symbol to "" to read whole input as one line
$/ = "";
$input = <STDIN>;
@lines = split("\n", $input);

$declarations="";
$implementations="";

#for( @lines ) {
#	$line = $_;
for($line_num = 0; $line_num < @lines; $line_num += 1) {
	$line = @lines[$line_num];

	print("--- ${line} ---\n");

	# if this is a function declaration
	$ws_re = "(\s*)";
#	$ret_re = "([A-Za-z0-9\:\&]+)";
	$ret_re = "(.*)";
	$fn_re = "([A-Za-z0-9]+)";
	$p_re = "(.*)";
	$m_re = "([A-Za-z0-9]*)";
	if( $line =~ m/(\s*)${ret_re}\s${fn_re}\(${p_re}\)\s*${m_re}\s*$/ ) {
#	if( /(\s*)(.*)\s([A-Za-z0-9]+)\((.*)\)(.*)/ ) {
		$whitespace = $1;
		$retval = $2;
		$funcname = $3;
		$params = $4;
		$modifiers = $5;

		print("Function ${funcname}\n");
		print(" parameters ${params}\n");
		print(" retval ${retval}\n");
		print(" modifiers ${modifiers}\n\n");

		$declarations = $declarations . 
			"${whitespace}${retval} ${funcname}\(${params}\)${modifiers};\n";


		# check if we have an implementation
		if( @lines[$line_num+1] =~ m/(\s*)\{/ ) {
		$implementations = $implementations .
			"${retval} ${classname}::${funcname}\(${params}\)${modifiers}\n" .
			"\{\n";

			$indent = $1;

			$line_num += 1;
			$line = @lines[$line_num];

			# collect implementation
			for( ; not @lines[$line_num+1] =~ m/${indent}\}.*/; $line_num += 1) {
				$line = @lines[$line_num+1];
				$line =~ s/$indent//;
				$implementations = $implementations . $line . "\n";
			}
			$line_num += 1;
			$implementations = $implementations . "\}\n\n";
		}
	}
	else {
		$declarations = $declarations . $line . "\n";
#		print("line not recognized: ${line}\n");
	}
}

print("Declarations:\n\n${declarations}");
print("\n\nImplementation stubs:\n\n${implementations}");

