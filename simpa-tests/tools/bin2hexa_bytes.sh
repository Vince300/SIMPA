#!/bin/sh
od -v -t x1 |  perl -e 'while (<STDIN>) {
                          chomp($_) ;
                          @f = ($_ =~ /[0-9a-f]+/gi) ;
			  foreach $v (@f[1..$#f]) {
			    print substr('0' . uc($v), -2) , "\n"
			  }
			}'

