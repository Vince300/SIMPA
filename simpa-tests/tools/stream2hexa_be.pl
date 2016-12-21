#!/usr/bin/env perl
# Parameter is stream size in words

# Stream size in bytes -1
if ($#ARGV >= 0) {$ssize = $ARGV[0] * 2 - 1} else {$ssize = 1} ;

# Stream size in words -1
if ($#ARGV >= 0) {$wssize = $ARGV[0] - 1} else {$wssize = 0} ;


sub handler {		# 1st argument is signal name
        my($sig) = @_ ;
    if (defined STATUS) {close(STATUS)} ; # Broken pipe
        die "Caught a SIG$sig" ;
}
$SIG{'INT'}  = \&handler ;
$SIG{'QUIT'} = \&handler ;
$SIG{'PIPE'} = \&handler ;


@outbuf=() ;
$offset=0 ;

open (STATUS, "od -v -t x1 |") || die "can't fork: $!" ;
printf "%07X ", $offset ;

while (<STATUS>) {
    chomp($_) ;
    @f = ($_ =~ /[0-9a-f]+/gi) ;
    push(@outbuf, @f[1..$#f]) ;
    if ($#outbuf >= $ssize) {
        for ($i=$ssize ; $i >= 0 ; $i -= 2) {
            $high = shift(@outbuf) ;
            $low  = shift(@outbuf) ;
            print substr('0' . uc($high), -2), substr('0' . uc($low), -2), " " ;
            $offset += 2 ;
        }
        printf "\n%07X ", $offset ;
    }
}
while ($#outbuf >= 0) {
            $high = shift(@outbuf) ;
            if ($#outbuf < 0) {
                print substr('0' . uc($high), -2) ;
            }
            else {
                $low  = shift(@outbuf) ;
                print substr('0' . uc($high), -2), substr('0' . uc($low), -2), " " ;
            }
}
print "\n" ;
close STATUS || die "bad od: $! $?";
