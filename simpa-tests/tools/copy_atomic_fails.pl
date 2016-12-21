#!/usr/bin/env perl

# version:              1.0
# date of creation:     16/03/2005
# date of modification: 16/03/2005
# author:               Guerte Yves
# usage:                copy_atomic_fails.pl -r <run_id> -p <pid> [-s <shared_directory> | -ftp_host <hostname> -ftp_port <port_number>]
# -------------------------------------------------------------------------------------
use POSIX ;
use FileHandle ;
use IO::Handle ;
use Sys::Hostname;
use Cwd qw(cwd chdir abs_path ) ;
use File::Temp qw/tempfile/ ;
use File::Basename ;
use File::Copy ;
use Getopt::Long qw(:config no_ignore_case permute pass_through) ;
use filetest 'access';

# Number of second between each running file scrutation
$polling_delay = 5 ;

# User name on FTP hostname
$qa_user = 'qatools' ;

# default value for FTP port
$ftp_port = 260 ;

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
	print STDOUT "usage: $scriptname [-h | -help] -r <run_id> -p <process_id> [-s <shared_directory> | -ftp_host <hostname> -ftp_port <port_number>] \n" ;
	print STDOUT "\n" ;
	print STDOUT "OPTIONS:\n" ;
	print STDOUT "-h, -help        to get this help message,\n" ;
	print STDOUT "-r, [RUN_ID]     run_id of the test session whose atomic failing reports must be copied,\n" ;
	print STDOUT "-p, [PROCESS_ID] process ID of the scenario interpreter (new_run_allapp.pl) running the test session,\n" ;
	print STDOUT "-s, [SHARED_DIRECTORY] path of the directory where the running file must be copied (in a 'atomic_fail_reports' dir).\n" ;
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
$pid            = undef ;
$shareddir      = undef ;
$ftp_host       = undef ;
$ftp_port       = undef ;
@unknown_params = () ;

sub add_unknown_params {
    push(@unknown_params, @_);
}

$ok_params = GetOptions('h|help'     => \$help,
                        'd|debug'    => \$debug,
                        'r=i'        => \$run_id,
                        'p=i'        => \$pid,
                        's=s'        => \$shareddir,
                        'ftp_host=s' => \$ftp_host,
                        'ftp_port=i' => \$ftp_port,
                        '<>'         => \&add_unknown_params) ;

# --------------------------------------------------------
# Are all the parameters OK ?
#
if ($#unknown_params != -1) {
	print STDERR "ERROR, unknown parameters: ", join(', ', @unknown_params), "\n" ;
	$ok_params = 0 ;
}
else {
    $ok_params = defined($run_id) and defined($pid) and (defined($shareddir) or defined($ftp_port)) ;
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

sub list_reports {
	# DEBUG print STDOUT "match: '$runtest_dir/atomic_fail_reports/report_v${run_id}*.xml.flagged_new'\n" ;
    my @filenames = glob("$runtest_dir/atomic_fail_reports/report_v${run_id}*.xml.flagged_new") ;
    foreach my $fname (@filenames) {
        # DEBUG print STDOUT "$fname \n" ;
        $fname =~ s/\.flagged_new$// ;
    }
    return @filenames ;
}

# We create the atomic_fail_reports source dir if it does not exist
system('mkdir', '-p', "$runtest_dir/atomic_fail_reports") unless ( -d "$runtest_dir/atomic_fail_reports") ;


# We create the atomic_fail_reports destination dir if it does not exist
unless (defined($ftp_port)) {
    $copy_dir      = "$shareddir/atomic_fail_reports" ;
    system('mkdir', '-p', "$copy_dir") unless ( -d "$copy_dir") ;
}

# --------------------------- REAL BEGINNING ------------------------------------

# While the process is living
WHILE_PID_LIVES: {
    do {
        my @new_fail_reports = list_reports() ;

        foreach my $fname (@new_fail_reports) {

            # DEBUG print STDOUT "$fname \n" ;
            # report_v3539_2005-3-16.1.Benchmarks_loop.bug_arnon.TIl7.xml

            my $name = basename(${fname}) ;
            $name =~ s/\.....\.xml// ;

            unless (defined($ftp_port)) {
                (undef, $fail_report_name) = tempfile("${name}.${HOST}.XXXX", DIR=>${copy_dir}, SUFFIX=>'.xml', OPEN=>1, UNLINK=>0)
                    or die "Can't open new atomic fail report: '${copy_dir}/${name}.${HOST}.XXXX.xml'" ;

                unless (copy(${fname}, ${fail_report_name})) {
                    warn "Can't copy '${fname}' to '${fail_report_name}'" ;
                }
                else {
                    unlink "${fname}.flagged_new" ;
                }
            }
            else {
                my @ARGS = ( $ENV{'QA_TOOLS'}.'/Other_src/update_tools/ftpput.sh', ${ftp_host}, ${ftp_port}, ${qa_user}, 'atomic_fail_reports', ${fname}, "${name}.${HOST}.${pid}.xml" ) ;

                unless (system(@ARGS) == 0) {
                    $exit_value = $? >> 8 ;
                    $signal_num = $? & 127 ;
                    print STDERR "\nERROR, ", join(' ', @ARGS), " failed: $?\n" ;
                    print STDERR "exit_value: $exit_value\n" ;
                    print STDERR "signal_num: $signal_num\n" ;
                }
                else {
                    unlink "${fname}.flagged_new" ;
                }
            }
        }
        sleep $polling_delay ;
    }
    while (kill 0 => $pid) ;
}
exit 0 ;


