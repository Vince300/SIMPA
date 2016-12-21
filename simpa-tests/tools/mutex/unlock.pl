#!/usr/bin/env perl

use lib "$ENV{QA_TOOLS}/mutex" ;
use semaphores ;

my $FILE = $ARGV[0] ;

unlock($FILE) ;
    
print STDOUT "File $FILE unlocked.\n" ;
