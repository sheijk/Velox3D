#!/usr/bin/perl

# author: sheijk, 12-06-2005

# reads a series of code lines like "type name;" from the standard input 
# and transforms them into a series of getters and setters which are printed
# to stdout
#
# Legal formats:
# m_nVar, m_Var, var -> GetVar, SetVar
#

while(1) {
	$_ = <STDIN>;
	$line = $_;
	if ( /(\s*)([^\s]+)\s+([^\s;]+)/ ) {
		
		$whitespace = $1;
		$type = $2;
		$name = $3;
		
		$name =~ m/(m_[a-z]?)?(.*)/;
		$pureName = $2;
		$pureName =~ s/^([a-z])/uc($1)/xe;
#		print("ws = #$whitespace# type = $type\t name = $name\t purename= $pureName \tin $line");
		# create getter
		print("${whitespace}${type} Get${pureName}()\n");
		print("${whitespace}\{\n");
		print("${whitespace}\treturn ${name};\n");
		print("${whitespace}\}\n\n");
		
		# create setter
		print("${whitespace}void Set${pureName}(const $type& in_${pureName})\n");
		print("${whitespace}\{\n");
		print("${whitespace}\t${name} = in_${pureName};\n");
		print("${whitespace}\}\n\n");
	}
	else {
		if ( ! $_ ) {
			exit(0);
		}
	}
}

