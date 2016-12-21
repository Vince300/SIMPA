#!/usr/bin/env perl
#usage : $0 computer port message

use IO::Handle ;
use strict;
use Socket;

my $EOL = "\015\012";

sub test_client {
    my ($remote,$port, $message, $iaddr, $paddr, $proto, $line);

    $remote  = shift || 'localhost';
    $port    = shift || 2345 ;  # random port
    $message = shift ;

    if ($port =~ /\D/) { $port = getservbyname($port, 'tcp') }
    die "No port" unless $port;
    $iaddr   = inet_aton($remote)               || die "no host: $remote";
    $paddr   = sockaddr_in($port, $iaddr);

    $proto   = getprotobyname('tcp');
    socket(SOCK, PF_INET, SOCK_STREAM, $proto)  || die "socket: $!";
    connect(SOCK, $paddr)    || die "connect: $!";
    autoflush SOCK 1 ;

    print SOCK  $message, $EOL;
    close (SOCK)            || die "close: $!";

}

test_client(@ARGV) ;
exit 0;
