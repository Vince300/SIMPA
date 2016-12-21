#!/usr/bin/env perl

# version:              1.0
# date of creation:     03/09/2004
# date of modification: 15/09/2004
# author:               Guerte Yves
# usage:                copy_running.pl -r <run_id> -p <pid> [ -s <shared_directory> | -ftp_host <host> -ftp_port <port> ]
# -------------------------------------------------------------------------------------
use POSIX ;
use FileHandle ;
use IO::Handle ;
use Sys::Hostname;
use Cwd qw(cwd chdir abs_path ) ;
use File::Basename ;
use Getopt::Long qw(:config no_ignore_case permute pass_through) ;
use filetest 'access';

# Number of second between each running file scrutation
$polling_delay = 5 ;

# The runtest directory is $NEW_QA_ROOT/runtest directory
#
if (exists($ENV{'NEW_QA_ROOT'}) and exists($ENV{'QA_TOOLS'})) {

	unless(eval{$runtest_dir = abs_path("$ENV{'NEW_QA_ROOT'}/runtest")}) {
		print STDERR "ERROR: '$ENV{'NEW_QA_ROOT'}/runtest': No such directory.\n" ;
		exit 1 ;
	}
	$runtest_dir =~ s/\/*$// ;
}
else {
	print STDERR "Variables NEW_QA_ROOT and QA_TOOLS must be set !\n" ;
	exit 1
}
my $launching_dir = cwd() ;

autoflush STDOUT 1 ;
autoflush STDERR 1 ;

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
# --------------------------- MAN -------------------------------------------------------
# Manual

sub man {
	print STDOUT "usage: $scriptname [-h | -help] -r <run_id> -p <process_id> -s <shared_directory> \n" ;
	print STDOUT "\n" ;
	print STDOUT "OPTIONS:\n" ;
	print STDOUT "-h, -help             : to get this help message,\n" ;
	print STDOUT "-r <RUN_ID>           : run_id of the test session whose trace must be copied,\n" ;
	print STDOUT "-p <PROCESS_ID>       : process ID of the scenario interpreter (new_run_allapp.pl) running the test session,\n" ;
	print STDOUT "-s <SHARED_DIRECTORY> : path of the directory where the running file must be copied (in a 'running' dir),\n" ;
    print STDOUT "-ftp_host <HOST>      : unused \n" ;
    print STDOUT "-ftp_port <PORT>      : unused \n" ;
	print STDOUT "\n" ;
}

# --------------------------- WE READ THE PARAMETERS ------------------------------------

# With no parameter: manual
#
if ($#ARGV == -1) {
		man() ;
		exit 1 ;
}
$debug          = undef ;
$help           = undef ;
$run_id         = undef ;
$pid    		= undef ;
$shareddir     = undef ;
@unknown_params = () ;

sub add_unknown_params {
	push(@unknown_params, @_);
}

$ok_params = GetOptions('h|help'	=> \$help,
						'd|debug'	=> \$debug,
						'r=s'       => \$run_id,
						'p=s'       => \$pid,
						's=s'       => \$shareddir,
						'<>'		=> \&add_unknown_params) ;

# --------------------------------------------------------
# Are all the parameters OK ?
#
if ($#unknown_params != -1) {
	print STDERR "ERROR, unknown parameters: ", join(', ', @unknown_params), "\n" ;
	$ok_params = 0 ;
}
else {
	$ok_params = defined($run_id) and defined($pid) and defined($shareddir) ;
}

if ($help) {
	man() ;
	exit 0 ;
}

unless ($ok_params) {
	man() ;
	exit 1 ;
}

# --------------------------- tools ------------------------------------
$running_fname    = undef ;
$RUNNING_FHANDLE = undef ;

sub open_running {
	my @filenames = glob("$runtest_dir/running.v${run_id}_*") ;
	$running_fname = $filenames[0] if (@filenames) ;
	if ($running_fname) {
		if (-r "$running_fname") {
			open $RUNNING_FHANDLE, "<$running_fname" ;
		}
	}
}

$copy_dir      = "$shareddir/running" ;
# We create the running dir if it does not exist
system('mkdir', '-p', "$copy_dir") ;

$copy_fname    = undef ;
$COPY_FHANDLE = undef ;

$finished_fname = undef ;

sub copy_running {
	if (not defined($copy_fname)) {
		if (defined($running_fname)) {
			$copy_fname = "${copy_dir}/${HOST}." . basename($running_fname) ;
			$finished_fname = basename($running_fname) ;
			$finished_fname =~ s/running/finished/ ;
			$finished_fname = "${copy_dir}/${HOST}." . $finished_fname ;

			open $COPY_FHANDLE, ">$copy_fname" or die "Cannot create $copy_fname." ;
			autoflush $COPY_FHANDLE 1 ;
			print STDOUT "File $copy_fname created." if ($debug) ;
		}
	}
	if (defined($COPY_FHANDLE)) {

		# We copy the running file to the shared drive
		seek($RUNNING_FHANDLE, 0, 1) ;
		COPY_RUNNING:
		while (<$RUNNING_FHANDLE>) {
			tr/\015//d ;
			print $COPY_FHANDLE $_ ;
			print if ($debug) ;
		}
	}
}
# --------------------------- REAL BEGINNING ------------------------------------


# if the running trace file exists, we open it
open_running() ;

# While the process is living
WHILE_PID_LIVES:
while ((kill 0 => $pid) and (not defined($RUNNING_FHANDLE))) {

	# If the running trace file is not opened and exists, we open it
	open_running() ;
	sleep $polling_delay ;
}
if (defined($RUNNING_FHANDLE)) {
	while ((-e $running_fname) and (kill 0 => $pid)) {
		copy_running() ;
		sleep $polling_delay ;
	}
}
copy_running() if (defined($RUNNING_FHANDLE)) ;

close $RUNNING_FHANDLE ;
close $COPY_FHANDLE ;

if (defined($finished_fname)) {
	if (-r $copy_fname) {
		rename $copy_fname, $finished_fname ;
	}
}
exit 0 ;

