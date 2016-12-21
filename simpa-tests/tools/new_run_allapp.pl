#!/usr/bin/env perl

# version:              1.9
# date of creation:     17/04/2001
# date of modification: 10/02/2005
# author:               Guerte Yves
# usage:                new_run_allapp.pl [-v version] [-i cpu_id] [-d macro] [-r run_id] [-tar] scenario
# -------------------------------------------------------------------------------------
use POSIX ;
use FileHandle ;
use IO::Handle ;
use Sys::Hostname ;
use Cwd qw(cwd chdir abs_path ) ;
use File::Basename ;

# The runtest directory is $NEW_QA_ROOT/runtest directory
#
if (exists($ENV{'NEW_QA_ROOT'}) and exists($ENV{'QA_TOOLS'})) {

	use lib "$ENV{'QA_TOOLS'}/mutex" ;
	use semaphores ;
	use lib "$ENV{'QA_TOOLS'}/libperl" ;
	use tools ;
	use qa_xml ;

	unless(eval{$runtest_dir = abs_path("$ENV{'NEW_QA_ROOT'}/runtest")}) {
	print STDERR "ERROR: '$ENV{'NEW_QA_ROOT'}/runtest': No such directory.\n" ;
	exit 1 ;
	}
	$runtest_dir =~ s/\/*$// ;
	$runtest_dir_qtd = quotemeta($runtest_dir) ;
}
else {
	print STDERR "Variables NEW_QA_ROOT and QA_TOOLS must be set !\n" ;
	exit 1
}
my $launching_dir = cwd() ;
system('mkdir', '-p', "$runtest_dir/allapp_reports") unless ( -d "$runtest_dir/allapp_reports") ;
system('mkdir', '-p', "$runtest_dir/atomic_fail_reports") unless ( -d "$runtest_dir/atomic_fail_reports") ;

autoflush STDOUT 1 ;
autoflush STDERR 1 ;

$online = (-t STDIN && -t STDOUT) ;

umask 002 ;

$scriptname = $0 ;
$scriptname =~ s/[^\/]*\///g ;

if (exists($ENV{'HOST'})) {
	$HOST = $ENV{'HOST'} ;
}
else {
	$HOST = hostname() ;
}
$HOST =~ tr/[A-Z]/[a-z]/ ;

$host_type = $^O ;
$PC = (sys_kind() eq 'PC') ;
# To handle Windows paths with dirname('C:\Cygwin\home')
fileparse_set_fstype('MSWin32') if ($PC);

# Name of the master scripts (enter point for each test directory)
$run_all_script    = 'run_all.pl' ;
$qt_run_all_script = quotemeta ($run_all_script) ;
# --------------------------------------------------------------------------------
#
# Array of all the paths to acces the tests to do
@run_paths    = () ; # to access:  $path = $run_paths[i]
#
# Array of all the paths to acces the tests already done
@runned_paths = () ;
#
# array indexed by the number of tests of array of the options of each test
@options      = () ; # to access:  "$option number i for $path" = ${$options[$i_test]}[$i_opt_set]

# Flag to indicate that $run_path/${run_all_script} is locked
%is_locked_by_me = () ;

# Definition of all the variables of the scenario
# by a list of tokens (a token is a string)
%strl_defvars = () ;
#
# by disjunction of conjunctions of tokens (array oy arrays of tokens)
%defvars = () ;

# List of parameter filenames from master scripts options
@param_files = () ;

# XML output:
# offset in local report where it has already been read.
%report_curpos = () ;

# XML output
# offset in running trace where to write next report
$running_xml_curpos = 0 ;

# Indexes of the test to run in the scenario
@scn_indexes = () ; # to access:  $scn_indexes[$id_path][$id_variant] ;

# current index of the running test in the scenario
$scn_idx = 0 ;

# Last indexes of the test copied in global report
@last_scn_indexes_reported = () ; # to access:  $last_scn_indexes_reported[$id_path] ;

# -------------------------------------------------------------------------------------
# Secured lock/unlock against user break
#
sub sec_lock {
	my $FILE = shift(@_) ;
	if (! ($FILE =~ '^/')) {
		my $cur = cwd() ;
		chomp $cur ;
		$FILE = $cur . '/' . $FILE ;
	}
	if (not($is_locked_by_me{$FILE})) {
		{
		use sigtrap 'handler' => 'IGNORE', 'error-signals';
		use sigtrap 'handler' => 'IGNORE', 'normal-signals';
		use sigtrap 'handler' => 'IGNORE', 'old-interface-signals';
	#        local $SIG{INT}  = 'IGNORE' ;
	#        local $SIG{QUIT} = 'IGNORE' ;
	#        local $SIG{PIPE} = 'IGNORE' ;
		$is_locked_by_me{$FILE} = lock($FILE) ;
		use sigtrap 'handler' => \&my_handler, 'error-signals';
		use sigtrap 'handler' => \&my_handler, 'normal-signals';
		use sigtrap 'handler' => \&my_handler, 'old-interface-signals';
		}
	}
	return ($is_locked_by_me{$FILE}) ;
}
sub sec_unlock {
	my $FILE = shift(@_) ;
	if (! ($FILE =~ '^/')) {
		my $cur = cwd() ;
		chomp $cur ;
		$FILE = $cur . '/' . $FILE ;
	}
	if ($is_locked_by_me{$FILE}) {
		{
		use sigtrap 'handler' => 'IGNORE', 'error-signals';
		use sigtrap 'handler' => 'IGNORE', 'normal-signals';
		use sigtrap 'handler' => 'IGNORE', 'old-interface-signals';
	#        local $SIG{INT}  = 'IGNORE' ;
	#        local $SIG{QUIT} = 'IGNORE' ;
	#        local $SIG{PIPE} = 'IGNORE' ;
		$is_locked_by_me{$FILE} = not(unlock($FILE)) ;
		use sigtrap 'handler' => \&my_handler, 'error-signals';
		use sigtrap 'handler' => \&my_handler, 'normal-signals';
		use sigtrap 'handler' => \&my_handler, 'old-interface-signals';
		}
	}
	return not($is_locked_by_me{$FILE}) ;
}
sub sec_clean_locks {
	while (($file, $key) = each(%is_locked_by_me)) {
	if ($key) {
		sec_unlock("$file") ;
		}
	}
}

# -------------------------------------------------------------------------------------
# to format the time spent by each run_all
sub timef {
	my $seconds = shift ;
	my $intseconds = floor($seconds) ;
	my $fsec   = $intseconds % 60 ;
	   $fcent  = floor(($seconds - $intseconds) * 100) ;
	my $rest   = ($intseconds - $fsec) / 60 ;
	my $fmin   = $rest %60 ;
	my $fhours = ($rest - $fmin) / 60 ;
	return ("${fhours}h${fmin}'${fsec}" . '"' . "$fcent") ;
}

# function which format a number on 2 characters
sub fmt_2car {
	return substr('0' . $_[0], -2) ;
}

sub formatted_date {
	my ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime(time);
	# $year -= 100 ; $year = fmt_2car($year) ;
	$year += 1900 ;
	$mon  += 1 ;
	# $date = fmt_2car($mon) . "-" . fmt_2car($mday) . "-" . fmt_2car($year) ;
	my $date = fmt_2car($mday) . '/' . fmt_2car($mon) . '/' .  $year
		. ' ' . fmt_2car($hour) . ':' . fmt_2car($min) . ':' . fmt_2car($sec)  ;
	return $date ;
}

# -------------------------------------------------------------------------------------
# in case of user break
#
sub my_kill_handler { # 1st argument is signal name
	my($sig) = @_ ;
	print STDERR "Caught a SIG$sig in my_kill_handler\n" ;
	close($KID_TO_READ) if defined($KID_TO_READ) ; # Broken pipe
	sec_clean_locks ;
}
sub my_handler {        # 1st argument is signal name
	my($sig) = @_ ;
	print STDERR "Caught a SIG$sig\n" ;

	close($KID_TO_READ) if defined($KID_TO_READ) ; # Broken pipe

	if ( -e "$runtest_dir/stop.$version" ) {
	print RUNNING "\n\nFile stop.$version found, stopping.\n" ;
	unlink "$runtest_dir/stop.$version" ;
	$online = 0 ;
	}

	my %was_locked_by_me =  %is_locked_by_me ;
	sec_clean_locks ;

	my $answer = 'y' ;
	if ($online) {
	print STDOUT "Do you want to abort all the tests ? y|o/n [y] " ;
	my $answer = <STDIN> ;
	chomp $answer ;
	}
	if ($answer eq '' || $answer =~ /o|y/i) {
	if (defined $running) {
		printf RUNNING "$scriptname aborted by user (^C), Times (user=%.5g, system=%.5g, cuser=%.5g, csystem=%.5g)s\n",
			   $user0, $system0, $cuser0, $csystem0 ;

		printf RUNNING "                                 Times (user=%s, system=%s, cuser=%s, csystem=%s)\n\n",
			   timef($user0), timef($system0), timef($cuser0),  timef($csystem0) ;

		if ($tar_report) {
		print RUNNING "\nConcatenation of the reports made by: 'new_allapp_reports_pack.pl -v $version -tar $runtest_dir/scenarios/report_order.scn'\n\n" ;
		print STDOUT  "\nLaunching the concatenation of the reports (new_allapp_reports_pack.pl -v $version -tar $runtest_dir/scenarios/report_order.scn)\n" ;
		@args = ('-v', "$version", '-tar', "$runtest_dir/scenarios/report_order.scn") ;
		}
		else {
		print RUNNING "\nConcatenation of the reports made by: 'new_allapp_reports_pack.pl -v $version $runtest_dir/scenarios/report_order.scn'\n\n" ;
		print STDOUT  "\nLaunching the concatenation of the reports (new_allapp_reports_pack.pl -v $version $runtest_dir/scenarios/report_order.scn)\n" ;
		@args = ('-v', "$version", "$runtest_dir/scenarios/report_order.scn") ;
		}
		close RUNNING ;
		unless (rename "$running", "$runtest_dir/allapp_reports/allapp_report_$version") {
			print STDERR "ERROR in: rename '$running', '$runtest_dir/allapp_reports/allapp_report_$version'" ;
		}

        # XML gen
        chdir $runtest_dir ;
        foreach my $id_path (0..$#run_paths) {
        my $run_path = $run_paths[$id_path] ;
        $run_path =~ s/^${runtest_dir_qtd}\/*// ;
        # Concatenation of the test report to the global report
        my $report = "$run_path/reports/report_$version.draft.xml" ;
        stat("$report") ;
        if ( -f _ && -r _  ) {
            if (open REPORT, "<$report") {
                print RUNNING_XML "\n\n" ;

                my $test_opened = 0 ;
                if (defined($last_scn_indexes_reported[$id_path])) {
                    my $last_scn_idx = $last_scn_indexes_reported[$id_path] + 1 ;
                    COPY_REM_XML1A:
                    while (<REPORT>) {
                        if (/^ *<TEST *scn_idx="$last_scn_idx"[^>]*>/) {
                            # We remove heading spaces
                            s/^  *</</ ;
                            tr/\015//d ;
                            print RUNNING_XML ;
                            $test_opened = 1 ;
                            last COPY_REM_XML1A ;
                        }
                    }
                }
                else {
                    COPY_REM_XML1B:
                    while (<REPORT>) {
                        if (/^ *<TEST[^>]*>/) {
                            # We remove heading spaces
                            s/^  *</</ ;
                            tr/\015//d ;
                            print RUNNING_XML ;
                            $test_opened = 1 ;
                            last COPY_REM_XML1B ;
                        }
                    }
                }
                # We copy remaining reports.
                COPY_REM_XML2:
                while (<REPORT>) {
                    # We remove heading spaces
                    s/^  *</</ ;
                    tr/\015//d ;

                    if ( $test_opened ) {
                        $test_opened = 0 if (/^ *<\/TEST[^>]*>/) ;
                    }
                    else {
                        $test_opened = 1 if (/^ *<TEST[^>]*>/) ;
                    }
                    last COPY_REM_XML2 if (/^ *<\/REPORT[^>]*>/) ;

                    print RUNNING_XML ;
				}
                print RUNNING_XML "\n</TEST>\n" if ($test_opened) ;
				close REPORT ;
			}
			else {
				print STDERR "ERROR: file $report is unreadable.\n" ;
			}
		}
		else {
			# print STDERR "ERROR: file $report not found.\n" ;
		}
		}
		pxml_until_tag_level(RUNNING_XML, 0) ;
		pxml_atomic_element (RUNNING_XML, 'End_date', formatted_date()) ;
		pxml_until_tag_level(RUNNING_XML, -1) ;
		close RUNNING_XML ;
		rename "$running_xml", "$runtest_dir/allapp_reports/allapp_report_$version.xml" ;

		chdir $launching_dir ;
		# Remaining tests to process
		unless (open REMAINING, "> /tmp/remaining_tests_${version}.scn") {
		print STDERR "Warning: cannot open /tmp/remaining_tests_${version}.scn\n\n" ;
		print STDOUT "Writing the scenario for the remaining tests:\n" ;
		foreach my $id_path (0..$#run_paths) {
			my $run_path = $run_paths[$id_path] ;
			$run_path =~ s/^${runtest_dir_qtd}\/*// ;
			foreach my $id_opt (0..$#{$options[$id_path]}) {
			print STDOUT $run_path, "\t", join(' ', quotes_surround(map { no_quote_surr($_) } @{$options[$id_path][$id_opt]})), "\n" ;
			}
		}
		}
		else {
		print STDOUT "Writing the scenario for the remaining tests: /tmp/remaining_tests_${version}.scn\n" ;
		foreach my $id_path (0..$#run_paths) {
			my $run_path = $run_paths[$id_path] ;
			$run_path =~ s/^${runtest_dir_qtd}\/*// ;
			foreach my $id_opt (0..$#{$options[$id_path]}) {
			print REMAINING $run_path, "\t", join(' ', quotes_surround(map { no_quote_surr($_) } @{$options[$id_path][$id_opt]})), "\n" ;
			}
		}
		close REMAINING ;
		}
		($EUID, $EGID) = ($UID, $GID); # suid only
		exec('new_allapp_reports_pack.pl', @args) || warn "Can't exec program: $!" ;
		# NOTREACHED
	}
	exit 2 ;
	}
	else {
	while (($file, $key) = each(%was_locked_by_me)) {
		if ($key) {
		sec_lock("$file") ;
		}
	}
	}
}

use sigtrap 'handler' => \&my_handler, 'error-signals';
use sigtrap 'handler' => \&my_handler, 'normal-signals';
use sigtrap 'handler' => \&my_handler, 'old-interface-signals';

use sigtrap 'handler' => \&my_kill_handler, 'KILL';

#DEBUG $SIG{'INT'}  = \&my_handler ;
#DEBUG $SIG{'QUIT'} = \&my_handler ;
#DEBUG $SIG{'PIPE'} = \&my_handler ;


# -------------------------------------------------------------------------------------
# function which converts a disjunction of conjunctions (an array of arrays)
# into a printable string
#
sub str_orand {
	my @orand = @_ ;
	my $str_orand = "(" ;

	if ($#orand >= 0) {
	for ($i=0 ; $i <= $#orand - 1 ; $i++ ) {
		if ($#{$orand[$i]} >= 0) {
		$str_orand .= "[" . join(' ', @{$orand[$i]}) . "] + " ;
		}
		else {
		$str_orand .= "[] + " ;
		}
	}
	$str_orand .= "[" . join(' ', @{$orand[$#orand]}) . "]" ;
	}
	$str_orand .= ")" ;
	return $str_orand ;
}
# -------------------------------------------------------------------------------------
# function which makes a "and" between two disjunctions of conjuntions
#
sub and_disj {
	my @or_and1 = @{$_[0]} ;
	my @or_and2 = @{$_[1]} ;

	if (($#or_and1 < 0) || (($#or_and1 == 0) && ($#{$or_and1[0]} < 0))) {
	return @or_and2 ;
	}
	elsif (($#or_and2 < 0) || (($#or_and2 == 0) && ($#{$or_and2[0]} < 0))) {
	return @or_and1 ;
	}
	else {
	my @or_and = () ;
	my $id_or  = 0 ;

	for ($id1=0 ; $id1 <= $#or_and1 ; $id1++) {
		for ($id2=0 ; $id2 <= $#or_and2 ; $id2++) {

		@{$or_and[$id_or]} = (@{$or_and1[$id1]}, @{$or_and2[$id2]}) ;
		$id_or++ ;
		}
	}
	return @or_and ;
	}
} # end sub and_disj

# -------------------------------------------------------------------------------------
# function which converts a list of tokens with ' '=and  ','=or
# into a disjunction of confunction (an array of arrays )
#
sub parse_orand {
	my @toklist = @_ ;
	my @orand = ([]) ;

	# index where we are writing a "or" expression
	my $id_or  = 0 ;

	# index until which we are writing a "and" expression
	my $id_and = 0 ;

	# No token
	if ( $#toklist < 0 ) {
	return ([@orand], [@toklist]) ;
	}
	# End of paren = empty list
	elsif ( $toklist[0] eq ')' ) {
	# shift @toklist ;
	# print STDERR "Error with variable definition in parenthesis.\n" ;
	# print STDERR "Rest to analyse: " . join(' ', @toklist) . "\n" ;
	return ([@orand], [@toklist]) ;
	}
	# Only one token
	elsif ($#toklist == 0 ) {
	return ([[@toklist]], []) ;
	}
	else {
	while (($#toklist >= 0) && ($toklist[0] ne ')')) {
		if ($toklist[0] eq ',') {
		shift @toklist ;
		# $id_or++ ;
		$id_or = $id_and + 1 ;
		$id_and = $id_or ;
		@{$orand[$id_or]} = () ;
		}
		elsif ($toklist[0] eq '(') {
		shift @toklist ;
		my @res_and_toklist = parse_orand(@toklist) ;
		my @orand2  = @{$res_and_toklist[0]} ;
		@toklist    = @{$res_and_toklist[1]} ;
		if ($toklist[0] ne ')') {
			print STDERR "Error with variable definition in parenthesis.\n" ;
			print STDERR "Rest to analyse: " . join(' ', @toklist) . "\n" ;
			return ([@orand], [@toklist]) ;
		}
		else {
			shift @toklist ;
			my @current_and = @orand[$id_or .. $id_and] ;
			my @orand3 = and_disj([@current_and], [@orand2]) ;
			$id_and = $id_or + $#orand3 ;
			for ($i=0 ; $i <= $#orand3 ; $i++ ) {
			@{$orand[$id_or + $i]} = @{$orand3[$i]} ;
			}
		} # end if $toklist[0] ne ')')
		} # end if ($toklist[0] eq ',')
		else {
		my @orand2 = ([$toklist[0]]) ;

		my @current_and = @orand[$id_or .. $id_and] ;

		my @orand3 = and_disj([@current_and], [@orand2]) ;

		$id_and = $id_or + $#orand3 ;
		for ($i=0 ; $i <= $#orand3 ; $i++ ) {
			@{$orand[$id_or + $i]} = @{$orand3[$i]} ;
		}
		shift @toklist ;
		}
	} # end while (($#toklist >= 0) && ($toklist[0] ne ')'))
	return ([@orand], [@toklist]) ;
	} # end if ( $#toklist < 0 )
} # end sub parse_orand


# -------------------------- BEGINNING OF THE MAIN ------------------------------------
# analyzing the parameters
#
$version        = '' ;
$scenario_fname = '' ;
$tar_report     = 0 ;
$CPU_ID         = undef ;
@macrodefs      = () ;
$run_id         = undef ;
$atomic_fail_reports = undef ;
@o_args         = () ;

while ($#ARGV >= 0) {

	SWITCH_ARGS: {

	if ($ARGV[0] =~ /^-v$/i ) {
					   shift @ARGV ;
					   if ($#ARGV >= 0) {
					   $version = shift @ARGV ;
					   }
					   else {
					   print STDERR "Error with the 'version' parameter.\n" ;
					   $help = 1 ;
					   }
					   last SWITCH_ARGS ;
	}
	if ($ARGV[0] =~ /^(-h|-help)$/i ) {
					   $help = 1 ;
					   shift @ARGV ;
					   last SWITCH_ARGS ;
	}
	if ($ARGV[0] =~ /^(-i|-cpu_id)$/i ) {
					   shift @ARGV ;
					   if ($#ARGV >= 0) {
					   $CPU_ID = lc(quotemeta(shift @ARGV)) ;
					   }
					   else {
					   print STDERR "Error with the 'cpu_id' parameter.\n" ;
					   $help = 1 ;
					   }
					   last SWITCH_ARGS ;
	}
	if ($ARGV[0] =~ /^-tar$/i ) {
					   $tar_report = 1 ;
					   shift @ARGV ;
					   last SWITCH_ARGS ;
	}
	if ($ARGV[0] =~ /^(-d|-def)$/i ) {
					   shift @ARGV ;
					   if ($#ARGV >= 0) {
					   push(@macrodefs, shift @ARGV) ;
					   }
					   else {
					   print STDERR "Error with the 'def' parameter.\n" ;
					   $help = 1 ;
					   }
					   last SWITCH_ARGS ;
	}
	if ($ARGV[0] =~ /^(-r|-run_id)$/i ) {
					   shift @ARGV ;
					   if ($#ARGV >= 0) {
					   $run_id = shift @ARGV ;
					   $run_id =~ s/^\s*(\S*)\s*$/$1/ ;
					   if ($run_id !~ /^[\-]?\d+$/) {
						   print STDERR "Error: the 'run_id' parameter is not a number.\n" ;
						   $help = 1 ;
					   }
					   }
					   else {
					   print STDERR "Error with the 'run_id' parameter.\n" ;
					   $help = 1 ;
					   }
					   last SWITCH_ARGS ;
	}
	if ($ARGV[0] =~ /^-atomic_fail_reports$/i ) {
					   $atomic_fail_reports = 1 ;
					   shift @ARGV ;
					   last SWITCH_ARGS ;
	}
	push (@o_args, (shift @ARGV)) ;

	}
}

if ($#o_args >= 1) {
	print STDERR "Unknown parameters: ", join(' ', @o_args), "\n" ;
	$help = 1 ;
}
elsif ($#o_args == 0) {
	$scenario_fname = $o_args[0] ;
}
if ($scenario_fname eq '') {
	print STDERR "Scenario file is mandatory.\n" ;
	$help = 1 ;
}

if ($help) {
	my $scriptname = $0 ;
	$scriptname =~ s/[^\/]*\///g ;
	print STDOUT "Syntax:\n" ;
	print STDOUT "$scriptname [-v version] [-i cpu_id] [-d macro] [-r run_id] [-tar] scenario_file\n" ;
	exit 1 ;
}

# -------------------------------------------------------------------------------------
# We compute a new run_id if not told by the caller
#
unless (defined($run_id)) {
	my $status = 0 ;
	my $brk = 0 ;
	my @cmd = ("$ENV{'QA_TOOLS'}/get_run_id.pl") ;

	my @lines = execute_it_stdout_errbrkhdl(sub {$status = shift}, sub {$brk = 1}, @cmd) ;
	if ($brk) {
	sec_clean_locks() ;
	exit 2 ;
	}
	elsif ($status) {
	print STDERR "ERROR: fail status returned accessing the run_id counter.\n" ;
	sec_clean_locks() ;
	exit 1 ;
	}
	elsif ($#lines < 0) {
	print STDERR "ERROR: fail with empty result accessing the run_id counter.\n" ;
	sec_clean_locks() ;
	exit 1 ;
	}
	else {
	$run_id = $lines[0] ;
	}
}

# Version if computed from date
#
(undef,undef,undef,$mday,$mon,$year,undef,undef,undef) = localtime(time);
$year += 1900 ;
$mon  += 1 ;
if ($version eq '') {
   $version = "v${run_id}_$year-$mon-$mday" ;
}
else {
   $version = "v${run_id}_$version" ;
}
print STDOUT "Version of test is: $version\n\n" ;
if (-f "$runtest_dir/allapp_reports/allapp_report_$version" ) {
	print STDERR "WARNING: allapp_report_$version report already exists, making .bak version.\n" ;
	print STDOUT 'mv $NEW_QA_ROOT/runtest/allapp_reports/', "allapp_report_$version",
			' $NEW_QA_ROOT/runtest/allapp_reports/', "allapp_report_$version.bak", "\n\n" ;
	unless (rename "$runtest_dir/allapp_reports/allapp_report_$version", "$runtest_dir/allapp_reports/allapp_report_$version.bak") {
		print STDERR "ERROR in: rename '$runtest_dir/allapp_reports/allapp_report_$version', '$runtest_dir/allapp_reports/allapp_report_$version.bak'" ;
	}
}

# --------------
# XML gen
if (-f "$runtest_dir/allapp_reports/allapp_report_${version}.xml" ) {
	print STDERR "WARNING: allapp_report_${version}.xml report already exists, making .bak version.\n" ;
	print STDOUT 'mv $NEW_QA_ROOT/runtest/allapp_reports/', "allapp_report_${version}.xml",
			' $NEW_QA_ROOT/runtest/allapp_reports/', "allapp_report_${version}.xml.bak", "\n\n" ;
	rename "$runtest_dir/allapp_reports/allapp_report_${version}.xml", "$runtest_dir/allapp_reports/allapp_report_${version}.xml.bak" ;
}
# --------------


# -------------------------------------------------------------------------------------
# File "running" contains the list of the processes launched by new_run_allapp.pl
#
$running = "$runtest_dir/running.$version" ;
open RUNNING, "> $running" or die "Can't open the trace file $running.\n" ;
autoflush RUNNING 1 ;
binmode RUNNING ;
print RUNNING "Begin $scriptname -v $version $scenario_fname\n\n" ;
print RUNNING "HOST        = '" . $HOST . "'\n" ;

# --------------
# XML gen
$running_xml = "$runtest_dir/running.${version}.xml" ;
open RUNNING_XML, "> $running_xml" or die "Can't open the trace file $running.\n" ;
autoflush RUNNING_XML 1 ;
binmode RUNNING_XML ;
pxml_header         (RUNNING_XML)  ;
pxml_begin_tag      (RUNNING_XML, 'REPORT', ['version', ${version}]) ;
pxml_atomic_element (RUNNING_XML, 'run_id', $run_id) ;
pxml_atomic_element (RUNNING_XML, 'scenario_file', $scenario_fname) ;
pxml_atomic_element (RUNNING_XML, 'start_date', formatted_date()) ;
$running_xml_curpos = tell(RUNNING_XML) ;
# --------------

($user0,$system0,$cuser0,$csystem0) = times ;

# --------------------------------------------------------------------------------
# We write the versions of the tools
# You must have initialised the environment by a command as:
# source $QA_TOOLS/startup.csh

pxml_begin_tag      (RUNNING_XML, 'compiler_version');
pxml_atomic_element (RUNNING_XML, 'host_type', $host_type);
pxml_atomic_element (RUNNING_XML, 'host_name', $HOST) ;

if ( exists($ENV{'CC'}) ) {
    my $versions_report_tool = $ENV{'QA_TOOLS'} . '/compilers/' . $ENV{'CC'} . '/versions.pl' ;
    if ( -f $versions_report_tool ) {

        my @cmd = ($versions_report_tool) ;
        my $status = 0 ;
        my $brk = 0 ;

        my @tools_versions = execute_it_errbrkhdl(sub {$status = shift}, sub {$brk = 1}, @cmd) ;
        exit 2 if ($brk) ;

        if ($status) {
            $exit_value = $? >> 8 ;
            $signal_num = $? & 127 ;
            print STDERR "ERROR: fail accessing $versions_report_tool.\n" ;
            print STDERR "       exit_value == $exit_value\n" ;
            print STDERR "       signal_num == $signal_num\n\n" ;
        }
        else {
            for my $line (@tools_versions) {
                print STDOUT  $line, "\n" ;
                print RUNNING $line, "\n" ;
            }
            print STDOUT  "\n" ;
            print RUNNING "\n" ;
            # --------------
            # XML gen
            # Versions for respectively scc, cobj, icode, llt, asmsc100, sc100-ld, runsc100, sc100-sim, disasmsc100 are:
            if ( @tools_versions ) {

                my $tools_names_str = shift @tools_versions ;
                $tools_names_str =~ s/^Versions for respectively *// ;
                $tools_names_str =~ s/ *are:$// ;
                my @tools_names = split(/, */, $tools_names_str) ;
                my $max_tools = $#tools_names ;
                if ($#tools_names < $#tools_versions) {
                    print STDERR "ERROR: more versions than tools names.\n" ;
                }
                elsif ($#tools_names > $#tools_versions) {
                    print STDERR "ERROR: more tools names than versions.\n" ;
                    $max_tools = $#tools_versions ;
                }
                foreach my $i (0 .. $max_tools) {
                    pxml_begin_tag      (RUNNING_XML, 'tool') ;
                    pxml_atomic_element (RUNNING_XML, 'tool_name', $tools_names[$i]) ;
                    pxml_atomic_element (RUNNING_XML, 'tool_version', $tools_versions[$i]) ;
                    pxml_end_tag        (RUNNING_XML, 'tool');
                }
            }
        }
    }
}
pxml_end_tag      (RUNNING_XML, 'compiler_version') ;

$running_xml_curpos = tell(RUNNING_XML) ;
# So that running is always a readable XML file
print RUNNING_XML "\n</REPORT>\n" ;
seek(RUNNING_XML, $running_xml_curpos, 0) ;

# -------------------------------------------------------------------------------------
# We read the scenario file

$cpp_cmd = 'scn_cpp.pl' ;
$cpp_cmd = join(' -I ', $cpp_cmd, quotemeta(dirname($scenario_fname)), quotemeta("$runtest_dir/scenarios")) ;
$cpp_cmd = join(' -D', $cpp_cmd, map(quotemeta, @macrodefs)) ;

chdir "$launching_dir" ;
print STDOUT "\n", "${cpp_cmd} < ${scenario_fname}\n\n" ;
open SCENARIO, "$cpp_cmd <$scenario_fname |" or die "Can't start scn_cpp.pl on the scenario file ${scenario_fname}: $!\n" ;

chdir "$runtest_dir" ;
READ_SCENARIO:
while (my $line = <SCENARIO>) {
   chomp ($line) ;

   # We suppress comments, leading and ending spaces
   #
   $line =~ s/([^\\])#.*$/$1/;
   $line =~ s/^\s+//;
   $line =~ s/\s+$//;

   # test of - empty line or comment,
   #         - def of variable,
   #         - def of run_all path and options
   #
   SWITCH_LINE: {
	   if ((length($line) == 0) || ($line =~ '^#')) {
	   # print STDERR "Empty line or comment.\n" ;
	   last SWITCH_LINE ;
	   }
	   if ($line =~ '^@') {
	   	   ($a_cpu_id, $line) = ($line =~ /^@([^\s]+)[\s]+(.*)$/gs) ;
		   if (defined($CPU_ID)) {
			   $a_cpu_id = lc(quotemeta($a_cpu_id)) ;
			   if ($a_cpu_id !~ /$CPU_ID/i) {
				# print STDERR "Line for another cpu.\n" ;
				last SWITCH_LINE ;
			   }
		   }
	   }

	   # We search for system variables
	   my $expanded_line = expand_sys_vars($line) ;
	   my (@items) = ($expanded_line =~ /(^[^=\"\s]+)\s*=\s*(.*)\s*$/gs) ;

	   # If it is a definition of a variable
	   if ($#items == 1) {

	   my $varname = $items[0] ;
	   my $vardef  = $items[1] ;

	   # Separating tokens
	   # my (@tokens) = ($vardef =~ /([^ \t\(\),\"]+|[\(\),]|\"[^\"]+\")/gsx) ;
	   my (@tokens) = ($vardef =~ /([^ \t\(\),\"\']+|[\(\),]|\"[^\"]*\"|\'[^\']*\')/gsx) ;

	   #applying previous definitions
	   for ($itok=0 ; $itok <= $#tokens ; $itok++) {
		   my $tokname = $tokens[$itok] ;
		   if (exists($strl_defvars{$tokname})) {

		   my @strl_deftok  = @{$strl_defvars{$tokname}} ;
		   unshift(@strl_deftok, '(') ;
		   push(@strl_deftok, ')') ;
		   splice(@tokens, $itok, 1, @strl_deftok) ;
		   }
	   }
	   @{$strl_defvars{$varname}} = @tokens ;

	   # Parsing the token list
	   my @orand_and_toklist = parse_orand(@tokens) ;

	   my @orand_r   = @{$orand_and_toklist[0]} ;
	   my @toklist_r = @{$orand_and_toklist[1]} ;

	   if ($#toklist_r >= 0) {
		   print STDERR "Variable definition not entirely parsed ($#toklist_r).\n" ;
		   print STDERR "Rest = " . join(' | ', @toklist_r) . "\n" ;
		   print STDERR "Rest = (" . join(' | ', @{$toklist_r[0]}) . ")\n" ;
	   }

	   @{$defvars{$varname}} = @orand_r ;
		   # print STDOUT "$varname orand[0..$#orand_r] = " . str_orand(@orand_r) . "\n" ; # DEBUG

	   last SWITCH_LINE ;
	   } # end if ($#items == 1) => definition of a variable

	   PATH_AND_OPTIONS: {
	   # a word (neither '"' nor " ") and the rest
	   my (@items) = ($expanded_line =~ /(^[^\"\s]+)\s*(.*)\s*$/gs) ;

	   my $item_path   = $items[0] ;
	   my $str_options = $items[1] ;

	   # Separating tokens
	   # my (@tokens) = ($str_options =~ /([^ \t\(\),\"]+|[\(\),]|\"[^\"]+\")/gsx) ;
	   my (@tokens) = ($str_options =~ /([^ \t\(\),\"\']+|[\(\),]|\"[^\"]*\"|\'[^\']*\')/gsx) ;

	   #applying previous definitions
	   for ($itok=0 ; $itok <= $#tokens ; $itok++) {
		   my $tokname = $tokens[$itok] ;
		   if (exists($strl_defvars{$tokname})) {

		   my @strl_deftok  = @{$strl_defvars{$tokname}} ;
		   unshift(@strl_deftok, '(') ;
		   push(@strl_deftok, ')') ;
		   splice(@tokens, $itok, 1, @strl_deftok) ;
		   }
	   }

	   # Parsing the token list
	   my @orand_and_toklist = parse_orand(@tokens) ;

	   my @orand_r   = @{$orand_and_toklist[0]} ;
	   my @toklist_r = @{$orand_and_toklist[1]} ;

	   if ($#toklist_r >= 0) {
		   print STDERR "Variable definition not entirely parsed ($#toklist_r).\n" ;
		   print STDERR "Rest = " . join(' | ', @toklist_r) . "\n" ;
		   print STDERR "Rest = (" . join(' | ', @{$toklist_r[0]}) . ")\n" ;
	   }

	   my @paths = glob "$item_path/${qt_run_all_script}" ;
	   foreach my $path (@paths) {
		   $path =~ s/[\/]${qt_run_all_script}$// ;
		   eval {$path = abs_path($path) ;} ;
		   if ($@) {
		   print STDERR  "ERROR, directory not found: ${path}\n\n" ;
		   print RUNNING "ERROR, directory not found: ${path}\n\n" ;
		   }
	   }
	   if ($#paths >= 0) {
		   if (($#paths == 0) and (not( -f "$paths[0]/${run_all_script}"))) {
		   print STDERR  "ERROR, master script $paths[0]/${run_all_script} doesn't exist.\n\n" ;
		   print RUNNING "ERROR, master script $paths[0]/${run_all_script} doesn't exist.\n\n" ;
		   }
		   else {
		   foreach my $path (@paths) {

			  push (@run_paths, $path) ;
			  my $nb_variants = $#{$options[$#run_paths]} + 1 ;

			  print STDOUT "$path => " . str_orand(@orand_r) . "\n\n" ;
			  for ($i=0 ; $i <= $#orand_r ; $i++ ) {

			  my @opt_this_path = @{$orand_r[$i]} ;

			  foreach my $opt (@opt_this_path) {
				  # search for system variables in the options and do the replacement
				  $opt = expand_sys_vars($opt) ;
			  }

			  # If a "pf|param_file" option is used, add it at the end of the report
			  my $i_opt = $#opt_this_path - 1 ;
			  while ( $i_opt >= 0 ) {
				  if ($opt_this_path[$i_opt] =~ /^-(pf|param_file)$/ix ) {

				  my $param_fname = no_quote_surr($opt_this_path[$i_opt + 1]) ;
				  my $param_basename = basename($param_fname) ;
				  my $param_dirname  = dirname($param_fname) ;

				  eval {$param_dirname = abs_path($param_dirname) ;} ;
				  if ($@) {
					  print STDERR  "ERROR, -pf directory not found: ${param_dirname}\n\n" ;
					  print RUNNING "ERROR, -pf directory not found: ${param_dirname}\n\n" ;
				  }
				  else {
					  $param_fname = "$param_dirname/$param_basename" ;

					  my $fname_expr = quotemeta($param_fname) ;
					  push(@param_files, $param_fname) unless (grep (/$fname_expr/i, @param_files)) ;
				  }
				  splice(@opt_this_path, $i_opt, 2) ;
				  }
				  $i_opt-- ;
			  }
			  @{$options[$#run_paths][$nb_variants + $i]}  = @opt_this_path ;
			  $scn_indexes[$#run_paths][$nb_variants + $i] = $scn_idx++;
			  }
		   } # end foreach $path (@paths)
		   } # end if (($#paths == 0) && ( -d "$paths[0]"))
	   }
	   else {
		   print STDERR  "ERROR, no directory found: $item_path.\n\n" ;
		   print RUNNING "ERROR, no directory found: $item_path.\n\n" ;
	   } # end if ($#paths >= 0)
	   } # end of PATH_AND_OPTIONS
   } # end of test of SWITCH_LINE
} # end of while <SCENARIO> (not eof)
close SCENARIO ;

print RUNNING '='x80, "\n" ;
foreach my $i_path (0..$#run_paths) {
	my $path = $run_paths[$i_path] ;
	print RUNNING "$path => " . str_orand(@{$options[$i_path]}) . "\n\n" ;
}
print RUNNING '='x80, "\n" ;
print RUNNING "\n\n" ;

# --------------
# XML gen
#
pxml_begin_tag      (RUNNING_XML, 'scenario', ['host_name', $HOST]) ;

foreach my $id_path ( 0 .. $#run_paths) {
	pxml_begin_tag      (RUNNING_XML, 'test_def') ;
	pxml_atomic_element (RUNNING_XML, 'test_path', $run_paths[$id_path]);
	foreach my $id_variant ( 0 .. $#{$options[$id_path]} ) {
		pxml_atomic_element (RUNNING_XML, 'options_set', join(' ', @{$options[$id_path][$id_variant]}) ) ;
	}
	pxml_end_tag       (RUNNING_XML, 'test_def') ;
}
pxml_end_tag      (RUNNING_XML, 'scenario') ;

# -------------------------------------------------------------------------------------

# We include the parameters files
#
# --------------
# XML gen
#
pxml_begin_tag      (RUNNING_XML, 'param_files') ;
pxml_atomic_element (RUNNING_XML, 'host_name', $HOST) ;

# --------------

chdir "$runtest_dir" ;
foreach my $param_file_name (@param_files) {

	unless (open(FOO, "< $param_file_name")) {
		printf RUNNING "* Parameter file: %20s not found ********\n", $param_file_name ;
		printf STDERR  "* Parameter file: %20s not found ********\n", $param_file_name ;

		pxml_begin_tag      (RUNNING_XML, 'param_file', ['filename', $param_file_name], ['ERROR', 'File not found.']) ;
		pxml_atomic_element (RUNNING_XML, 'filename', $param_file_name) ;
		print RUNNING_XML    '<![CDATA[', "\n", 'ERROR: File not found', "\n", ']]>', "\n" ;
	}
	else {
		printf RUNNING "* Parameter file: %20s ******************\n", $param_file_name ;

		pxml_begin_tag      (RUNNING_XML, 'param_file', ['filename', $param_file_name]) ;
		pxml_atomic_element (RUNNING_XML, 'filename', $param_file_name) ;
		print RUNNING_XML    '<![CDATA[', "\n" ;
		while ( <FOO> ) {
			chomp ;
			# We strip newline (LF, NL) ; return (CR) ; form feed (FF) ; alarm (bell) (BEL) ; escape (think troff)  (ESC)
			s/[\n\r\f\a\e]//g ;
			print RUNNING     $_, "\n" ;
			print RUNNING_XML $_, "\n" ;
		}
		close FOO ;
		printf RUNNING "* End of parameter file: %20s ***********\n\n", $param_file_name ;

		print RUNNING_XML    ']]>', "\n" ;
	}
	pxml_end_tag      (RUNNING_XML, 'param_file') ;
}
print RUNNING '='x80 . "\n" ;
print RUNNING "\n\n" ;

# --------------
# XML gen
#
pxml_end_tag      (RUNNING_XML, 'param_files') ;

$running_xml_curpos = tell(RUNNING_XML) ;
# So that running is always a readable XML file
print RUNNING_XML "\n</REPORT>\n" ;
seek(RUNNING_XML, $running_xml_curpos, 0) ;


# -------------------------------------------------------------------------------------
# Creating all XML empty reports

# Table telling if master script is generic
@is_generic = () ;

foreach my $id_path ( 0 .. $#run_paths) {
	my $run_path = $run_paths[$id_path] ;

	my @script_lines = read_alllines("$run_path/${run_all_script}") ;
	# Temporary version : limited to master scripts that generate XML report or generic master script
	if ((grep (/^\s*use\s+qa_xml\s*;/, @script_lines))
	     or (grep (/^exec\(\"\$ENV\{\'QA_TOOLS\'\}\/generic_test\/(codec|unit_tests)\/run_all_generic.pl\", *\@ARGV/, @script_lines))) {

        $is_generic[$id_path] = 1 ;

        foreach my $id_variant ( 0 .. $#{$options[$id_path]}) {
			chdir "$run_path" ;
			my @args = @{$options[$id_path][$id_variant]} ;
			# Index of the test to run in the scenario
			my $scn_idx = $scn_indexes[$id_path][$id_variant] ;

			foreach $arg (@args) {
				if ($arg =~  /^\"([^\"]+)\"$/) {
					$arg =~ s/^\"([^\"]+)\"$/$1/;
				}
				elsif ($arg =~ /^\'([^\']+)\'$/) {
					$arg =~ s/^\'([^\']+)\'$/$1/;
				}
			}
			unshift(@args, '-v', $version, '-empty', '-scn_idx', $scn_idx) ;
			# DEBUG
			print STDOUT "cd $run_path", "\n" , join(' ', "./${run_all_script}", @args), "\n" ;
			system("./${run_all_script}", @args) == 0 or warn "Can't exec ${run_all_script}: $?\n" ;
		}
	}
	else {
        $is_generic[$id_path] = 0 ;
		foreach my $id_variant ( 0 .. $#{$options[$id_path]}) {
			# Temporary version : limited to generic master scripts
			$scn_indexes[$id_path][$id_variant] = -1 ;
		}
	}
}

# ========================== REAL EXECUTION ===========================================
$id_path = 0 ;

RUN_ALL:
while ($#run_paths >= 0) {

	chdir "$runtest_dir" ;
	my $run_path = $run_paths[$id_path] ;

	# lock the file "run_all"
	while ( ($#run_paths >= 0) &&
		(    (not( -x "$run_path/${run_all_script}"))
		  || (not(sec_lock("$run_path/${run_all_script}")))
		)
	  ) {

	if (not( -x "$run_path/${run_all_script}")) {
		print STDERR  "File $run_path/${run_all_script} is not executable.\n\n" ;
		print RUNNING "File $run_path/${run_all_script} is not executable.\n\n" ;
		splice(@run_paths,   $id_path, 1) ;
		splice(@options,     $id_path, 1) ;
		splice(@scn_indexes, $id_path, 1) ;
		if ($#run_paths >= 0) {
		$id_path = $id_path % ($#run_paths + 1) ;
		}
	}
	else {
		$now_string = localtime ;
		printf STDOUT  "%25s  Skip  %s (locked)\n", $now_string, $run_path ;
	#            printf RUNNING "%25s  Skip  %s (locked)\n", $now_string, $run_path ;
		$id_path = ($id_path + 1) % ($#run_paths + 1) ;
		sleep 10 ;
	}
	$run_path = $run_paths[$id_path] ;
	}
	if ($#run_paths >= 0) {

	# Variant of options for the same run_path
	$id_variant = 0 ;

	while ($#{$options[$id_path]} >= 0) {
		chdir "$run_path" ;

		# Index of the test to run in the scenario
		$scn_idx = $scn_indexes[$id_path][$id_variant] ;

		if ( -e "$runtest_dir/stop.$version" ) {
		print STDERR "\n\nFile stop.$version found, stopping.\n" ;
		unlink "$runtest_dir/stop.$version" ;
		$online = 0 ;
		my_handler(INT) ;
		exit 0 ;
		}

		# Trace the beginning of the test
		$now_string = localtime ;
		printf STDOUT  "\n%25s  Begin %s %s\n", $now_string,
						  $run_path,
						  join(' ', @{$options[$id_path][$id_variant]}) ;
		printf RUNNING "\n%25s  Begin %s %s\n", $now_string,
						  $run_path,
						  join(' ', @{$options[$id_path][$id_variant]}) ;

		# -------------------------------------------------
		# Call of run_all

		my $pid ;
		$pid = open($KID_TO_READ, "-|") ;

		if ($pid) {   # parent

		system($ENV{'QA_TOOLS'}."/stop_poll.pl $version $pid &" ) ;

		while (<$KID_TO_READ>) {
			tr/\015//d ;
			print ;
		}

		unless (close($KID_TO_READ)) {
			$exit_value = $? >> 8 ;
			$signal_num = $? & 127 ;

			SWITCH_SIG:  {                # see <signal.h> or man -s 3HEAD signal
			if ($signal_num == 2 ||
				$signal_num == 13) { print STDERR     "User Break in $run_path/${run_all_script}\n" ;
						 print RUNNING    "User Break in $run_path/${run_all_script}\n" ;
						 print ALL_REPORT "User Break in $run_path/${run_all_script}\n" ;
						 last SWITCH_SIG ;
						   }
			if ($signal_num == 0)  { if ($exit_value == 30) {
							 print STDERR     "Timeout in $run_path/${run_all_script}\n" ;
							 print RUNNING    "Timeout in $run_path/${run_all_script}\n" ;
							 print ALL_REPORT "Timeout in $run_path/${run_all_script}\n" ;
							 last SWITCH_SIG ;
						 }
						 else {
							 print STDERR     "Fatal error in $run_path/${run_all_script}\n" ;
							 print RUNNING    "Fatal error in $run_path/${run_all_script}\n" ;
							 print ALL_REPORT "Fatal error in $run_path/${run_all_script}\n" ;

							 last SWITCH_SIG ;
						 }
						   }
			print STDERR     "exit_value: $exit_value\n" ;
			print RUNNING    "exit_value: $exit_value\n" ;
			print ALL_REPORT "exit_value: $exit_value\n" ;
			print STDERR     "signal_num: $signal_num\n" ;
			print RUNNING    "signal_num: $signal_num\n" ;
			print ALL_REPORT "signal_num: $signal_num\n" ;
			last SWITCH_SIG ;
			} ; # End of SWITCH_SIG
		} ; # end of unless (close($KID_TO_READ))
		}
		else {      # child
		($EUID, $EGID) = ($UID, $GID); # suid only
		@args = @{$options[$id_path][$id_variant]} ;
		foreach $arg (@args) {
			if ($arg =~  /^\"([^\"]+)\"$/) {
			$arg =~ s/^\"([^\"]+)\"$/$1/;
			}
			elsif ($arg =~ /^\'([^\']+)\'$/) {
			   $arg =~ s/^\'([^\']+)\'$/$1/;
			}
		}
        # If we want to have atomic fail reports
        unshift(@args, '-atomic_fail_reports') if ($is_generic[$id_path] and $atomic_fail_reports) ;

		# If the master script can handle the -scn_idx parameter (for now, if it is a generic one)
        unshift(@args, '-scn_idx', $scn_idx) if ($scn_idx != -1) ;

        unshift(@args, '-v', $version) ;
		print STDOUT "cd $run_path", "\n" , join(' ', "./${run_all_script}", @args), "\n" ;
		exec("./${run_all_script}", @args) || die "Can't exec program: $!" ;
		# NOTREACHED
		exit 0 ;
		} # end if ($pid)


		# Trace the end of the test
		my $params = join(' ', @{$options[$id_path][$id_variant]}) ;

		printf ALL_REPORT "$run_path/${run_all_script} ", $params, "\n" ;

		$now_string = localtime ;
		($user,$system,$cuser,$csystem) = times ;
		printf STDOUT  "%25s  End   %s %s\n\n", $now_string, $run_path, $params ;
		printf RUNNING "%25s  End   %s %s\n",   $now_string, $run_path, $params ;
		printf RUNNING "%25s  Times (user=%s, system=%s, cuser=%s, csystem=%s)\n\n",
					"", timef($user - $user0), timef($system - $system0),
					   timef($cuser - $cuser0),  timef($csystem - $csystem0) ;
		($user0,$system0,$cuser0,$csystem0) = ($user,$system,$cuser,$csystem) ;

		splice(@{$options[$id_path]},     $id_variant, 1) ;
		splice(@{$scn_indexes[$id_path]}, $id_variant, 1) ;
		$id_variant = 0 ;


        # Copy of the XML local report
        #
        # Concatenation of the test report to the global report
        unless ($scn_idx == -1) {
            chdir $runtest_dir ;
            my $report = "$run_path/reports/report_$version.xml" ;
            stat("$report") ;
            unless ( -f _ && -r _  ) {
                print STDERR "Warning: file $report not found.\n" ;
                $report = "$run_path/reports/report_$version.draft.xml" ;
            }
            stat("$report") ;
            if ( -f _ && -r _  ) {
                if (open REPORT, "<$report") {
                    # DEBUG print STDOUT "\n INCLUDING $report", exists($report_curpos{$report}) ? (' at ' . $report_curpos{$report}) : '', "\n" ; # DEBUG
                    seek(REPORT, $report_curpos{$report}, 0) if (exists($report_curpos{$report})) ;
                    print RUNNING_XML "\n\n" ;
                    COPY_XML1:
                    while (<REPORT>) {
                        if (/^ *<TEST *scn_idx="$scn_idx"[^>]*>/) {
                            # We remove heading spaces
                            s/^  *</</ ;
                            tr/\015//d ;
                            print RUNNING_XML ;
                            last COPY_XML1 ;
                        }
                    }
                    $report_curpos{$report} = tell(REPORT) ;
                    # We copy the test report
                    COPY_XML2:
                    while (<REPORT>) {
                        # We remove heading spaces
                        s/^  *</</ ;
                        tr/\015//d ;
                        print RUNNING_XML ;
                        last COPY_XML2 if (/^\s*<\/TEST[^>]*>/) ;
                        $report_curpos{$report} = tell(REPORT) ;
                    }
                    close REPORT ;
                    $running_xml_curpos = tell(RUNNING_XML) ;
                    # So that running is always a readable XML file
                    print RUNNING_XML "\n</REPORT>\n" ;
                    seek(RUNNING_XML, $running_xml_curpos, 0) ;

                    $last_scn_indexes_reported[$id_path] = $scn_idx ;
                }
                else {
                    print STDERR "ERROR: file $report is unreadable.\n" ;
                }
            }
            else {
                print STDERR "ERROR: file $report not found.\n" ;
            }
        } # end unless ($scn_idx == -1)
    } # end of while $#{$options[$id_path]} >= 0

	chdir $runtest_dir ;

	# unlock the file "run_all"
	sec_unlock("$run_path/${run_all_script}") ;

	push (@runned_paths, splice(@run_paths, $id_path, 1)) ;
	splice(@options,     $id_path, 1) ;
	splice(@scn_indexes, $id_path, 1) ;
    splice(@is_generic,  $id_path, 1) ;
	$id_path = 0 ;
	} # end if ($#run_paths >= 0)
} # end of while ($#run_paths >= 0)

# -------------------------------------------------------------------------------------

FIN_new_run_allapp:
printf RUNNING "\nEnd $scriptname, Times (user=%s, system=%s, cuser=%s, csystem=%s)\n",
		   timef($user0), timef($system0), timef($cuser0),  timef($csystem0) ;

if ($tar_report) {
	print RUNNING "\nConcatenation of the reports made by: 'new_allapp_reports_pack.pl -v $version -tar $runtest_dir/scenarios/report_order.scn'\n\n" ;
	print STDOUT  "\nLaunching the concatenation of the reports (new_allapp_reports_pack.pl -v $version -tar $runtest_dir/scenarios/report_order.scn)\n" ;
	@args = ('-v', "$version", '-tar', "$runtest_dir/scenarios/report_order.scn") ;
}
else {
	print RUNNING "\nConcatenation of the reports made by: 'new_allapp_reports_pack.pl -v $version $runtest_dir/scenarios/report_order.scn'\n\n" ;
	print STDOUT  "\nLaunching the concatenation of the reports (new_allapp_reports_pack.pl -v $version $runtest_dir/scenarios/report_order.scn)\n" ;
	@args = ('-v', "$version", "$runtest_dir/scenarios/report_order.scn") ;
}

close RUNNING ;
unless (rename "$running", "$runtest_dir/allapp_reports/allapp_report_$version") {
	print STDERR "ERROR in: rename '$running', '$runtest_dir/allapp_reports/allapp_report_$version'" ;
}

# --------------
# XML gen
pxml_atomic_element (RUNNING_XML, 'End_date', formatted_date()) ;
pxml_end_tag (RUNNING_XML, 'REPORT') ;
close RUNNING_XML ;
rename "$running_xml", "$runtest_dir/allapp_reports/allapp_report_$version.xml" ;


chdir $launching_dir ;
($EUID, $EGID) = ($UID, $GID); # suid only
exec('new_allapp_reports_pack.pl', @args) || warn "can't exec program: $!" ;
# NOTREACHED
exit 0 ;
