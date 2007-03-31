!/usr/bin/env perl

# Copyright 2002-2006 Velox Development Team. This file is licenced under the
# revised BSD licence. See licence_bsd.txt in the root of the Velox 
# distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
# complete licence text

# author: sheijk, 12-06-2005

# reads a series of code lines like "type name;" from the standard input 
# and transforms them into a series of getters and setters which are printed
# to stdout
#
# Legal formats:
# m_nVar, m_Var, var -> GetVar, SetVar
# Note: m_strVar currently not supported

$declarations="";
$implementations="";
$inlineimpl="";

# set new line symbol to "" to read whole input as one line
$/ = "";
$input = <STDIN>;
@lines = split("\n", $input);

#while(1) {
for( @lines ) {
	$line = $_;
	#print("---" . $line . "---\n");

	# match $_ against a regexp which will extract all interesting values
	if ( /(\s*)([^\s]+)\s+([^\s;]+)/ ) {
		
		$whitespace = $1;
		$type = $2;
		$name = $3;
		
		$name =~ m/(m_[a-z]?)?(.*)/;
		$pureName = $2;
		$pureName =~ s/^([a-z])/uc($1)/xe;

		# create prototypes
		$declarations = $declarations . "${whitespace}${type} Get${pureName}() const;\n"
		. "${whitespace}void Set${pureName}(const $type& in_${pureName});\n"
		. "\n";

		# create getter
		$implementations = $implementations . "${whitespace}${type} xxxtype::Get${pureName}() const\n"
		. "${whitespace}\{\n"
		. "${whitespace}\treturn ${name};\n"
		. "${whitespace}\}\n\n";
		
		# create setter
		$implementations = $implementations . "${whitespace}void xxxtype::Set${pureName}(const $type& in_${pureName})\n"
		. "${whitespace}\{\n"
		. "${whitespace}\t${name} = in_${pureName};\n"
		. "${whitespace}\}\n\n";

		# create inline getter and setter
		$inlineimpl = $inlineimpl . "${whitespace}${type} Get${pureName}() const { return ${name}; }\n"
		. "${whitespace}void Set${pureName}(const ${type}& in_Value) { ${name} = in_Value; }\n";
	}
	else {
#print("Could not match line ---${line}---");
	}
}

print("--- Declarations ---\n\n");
print($declarations);
print("\n\n--- Implementations ---\n\n");
print($implementations);
print("\n\n--- Inline functions ---\n\n");
print($inlineimpl);



