#!/usr/bin/env perl

# --------------------------------------------------------
# Target specific environment
if(defined $p_makefile) {
	$toolchain = $p_makefile;
	$toolchain=~s/makefile.//;
	### assume every one defining target specfic are well behaved
	### makefile in makefile.<arch>, target specific environment
	### in <arch>/utils/cwenv.pm
	$envfile = "$ENV{'QA_TOOLS'}" . '/compilers/' . "$toolchain" . '/cwenv.pm';
	if ( -f $envfile) {
		require "$envfile";
		&setenv;
		print STDOUT 'target specific environment file at ';
		print STDOUT $envfile;
		print STDOUT ' is loaded';
	}
	else {
		print STDOUT 'target specific environment file at ';
		print STDOUT $envfile;
		print STDOUT ' is not found';
	}
}


system("mkdir -p bin obj outputs reports");
system("$ENV{'QA_TOOLS'}/generic_test/unit_tests/run_all_generic.pl @ARGV");

