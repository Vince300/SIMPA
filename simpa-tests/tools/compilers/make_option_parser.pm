package Make_option_parser;
use Exporter;
@ISA = qw ( Exporter );
our @EXPORT = qw(pmo_parse_make_options pmo_get_make_options pmo_reset_make_options);

use strict;
use warnings;
use vars qw( $Option_string $False $True);
$False = 0;
$True = 1;

BEGIN { }
#
# parse_make_options - parse the -make_options arguments to run_all
#
# In order to facilitate the use of MWTH makefiles, it is necessary for
# run_all to pass permuted makefile variable to the make command. As we
# know, any make variable in a makefile can be overridden on the command
# to make. For example, make CFLAGS='-g -O2' overrides the default value
# of the makefile's CFLAGS variable.
#
# There is only one restriction on this parser, that the -make_options
# be terminated by the traditional -- terminator that indicates the end of
# options. For example: -make_options CFLAGS= -g -04 -- would be passed
# make as >make CFLAGS='-g -04 '. The terminating -- is gobbled up so that
# it does not affect further processing in GetOpts::Long. Any -- not
# following -make_options is handled by GetOpts::Long.
#
#
# This handler will parse the -make_options in the following way:
#
# 1. Any arguments starting with - that are seen prior to variable
# definitions are passed through directly to make
# unaltered. E.g.: -make_options -g -- is passed as >make -g
#
# 2. Bare arguments following a variable definition are considered a single
# argument. E.g. -make_options VAR=a b c is passed as >make VAR='a b c'
# This includes options following the variable definition. E.g.
# VAR=a b c -i ==> VAR='a b c -i'. Pass the options before variable
# definitions or send another -make_options. E.g. -make_options VAR=a b c
# -make_options -i ==> >make VAR='a b c' -i
#
# Prerequisites: This design requires that GetOpts::Long be configured to
# pass through any unknown command line arguments in @ARGV. This is done
# by specifying  use Getopt::Long qw(:config pass_through);
#
# Input: A list of arguments for -make_options in @ARGV
#
# Output: The properly formatted make command arguments are appended the the
# global $Option_string variable.
#
#
sub pmo_parse_make_options {
	my $option = shift @_;
	my $value = shift @_;
	my $arg;
	my $str_buffer = $value . ' ';

	# Concatenate all the arguments until a -- into a string buffer
	$str_buffer .= get_argv_str();

	#print $str_buffer,"\n";

	parse($str_buffer, $False, $False);

}

sub pmo_reset_make_options {
	$Option_string = "";
}

sub pmo_get_make_options {
	return $Option_string;
}

sub parse {
	my $input_str = shift @_;
	my $quoting = shift @_;
	my $defining_variable = shift @_;

PARSE:
{
	# Clean up quoting when nothing left to parse
	$input_str =~ s/^\s*$// && do {
		# Add last quote if necessary
		if ( $quoting ) {
			$Option_string .= "' ";
		}
		last PARSE;
	};

	# Eat ' and " chars
	$input_str =~ s/^\s*(['"])//i && do {
		if ( ! $quoting ) {
			$quoting = $True;
		}
		$Option_string .= "'";
		parse($input_str, $quoting, $defining_variable);
		last PARSE;
	};

	# VAR= or VAR =
	$input_str =~ s/^\s*(\w+)\s*[=]//i && do {
		# Finish off previous quoting
		if ( $quoting ) {
			# ygt mod: no space after, space added before new var def
			$Option_string .= "'";
			$quoting = $False;
		}
		$defining_variable = $True;
		# YGT mod: space added before new var def
		$Option_string .= " $1=";

		# Quote variable definitions
		if ( ! $quoting ) {
			$Option_string .= "'";
			$quoting = $True;
		}

		parse($input_str, $quoting, $defining_variable);
		$defining_variable = $False;
		last PARSE;
	};

	# BAREWORD
	$input_str =~ s/^(\s*[a-zA-Z0-9_.]+)//i && do {
		# Finish off previous quoting
		if ( $quoting && ! $defining_variable ) {
			$Option_string .= "' ";
			$quoting = $False;
		}
		$Option_string .= "$1";
		parse($input_str, $quoting, $defining_variable);
		last PARSE;
	};

	# OPTION
	$input_str =~ s/^(\s*\-\w+\s*)//i && do {
		if ( ! $quoting && $defining_variable ) {
			$Option_string .= "'";
			$quoting = $True;
		}
		$Option_string .= "$1";
		parse($input_str, $quoting, $defining_variable);
		last PARSE;
	};

} # PARSE


}

sub get_argv_str {
	my $arg;
	my $str_buffer = "";

	# Iterate thru the @ARGV array
	#
	while ( $arg = shift @ARGV ) {

SWITCH:	{
		# Handle illegal terminator
		$arg =~ /^(--[\w])/ && do {
			die "Illegal terminator $1\n";
		};

		# Handle -- terminator
		$arg =~ /^--/ && do {
			return $str_buffer;
		};

		# else just build a string from args
		$str_buffer .= $arg . ' ';

		} # End SWITCH

	} #end while

	return $str_buffer;
}

1;
