#!/usr/bin/env perl

# This script allows to launch a tcsh command from any PC/Station to a PC.
# The target PC must have its %CYG_PATH% MS/DOS variable set with the root of Cygwin.
# The target PC must have tcsh_server.bat and tcsh_server.csh in the root of Cygwin.

use Socket;
use POSIX qw/getpgrp tcgetpgrp/;

if (exists($ENV{'QA_TOOLS'})) {

    use lib "$ENV{'QA_TOOLS'}/libperl" ;
    use cyg_rexec;
}
else {
    print STDERR "Variable QA_TOOLS must be set !\n" ;
    exit 1
}

$help = 0 ;
@o_args = () ;
$scriptname = $0 ;
$scriptname =~ s/[^\/]*\///g ;
$rusername = $ENV{'USER'} ;
$cygwin = 0 ;

if ($#ARGV < 1) {
    $help = 1;
}
else {
    while ($#ARGV >= 0) {
    
        SWITCH_ARGS: {
    
            if ($ARGV[0] =~ /^-l$/i ) {
                                           shift @ARGV ;
                                           if ($#ARGV >= 0) {
                                               $rusername = shift @ARGV ;
                                           }
                                           else {
                                               print STDERR "Error with the '-l' parameter.\n" ;
                                               $help = 1 ;
                                           }
                                           last SWITCH_ARGS ;
            }
            if ($ARGV[0] =~ /^-cygwin$/i ) {
                                           shift @ARGV ;
                                           $cygwin = 1 ;
                                           last SWITCH_ARGS ;
            }
            push (@o_args, (shift @ARGV)) ;
    
        } # end SWITCH_ARGS
    }
}

if ($help) {
    print "Usage:\n" ;
    print "$scriptname host [-l username] [-cygwin] command\n" ;
    exit 1;
}
$rhostname = shift @o_args ;

$rhostaddr = inet_aton($rhostname) ;
if (not defined($rhostaddr)) {
    print "The host $rhostname is unknown.\n" ;
    exit 1
}


$cmd = join(' ', @o_args) ;


open(TTY, "/dev/tty") or die $!;
$tpgrp = tcgetpgrp(TTY);
$pgrp = getpgrp();
if ($tpgrp == $pgrp) {
    # foreground
    system "stty -echo";
    print "Password: ";
    chop($password = <STDIN>);
    print "\n";
    system "stty echo";
} else {
    # background
    chop($password = <STDIN>);
}

print STDOUT    "rexec($rhostname, '$cmd', $rusername, \$password) ;\n" ;
($rc, @output) = cyg_rexec($rhostname, $cygwin, $cmd, $rusername, $password)
    or die "$scriptname failed: $!\n" ;

foreach (@output) { print $_, "\n" } ;
if ($rc) {
    print STDERR "$scriptname failed.\n" ;
}

exit $rc ;

