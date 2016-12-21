#!/usr/bin/env perl

# version:              1.0
# date of creation:     22/04/2004
# date of modification: 22/04/2004
# author:               Guerte Yves
# usage:                stop_poll.pl <test_version> <pid>
# -------------------------------------------------------------------------------------
use POSIX ;
use FileHandle ;
use IO::Handle ;
use Cwd qw(cwd chdir abs_path ) ;
use Config ;

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

# --------------------------------------------------------------------------------
# Setting the supported "stopping" signals
# SIGPIPE is the first choosed as the new_run_allapp.pl use a pipe to run master scripts
#
# Posix ones:
#       SIGPIPE	    13	     Term    Broken pipe: write to pipe with no readers
#       SIGINT	     2	     Term    Interrupt from keyboard
#       SIGQUIT	     3	     Core    Quit from keyboard
#       SIGABRT	     6	     Core    Abort signal from abort(3)
#       SIGKILL	     9	     Term    Kill signal

defined $Config{sig_name} || die "No sigs?" ;
my $i = 1 ;
foreach my $name (split(' ', $Config{sig_name})) {
    $signo{$name} = $i;
    $signame[$i] = $name;
    $i++ ;
}

my @sig_to_stop = () ;
foreach my $name (PIPE, INT, QUIT, ABRT, KILL) {
    push (@sig_to_stop, $name) if (exists $signo{$name}) ;
}
if ($#sig_to_stop == -1) {
    die "ERROR: there is no signal among PIPE, INT, QUIT, ABRT, KILL to stop processes." ;
}

# --------------------------------------------------------------------------------

if (($#ARGV == 1) and ($ARGV[1] =~ /^\d+$/)) {
    my $version = $ARGV[0] ;
    my $pid = $ARGV[1] ;

    print STDOUT "${scriptname} of pid=$$ polling stop.${version} to kill ${pid} with ", join(' ', @sig_to_stop), " signals.\n" ;

    # While the process is running
    while (kill 0 => $pid) {
        if ( -e "$runtest_dir/stop.$version" ) {

            my $i_sig = 0 ;
            while (kill 0 => $pid) {
                print STDERR "\n\nFile stop.$version found, sending SIG", $sig_to_stop[$i_sig], " to process $pid.\n" ;
                kill($sig_to_stop[$i_sig], $pid) ;
                $i_sig = ($i_sig + 1) % ($#sig_to_stop + 1) ;
                sleep 5 ;
            }
            exit 0 ;
        }
        else {
            sleep 10 ;
        }
    }
}
else {
    print STDOUT "Syntax: $scriptname [ -help | <version> <pid> ]", "\n" ;
    print STDOUT "        The <version> string is the version id of the test,", "\n" ;
    print STDOUT "        for example the trace file is 'running.<version>'", "\n" ;
    print STDOUT "        The <pid> number is the process id of the task to stop if 'stop.<version>' file is found", "\n" ;
    print STDOUT "        in the \$NEW_QA_ROOT/runtest directory.", "\n" ;

    exit 0 if (($#ARGV == -1) or (($#ARGV == 0) and ($ARGV[0] =~ /^(-h|-help|--help)$/i)) ) ;
    exit 1 ;
}
exit 0 ;


