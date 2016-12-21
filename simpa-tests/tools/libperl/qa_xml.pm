#!/usr/bin/env perl

# version:              1.0
# date of creation:     13/07/2004
# date of modification: 13/07/2004
# author:               Guerte Yves
# usage:                use lib "$ENV{'QA_TOOLS'}/libperl" ; use qa_xml ;

use POSIX ;
use POSIX qw/getpgrp tcgetpgrp/;
use FileHandle ;
use IO::Handle ;

if (exists($ENV{'QA_TOOLS'})) {
	use lib "$ENV{'QA_TOOLS'}/libperl" ;
	use tools ;
}
else {
	print STDERR "\nERROR, the variable QA_TOOLS must be set !\n" ;
	exit 1
}

autoflush STDOUT 1 ;
autoflush STDERR 1 ;
umask 002 ;


$PC = (sys_kind() eq 'PC') ;

# ---------------- Configuration ----------------------------------------
# indentation at each level of inclusion in objects
my $indent = '  ' ;

# ---------------- local variables ----------------------------------------
# level of inclusion in objects
my @xml_current = () ;

# --------------------------------------------------------
sub pxml_header {
	my $FILE = shift ;
	
	print $FILE '<?xml version="1.0" ?>', "\n" ;
	return ;
}
# --------------------------------------------------------
sub pxml_begin_tag {
	my $FILE = $_[0] ;
	my $tag_name = $_[1] ;
	
	print $FILE $indent x ($#xml_current + 1), '<', $tag_name ;
	foreach $i (2 .. $#_) {
		print $FILE ' ', ${$_[$i]}[0], '="', no_quote_surr(${$_[$i]}[1]), '"' ;
	}
	print $FILE '>', "\n" ;
	push (@xml_current, $tag_name) ;
	return ;
}

# --------------------------------------------------------
sub pxml_end_tag {
	my $FILE = shift ;
	my $tag_name = shift ;
	
	if (@xml_current) {
		my $current = pop(@xml_current) ;
		print $FILE $indent x ($#xml_current + 1), '</', $tag_name, '>', "\n" ;
		
		print STDERR "WARNING: closing $tag_name instead of $current.\n" unless ($tag_name =~ /^$current$/i) ;
	}
	else {
		print STDERR "WARNING: no tag to close\n" ;
	}
	return ;
}
	
# --------------------------------------------------------
sub pxml_end_current_tag {
	my $FILE = shift ;
	
	if (@xml_current) {
		my $current = pop(@xml_current) ;
		print $FILE $indent x ($#xml_current + 1), '</', $current, '>', "\n" ;
	}
	else {
		print STDERR "WARNING: no tag to close.\n" ;
	}
	return ;
}
	
# --------------------------------------------------------
sub pxml_empty_tag {
	my $FILE = $_[0] ;
	my $tag_name = $_[1] ;
	
	print $FILE $indent x ($#xml_current + 1), '<', $tag_name ;
	foreach $i (2 .. $#_) {
		print $FILE ' ', ${$_[$i]}[0], '="', no_quote_surr(${$_[$i]}[1]), '"' ;
	}
	print $FILE '/>', "\n" ;
	return ;
}

# --------------------------------------------------------
sub pxml_until_tag_level {
	my $FILE = shift ;
	my $level = shift ;
	
	foreach $i (reverse(($level + 1) .. $#xml_current)) {
		my $current = pop(@xml_current) ;
		print $FILE $indent x ($#xml_current + 1), '</', $current, '>', "\n" ;
	}
	return ;
}
# --------------------------------------------------------
sub pxml_until_in_tag {
	my $FILE = shift ;
	my $tag_name = shift ;
	
	return unless (@xml_current) ;
	my $current = $xml_current[$#xml_current] ;
	
	UNTIL_IN_TAG:
	while ($current !~ /^$tag_name$/i) {
		pxml_end_current_tag($FILE) ;
		exit UNTIL_IN_TAG unless (@xml_current) ;
		$current = $xml_current[$#xml_current] ;
	}
	return ;
}
# --------------------------------------------------------
sub pxml_push_tags {
	my @tag_names = @_ ;
	push (@xml_current, @tag_names) ;
	return ;
}
# --------------------------------------------------------
sub pxml_atomic_element {
	my $FILE = shift ;
	my $name = shift ;
	my $value = shift ;
	
	print $FILE $indent x ($#xml_current + 1), '<', $name, '>' , $value, '</', $name, '>', "\n" ;
	return ;
}

# ------------------ End of library ----------------------------------

1 ;

