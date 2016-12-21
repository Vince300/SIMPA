#!/usr/bin/env perl

# version:              1.0
# date of creation:     02/12/2002
# date of modification: 02/12/2002
# author:               Guerte Yves
# usage:                have_main.pl file_1.c file_2.c ... file_n.c
#
# This script reports from a list of C source files the ones which contain a "main"
#
if ($#ARGV < 0) {
    print STDERR "You must provide a list of C source files as parameters.\n" ;
    exit 1 ;
}

my $re_comment = qr/(\/\*.+\*\/|\/\/.*$)/mo ;
my $re_main = qr/\bmain\s*\(/o ;

FILE_LOOP:
foreach my $f (@ARGV) {
    my $fname = "${f}\0" ;
    unless (open (FILE, "< $fname")) {
        warn "Can't open the file ${fname}: $!" ;
        next FILE_LOOP ;
    }

    while (<FILE>)  {
        # We suppress C and C++ comments
        s/$re_comment//g ;

        if (/$re_main/) {
            close FILE ;
            print STDOUT "${f}\n" ;
            next FILE_LOOP ;
        }
    }
    close FILE ;
}

exit 0 ;

