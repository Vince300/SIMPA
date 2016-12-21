#!/usr/bin/env perl

# version:              1.0
# date of creation:     17/12/2003
# date of modification: 17/12/2003
# author:               Guerte Yves
# usage:                use lib "$ENV{'QA_TOOLS'}/libperl" ; use cflags_cygfilter ;

use POSIX ;
use POSIX qw/getpgrp tcgetpgrp/;
use FileHandle ;
use IO::Handle ;
use Carp ;

if (exists($ENV{'QA_TOOLS'})) {
    use lib "$ENV{'QA_TOOLS'}/libperl" ;
    use tools ;
}
else {
    print STDERR "\nERROR, the variable QA_TOOLS must be set !\n" ;
    exit 1
}

autoflush STDOUT 1 ;
autoflush STDERR 1 ;
umask 002 ;


$PC = (sys_kind() eq 'PC') ;

# --------------------------------------------------------
# We surround by " the parameters containing a space,
# we correct the file parameter of :
# -Xicode "-F <file>",
# -Xicode "-a <file>,
# -ma <file> application configuration file,
# -mc <file> machine configuration file,
# -mem <file> memory control file
#
sub cflags_cygfilter {
    my @options = @_ ;
    my $i = $#options ;
    while ($i >= 0) {
        my $opt = no_quote_surr(no_quote_surr($options[$i])) ;
        if ($opt =~ /^-Xicode[\s]+[\'\"][\s]*-F/) {

            $opt =~ s/^-Xicode[\s]+// ;
            $opt = no_quote_surr($opt) ;

            $opt =~ s/^[\s]*-F[\s]*// ;
            $opt = no_quote_surr($opt) ;

            if ($PC) {
                $opt = `cygpath -m "$opt"`  ;
                chomp $opt ;
            }
            splice(@options, $i, 1, quotes_surround('-Xicode', "-F $opt")) ;
        }
        elsif ($opt =~ /^-Xicode[\s]+[\'\"][\s]*-a/) {

            $opt =~ s/^-Xicode[\s]+// ;
            $opt = no_quote_surr($opt) ;

            $opt =~ s/^[\s]*-a[\s]*// ;
            $opt = no_quote_surr($opt) ;

            if ($PC) {
                $opt = `cygpath -m "$opt"`  ;
                chomp $opt ;
            }
            splice(@options, $i, 1, quotes_surround('-Xicode', "-a $opt")) ;
        }
        elsif (($opt =~ /^-Xicode$/) and defined($options[$i + 1])) {

            $opt = no_quote_surr(no_quote_surr($options[$i + 1])) ;
            if ($opt =~ /^-F[\s]+/) {

                $opt =~ s/^-F[\s]+// ;
                $opt = no_quote_surr(no_quote_surr($opt)) ;

                if ($PC) {
                    $opt = `cygpath -m "$opt"`  ;
                    chomp $opt ;
                }
                splice(@options, $i + 1, 1, quotes_surround("-F $opt")) ;
            }
            elsif ($opt =~ /^-a[\s]+/) {

                $opt =~ s/^-a[\s]+// ;
                $opt = no_quote_surr(no_quote_surr($opt)) ;

                if ($PC) {
                    $opt = `cygpath -m "$opt"`  ;
                    chomp $opt ;
                }
                splice(@options, $i + 1, 1, quotes_surround("-a $opt")) ;
            }
        }
        elsif (($opt =~ /^-(ma|mc|mem)$/x) and defined($options[$i + 1])) {
            my $opt = no_quote_surr(no_quote_surr($options[$i + 1])) ;

            if ($PC) {
                $opt = `cygpath -m "$opt"`  ;
                chomp $opt ;
                splice(@options, $i + 1, 1, $opt) ;
            }
        }
        elsif (($opt !~ /^[\'\"]/) and ($opt =~ /[^\\]\s/)) {
            splice(@options, $i, 1, quotes_surround($opt)) ;
        }
        $i-- ;
    }
    return @options ;
}
# ------------------ End of library ----------------------------------

1 ;


