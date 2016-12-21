#!/usr/bin/env perl

use lib "$ENV{QA_TOOLS}/mutex" ;
use semaphores ;

my $FILE = $ARGV[0] ;

unless (lock($FILE)) {
       die "File $FILE is already locked.\n" ;
}

print STDOUT "File $FILE is now locked.\n" ;
