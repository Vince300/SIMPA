#!/usr/bin/env perl

# version:              1.0
# date of creation:     02/12/2002
# date of modification: 02/12/2002
# author:               Guerte Yves
# usage:                smartdiff.pl file_1.c file_2.c
#
# This script reports diff from 2 C files ignoring RCS tags
#

use POSIX ;
use POSIX qw/getpgrp tcgetpgrp/;
use FileHandle ;
use IO::Handle ;
use File::Temp qw/tempfile/ ;

autoflush STDOUT 1 ;
autoflush STDERR 1 ;
umask 002 ;


# --------------------------------------------------------------------
# function that returns a secure string for use as filename
#
# How can I open a file with a leading "1/4‡ô3/4" or trailing blanks?
# Normally perl ignores trailing blanks in filenames, and interprets
# certain leading characters (or a trailing ``|'') to mean something special.
# To avoid this, you might want to use a routine like this.
# It tacks a trailing null byte on the name to make perl leave it alone:
#
sub safe_filename {
    my $fname  = shift ;
    return "$fname\0" ;
}
# --------------------------------------------------------------------------------
# this function return a string usable in a filename
# from another string which is a set of compiling options
# including the "/"
sub opt_to_str {
    my $CFLAGS = shift ;
    $CFLAGS =~ tr/a-zA-Z0-9\-_\./!/cs ;
    $CFLAGS =~ s/!+$// ;
    $CFLAGS =~ s/^$/!/ ;
    return $CFLAGS ;
}
# --------------------------------------------------------------------

my $fname1 = safe_filename($ARGV[$#ARGV - 1]) ;
my $fname2 = safe_filename($ARGV[$#ARGV]) ;

open FILE1, "< $fname1" or die "Can't open the file ${fname1}." ;
open FILE2, "< $fname2" or die "Can't open the file ${fname2}." ;

#my ($TMP1, $tmp1_fname) = tempfile("tmp1_XXXX", DIR=>"/tmp", OPEN=>1, UNLINK=>0) ;
#unless (defined($TMP1)) { close FILE1 ; close FILE2 ; die "ERROR: cannot open temporary file in /tmp." ; } ;
#my ($TMP2, $tmp2_fname) = tempfile("tmp2_XXXX", DIR=>"/tmp", OPEN=>1, UNLINK=>0) ;
#unless (defined($TMP2)) { close FILE1 ; close FILE2 ; close $TMP1 ; die "ERROR: cannot open temporary file in /tmp." ; } ;

my $tmp1_fname = '/tmp/' . safe_filename(opt_to_str($ARGV[$#ARGV - 1])) ;
my $tmp2_fname = '/tmp/' . safe_filename(opt_to_str($ARGV[$#ARGV])) ;
open $TMP1, "> $tmp1_fname" or die "Can't open the file ${tmp1_fname}." ;
open $TMP2, "> $tmp2_fname" or die "Can't open the file ${tmp2_fname}." ;

# Comments removing
my $is_c     = undef ;
my $is_diese = undef ;
$is_c     = ( ($fname1 =~ /\.([ch]|cpp)\0$/) or ($fname2 =~ /\.([ch]|cpp)\0$/) ) ;
$is_diese = ( ($fname1 =~ /\.(p[lm]|mak|sh|csh|tcsh)\0$/) or ($fname2 =~ /\.(p[lm]|mak|sh|csh|tcsh)\0$/) ) unless ($is_c);

undef $/;           # read in whole file, not just one line or paragraph
while (<FILE1>)  {
    # We suppress C and C++ comments
    s#/\*[^*]*\*+([^/*][^*]*\*+)*/|("(\\.|[^"\\])*"|'(\\.|[^'\\])*'|\n+|.[^/"'\\]*)#$2#go if ($is_c);
    
    # We suppress Perl/shells/makefiles comments
    s/\n\s*#[^\n]*\n/\n/go if ($is_diese) ;
    print $TMP1 $_ ;

}
close FILE1 ; close $TMP1 ;

while (<FILE2>)  {
    # We suppress C and C++ comments
    s#/\*[^*]*\*+([^/*][^*]*\*+)*/|("(\\.|[^"\\])*"|'(\\.|[^'\\])*'|\n+|.[^/"'\\]*)#$2#go if ($is_c);
    s/\n\s*#[^\n]*\n/\n/go if ($is_diese) ;
    print $TMP2 $_ ;

}
close FILE2 ; close $TMP2 ;

#my @CMD = ('diff', '-w', '-I', '\$\(Author\|Date\|Header\|Id\|Name\|Locker\|Log\|RCSfile\|Revision\|Source\|State\):[^\$]*\$', $tmp1_fname, $tmp2_fname) ;

my @CMD = ('diff', '-I', '\$\(Author\|Date\|Header\|Id\|Name\|Locker\|Log\|RCSfile\|Revision\|Source\|State\):[^\$]*\$', @ARGV) ;
$CMD[$#CMD - 1] = $tmp1_fname ;
$CMD[$#CMD]     = $tmp2_fname ;

unless (system(@CMD)) {
    $exit_value = $? >> 8 ;
    $signal_num = $? & 127 ;
    # print STDERR join(' ', @cmd), " failed: $?\n" ;
    # print STDERR "exit_value: $exit_value\n" ;
    # print STDERR "signal_num: $signal_num\n\n" ;
    unlink $tmp1_fname, $tmp2_fname ;
    if (($signal_num == 2) || ($signal_num == 125)) {
        exit 2 ;
    }
    else {
        exit $exit_value ;
    }
}
$exit_value = $? >> 8 ;
$signal_num = $? & 127 ;

unlink $tmp1_fname, $tmp2_fname ;

exit $exit_value ;
