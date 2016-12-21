#!/usr/bin/env perl

unless (exists($ENV{'QA_TOOLS'})) {
    print STDERR "ERROR: QA_TOOLS variable must be set !\n" ;
    exit 1
}
exec("$ENV{'QA_TOOLS'}/generic_test/unit_tests/run_all_generic.pl", @ARGV) || die "$!" ;
exit 0 ;
