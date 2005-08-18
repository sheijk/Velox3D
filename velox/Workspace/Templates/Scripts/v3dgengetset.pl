#!/usr/bin/perl

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

# set new line symbol to "" to read whole input as one line
$/ = "";
$input = <STDIN>;
@lines = split("\r", $input);

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
		
		# print("${whitespace}${type} Get${pureName}() const;\n");
		# print("${whitespace}void Set${pureName}(const $type& in_${pureName});\n");
		# print("\n");
		
		$implementations = $implementations . "${whitespace}${type} xxxtype::Get${pureName}() const\n"
		. "${whitespace}\{\n"
		. "${whitespace}\treturn ${name};\n"
		. "${whitespace}\}\n\n";
		
		# create setter
		$implementations = $implementations . "${whitespace}void xxxtype::Set${pureName}(const $type& in_${pureName})\n"
		. "${whitespace}\{\n"
		. "${whitespace}\t${name} = in_${pureName};\n"
		. "${whitespace}\}\n\n";
	
		# create getter
		#print("${whitespace}${type} xxxtype::Get${pureName}() const\n");
		#print("${whitespace}\{\n");
		#print("${whitespace}\treturn ${name};\n");
		#print("${whitespace}\}\n\n");
		
		# create setter
		#print("${whitespace}void Sxxxtype::Set${pureName}(const $type& in_${pureName})\n");
		#print("${whitespace}\{\n");
		#print("${whitespace}\t${name} = in_${pureName};\n");
		#print("${whitespace}\}\n\n");
	}
	else {
#print("Could not match line ---${line}---");
	}
}

print($declarations);
print("\n\n\n");
print($implementations);


