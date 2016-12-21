#!/usr/bin/env perl

unless (exists($ENV{'QA_TOOLS'})) {
    print STDERR "ERROR: QA_TOOLS variable must be set !\n" ;
    exit 1
}
exec("$ENV{'QA_TOOLS'}/generic_test/codec/inputs/run_norm.pl", @ARGV) || die "$!" ;
exit 0 ;
