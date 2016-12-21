#!/usr/bin/env perl

# version:              1.0
# date of creation:     17/12/2003
# date of modification: 17/12/2003
# author:               Guerte Yves
# usage:                cflags_cygfilter CFLAGS_LIST

use POSIX ;

if (exists($ENV{'QA_TOOLS'})) {
    use lib "$ENV{'QA_TOOLS'}/libperl" ;
    use cflags_cygfilter ;
}
else {
    print STDERR "\nERROR, the variable QA_TOOLS must be set !\n" ;
    exit 1
}

autoflush STDOUT 1 ;
autoflush STDERR 1 ;
umask 002 ;

#DEBUG print STDOUT 'cflags_cygfilter $#ARGV == ', $#ARGV, "\n" ;
#DEBUG print STDOUT 'cflags_cygfilter ARGV   == ', join(', ', @ARGV), "\n" ;

my @CFLAGS = cflags_cygfilter(@ARGV) ;
print STDOUT join(' ', map { quotemeta } @CFLAGS ), "\n" ;
exit 0 ;
