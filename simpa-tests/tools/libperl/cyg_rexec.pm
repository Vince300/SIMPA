#!/bin/perl

# version:              1.2
# date of creation:     ??/??/200?
# date of modification: 20/01/2003
# author:               Guerte Yves
# usage:                use lib '/home/comtools/tools/libperl' ; use cyg_rexec

# This script allows to launch a tcsh command from any PC/Station to a PC.
# The target PC must have its %CYG_PATH% MS/DOS variable set with the root of Cygwin.
# The target PC must have tcsh_server.bat and tcsh_server.csh in the root of Cygwin.

use IO::Socket;
use Carp;
use Net::hostent;

if (exists($ENV{'QA_TOOLS'})) {

    use lib "$ENV{'QA_TOOLS'}/libperl" ;
    use Net::Netrc ;
    use Net::Rexec 'rexec';
}
else {
    print STDERR "Variable QA_TOOLS must be set !\n" ;
    exit 1
}

autoflush STDOUT 1 ;
autoflush STDERR 1 ;

# ---------------------------------------------------------------------------------------
# PARAMETERS

# Port from which we get the status for the cyg_rexecr function
my $PORT = 9001;

my $EOL = "\015\012";
my $max_msglen = 1024;

# ---------------------------------------------------------------------------------------
# Rexec to unix or PC with cygwin
# The 2nd parameter must be 1 when the remote computer is a PC with cygwin

sub cyg_rexec {
    my $rhostname = shift ;
    my $cygwin    = shift ;
    my $cmd       = shift ;
    my $rusername = shift ;
    my $password  = shift ;
    
    if ($cygwin) {
        $rexec_cmd = "cmd.exe /K \"\%CYG_DRIVE\%\%CYG_PATH\%\\tcsh_server.bat " . $cmd . "\"" ;
    }
    else {
        $rexec_cmd = $cmd ;
    }
    
    my ($rc, @output) = rexec($rhostname, $rexec_cmd, $rusername, $password)
        or print STDERR "rexec failed: $!\n" ;

    foreach (@output) { chomp ; s/[\015\012]$// } ;
    return ($rc, @output) ;
}

# ---------------------------------------------------------------------------------------
# Bloquant rexec to unix or PC with cygwin
# The 2nd parameter must be 1 when the remote computer is a PC with cygwin
# The rexec waits for a status of the execution of the remote command
# The 4rd parameter must be 0 for no timeout

sub cyg_rexec_b {
    my $rhostname = shift ;
    my $cygwin    = shift ;
    my $cmd       = shift ;
    my $timeout   = shift ;
    my $rusername = shift ;
    my $password  = shift ;
    
    if ($cygwin) {
        my $HOSTNAME = `uname -n` ;
        chomp $HOSTNAME ;
        #  $HOSTNAME = inet_ntoa(inet_aton($HOSTNAME)) ;
        
        $rexec_cmd = "cmd.exe /K \"\%CYG_DRIVE\%\%CYG_PATH\%\\tcsh_server_b.bat " . "$HOSTNAME " . "$PORT " . $cmd . "\"" ;
    }
    else {
        $rexec_cmd = $cmd ;
    }
    
    my ($rc, @output) = rexec($rhostname, $rexec_cmd, $rusername, $password)
        or print STDERR "rexec failed: $!\n" ;

    foreach (@output) { chomp ; s/[\015\012]$// } ;
    
    if ($cygwin) {
        # if there is an error
        if ($rc) {
            return ($rc, @output) ;
        }
        else {

            my $server = IO::Socket::INET->new( Proto     => 'tcp',
                                                 LocalPort => $PORT,
                                                 Listen    => SOMAXCONN,
                                                 Reuse     => 1,
                                                 Timeout   => $timeout);
            
            unless ($server) {
                push(@output, "Can't setup server for getting status\n") ;
                return (1, @output) ;
            }
            else {
                unless ($client = $server->accept()) {
                    push(@output, "No answer getting status\n") ;
                    return (1, @output) ;
                }
                    
                $client->autoflush(1);
                $hostinfo = gethostbyaddr($client->peeraddr);
                  
                # DEBUG printf "[Connect from %s]\n", $hostinfo->name || $client->peerhost;

                my $status = <$client> ;
                chomp $status ;
                $status =~ s/[\015\012]$// ;
                
                # DEBUG printf "[Status=%s]\n", $status ;
                
                close $client;
                return ($status, @output) ;
            }

        }
    }
    else {
        return ($rc, @output) ;
    }
}

1 ;

