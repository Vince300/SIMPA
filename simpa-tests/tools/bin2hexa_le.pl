#!/usr/bin/env perl

sub handler {		# 1st argument is signal name
	my($sig) = @_ ;
    if (defined STATUS) {close(STATUS)} ; # Broken pipe
	die "Caught a SIG$sig" ;
}
$SIG{'INT'}  = \&handler ;
$SIG{'QUIT'} = \&handler ;
$SIG{'PIPE'} = \&handler ;


@outbuf=() ;

open (STATUS, "od -v -t x1 |") || die "can't fork: $!" ;
while (<STATUS>) {
    chomp($_) ;
    @f = ($_ =~ /[0-9a-f]+/gi) ;
    push(@outbuf, @f[1..$#f]) ;
    while ($#outbuf >= 1) {
        $high = shift(@outbuf) ;
        $low  = shift(@outbuf) ;
        print substr('0' . uc($low), -2), substr('0' . uc($high), -2), "\n" ;
    }
}
if ($#outbuf = 0) {
    $low= shift(@outbuf) ;
    print substr('0' . uc($low), -2), "\n" ;
}
close STATUS || die "bad od: $! $?";
