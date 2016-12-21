#!/usr/bin/env perl

# version:              1.4
# date of creation:     08/08/2001
# date of modification: 07/03/2004
# author:               Guerte Yves
# usage:                use lib "$ENV{'QA_TOOLS'}/libperl" ; use tools

use POSIX ;
use POSIX qw/getpgrp tcgetpgrp/;
use FileHandle ;
use IO::Handle ;
use Carp ;
use English ;

autoflush STDOUT 1 ;
autoflush STDERR 1 ;
umask 002 ;

# --------------------------------------------------------------------
# function that returns the array as parameter without repetition of values

sub norepet {
    my $i = $#_ ;
    while ($i > 0) {
        splice(@_, $i, 1) if ($_[$i] eq $_[$i - 1]) ;
        $i-- ;
    }
    return @_ ;
}

# --------------------------------------------------------------------
# function that returns the array as parameter without duplicated values

sub nodup {
    my %saw = () ;
    return grep(!$saw{$_}++, @_) ;
}

# --------------------------------------------------------------------
# function that returns a secure string for use as filename
#
# How can I open a file with a leading "1/4��3/4" or trailing blanks?
# Normally perl ignores trailing blanks in filenames, and interprets
# certain leading characters (or a trailing ``|'') to mean something special.
# To avoid this, you might want to use a routine like this.
# It tacks a trailing null byte on the name to make perl leave it alone:
#
sub safe_filename {
    my $fname  = shift ;
    return "$fname\0" ;
}


# --------------------------------------------------------------------
# function that reads all the nonempty lines of a text file which are not comments
sub read_goodlines {
    my $fname = safe_filename(shift) ;
    open (FILE, "< $fname") or die "Can't open the file $fname: $!" ;

    my @alllines = () ;
    READ_FILE:
    while (my $line = <FILE>) {
        chomp ($line) ;
        # We strip newline (LF, NL) ; return (CR) ; form feed (FF)
        $line =~ s/[\n\r\f]//g ;

        # We suppress leading and ending spaces from the line
        #
        $line =~ s/^\s+//;
        $line =~ s/\s+$//;

        # test of - empty line or comment,
        #
        if ((length($line) == 0) || ($line =~ '^#')) {
                next READ_FILE ;
        }
        else {
                push(@alllines, $line) ;
        }
    } # end READ_FILE
    close FILE ;
    return @alllines
}


# --------------------------------------------------------------------
# function that reads all the lines of a text file
sub read_alllines {
    my $fname = safe_filename(shift) ;
    open (FILE, "< $fname") or die "Can't open the file $fname: $!" ;

    my @alllines = () ;
    READ_FILE:
    while (my $line = <FILE>) {
        chomp ($line) ;
        # We strip newline (LF, NL) ; return (CR) ; form feed (FF)
        $line =~ s/[\n\r\f]//g ;

        push(@alllines, $line) ;
    } # end READ_FILE
    close FILE ;
    return @alllines
}


# --------------------------------------------------------------------
# function that count the lines of a text file
sub wc_l {
    my $fname = safe_filename(shift) ;
    open (FILE, "< $fname") or die "Can't open the file $fname: $!" ;

    my $nlines = 0;
    while (sysread FILE, $buffer, 4096) {
        $nlines += ($buffer =~ tr/\n//);
    }
    close FILE;
    return $nlines ;

}

# --------------------------------------------------------------------
# function that returns the path to executable that would be launched
# or return 0 instead
sub which {
    my $fname = safe_filename(shift) ;

    my @allpaths = split(/:/, $ENV{'PATH'}) ;
    my $index   = 0 ;
    my $index_f = -1 ;

    my ($dev,$ino,$mode,$nlink,$uid,$gid,$rdev,$size,$atime,$mtime,$ctime,$blksize,$blocks) = ('','','','','','','','','','','','','') ;

#DEBUG    sub print_stat {
#DEBUG        printf "
#DEBUG            \$dev    == %s
#DEBUG            \$ino    == %s
#DEBUG            \$mode   == %s == %b
#DEBUG            \$nlink  == %s
#DEBUG            \$uid    == %s
#DEBUG            \$gid    == %s
#DEBUG            \$rdev   == %s
#DEBUG            \$size   == %s
#DEBUG            \$atime  == %s
#DEBUG            \$mtime  == %s
#DEBUG            \$ctime  == %s
#DEBUG            \$blksiz == %s
#DEBUG            \$blocks == %s
#DEBUG            \n", $dev,$ino,$mode,$mode,$nlink,$uid,$gid,$rdev,$size,$atime,$mtime,$ctime,$blksize,$blocks ;
#DEBUG    }

    while (($index <= $#allpaths) && ($index_f == -1)) {

        ($dev,$ino,$mode,$nlink,$uid,$gid,$rdev,$size,$atime,$mtime,$ctime,$blksize,$blocks) = stat("$allpaths[$index]/$fname" ) ;

        if ( -x _ ) {
#DEBUG            print_stat() ;
             $index_f = $index ;
        }
        elsif (( -f _ ) and (sys_kind() eq 'PC') and (($fname =~ /\.exe$/) or ( -f "$allpaths[$index]/$fname.exe")) ) {

#DEBUG            print_stat() ;
            $index_f = $index ;
        }
        else {
            $index++ ;
        }
    }
    if ($index_f == -1) {
        return undef ;
    }
    else {
        return "$allpaths[$index_f]" ;
    }
}

# --------------------------------------------------------------------
# function that returns kind of system on which we are
sub sys_kind {
    my $syst = $^O ;
    if    ($syst =~ /dos|os2|MSWin32|cygwin/i) { return 'PC' ; }
    elsif ($syst =~ /aix|bsdos|dgux|dynixptx|freebsd|linux|hpux|irix|rhapsody|machten|next|openbsd/i
           || $syst =~ /dec_osf|svr4|sco_sv|svr4|unicos|unicosmk|solaris|sunos/i) { return 'UNIX' ; }
    else { return 'unknown' ; }
}

# --------------------------------------------------------------------
# function that does a file comparaison
# and returns 1 if files are differents.
#
sub diff {
    if ($#_ != 1) {
        die "The diff function needs 2 and only 2 operands." ;
    }
    else {
        my $fname1 = safe_filename(shift) ;
        my $fname2 = safe_filename(shift) ;
        my $bufsz  = 4096 ;

        open FILE1, "< $fname1" or die "Can't open the file ${fname1}." ;
        open FILE2, "< $fname2" or die "Can't open the file ${fname2}." ;

        binmode FILE1 ; binmode FILE2 ;
        my $buf1 = my $buf2 = '' ;

        while ( ($sz1 = read(FILE1, $buf1, $bufsz)) == ($sz2 = read(FILE2, $buf2, $bufsz))
                and ($sz1 != 0)
              ) {
            if ($buf1 ne $buf2) {
                close FILE1 ; close FILE2 ;
                return 1 ;
            }
        }
        close FILE1 ; close FILE2 ;
        return ($sz1 != $sz2) ;
    }
}

# --------------------------------------------------------------------
# function that does a file comparaison
# and return O or () if files are equals.
# else it returns an array with the index of the first byte which differs.
#
sub compare {
    if ($#_ != 1) {
        die "The compare function needs 2 and only 2 operands." ;
    }
    else {
        my $fname1 = safe_filename(shift) ;
        my $fname2 = safe_filename(shift) ;
        my $bufsz  = 4096 ;
        my $bufcnt = 0 ;

        open FILE1, "< $fname1" or die "Can't open the file ${fname1}." ;
        open FILE2, "< $fname2" or die "Can't open the file ${fname2}." ;

        binmode FILE1 ; binmode FILE2 ;
        my $buf1 = my $buf2 = '' ;

        $sz1 = read(FILE1, $buf1, $bufsz) ;
        $sz2 = read(FILE2, $buf2, $bufsz) ;

        while ( ($sz1 != 0) and ($sz1 == $sz2) and ($buf1 eq $buf2)) {
            $bufcnt += $sz1 ;
            $sz1 = read(FILE1, $buf1, $bufsz) ;
            $sz2 = read(FILE2, $buf2, $bufsz) ;
        }
        close FILE1 ; close FILE2 ;

        if (($sz1 == 0) and ($sz1 == $sz2)) {

            # There is no difference
            return wantarray ? () : 0 ;
        }
        else {
            if ($sz1 == 0) {
                return wantarray ? ( $bufcnt + 1 ) : 1 ;
            }
            else {
                unless (wantarray) {
                    return 1 ;
                }
                else {
                    my $lmin =  ($sz1 < $sz2) ? $sz1 : $sz2 ;
                    my $i = 0 ;
                    while ( $i <= $lmin and (substr($buf1, $i, 1) eq substr($buf2, $i, 1))) {
                        $i++ ;
                    }
                    my @res = ( $bufcnt + $i + 1 ) ;
                    return @res ;
                }
            }
        }
    }
}

# --------------------------------------------------------------------------------
# this function launch another application and returns its standard and error output together
sub execute_it {
    my @cmd = @_ ;
    my @res = () ;
    my $sleep_count = 0;
    do {
        $pid = open(KID_TO_READ, "-|");
        unless (defined $pid) {
            warn "cannot fork: $!";
            die "bailing out" if $sleep_count++ > 6;
            sleep 10;
        }
    } until defined $pid;
    if ($pid) {   # parent

        local $SIG{INT} = local $SIG{QUIT} = local $SIG{PIPE} =
            sub {
                my $sig = shift ;
                print STDERR "Process $$ caught a SIG${sig}.\n" ;
                print STDERR "Killing process ${pid}.\n" ;
                kill $sig, $pid ;
                waitpid($pid ,0) ;
                exit 2 ;
            } ;

        while (<KID_TO_READ>) {
            chomp $_ ;
            # We strip newline (LF, NL) ; return (CR) ; form feed (FF)
            s/[\n\r\f]//g ;
            push (@res, $_) ;
        }
        unless (close(KID_TO_READ)) {
            $exit_value = $? >> 8 ;
            $signal_num = $? & 127 ;
            # print STDERR join(' ', @cmd), " failed: $?\n" ;
            # print STDERR "exit_value: $exit_value\n" ;
            # print STDERR "signal_num: $signal_num\n\n" ;
            if (($signal_num == 2) || ($signal_num == 125)) {
                # print STDERR "Killing process ${pid}.\n" ;
                kill INT, $pid ;
                waitpid($pid ,0) ;
                exit 2 ;
            }
        }
    # end of parent
    }
    else {      # child
        open(OLDERR, ">&STDERR");
        open(STDERR, ">&STDOUT") || die "Can't dup STDOUT";
        ($EUID, $EGID) = ($UID, $GID); # suid only
        $OUTPUT_AUTOFLUSH = 1;
        exec(@cmd) || die "Can't exec program " . join(' ', @cmd) . ": $!";
        # NOTREACHED
    }
    # print STDOUT join("\n", @res) , "\n" ;
    return @res ;
}

# --------------------------------------------------------------------------------
# this function launch another application and returns its standard output
sub execute_it_stdout {
    my @cmd = @_ ;
    my @res = () ;
    my $sleep_count = 0;
    do {
        $pid = open(KID_TO_READ, "-|");
        unless (defined $pid) {
            warn "cannot fork: $!";
            die "bailing out" if $sleep_count++ > 6;
            sleep 10;
        }
    } until defined $pid;
    if ($pid) {   # parent

        local $SIG{INT} = local $SIG{QUIT} = local $SIG{PIPE} =
            sub {
                my $sig = shift ;
                print STDERR "Process $$ caught a SIG${sig}.\n" ;
                print STDERR "Killing process ${pid}.\n" ;
                kill $sig, $pid ;
                waitpid($pid ,0) ;
                exit 2 ;
            } ;

        while (<KID_TO_READ>) {
            chomp $_ ;
            # We strip newline (LF, NL) ; return (CR) ; form feed (FF)
            s/[\n\r\f]//g ;
            push (@res, $_) ;
        }
        unless (close(KID_TO_READ)) {
            $exit_value = $? >> 8 ;
            $signal_num = $? & 127 ;
            print STDERR join(' ', @cmd), " failed: $?\n" ;
            print STDERR "exit_value: $exit_value\n" ;
            print STDERR "signal_num: $signal_num\n\n" ;
            if (($signal_num == 2) || ($signal_num == 125)) {
                print STDERR "Killing process ${pid}.\n" ;
                kill INT, $pid ;
                waitpid($pid ,0) ;
                exit 2 ;
            }
        }
    # end of parent
    }
    else {      # child
        ($EUID, $EGID) = ($UID, $GID); # suid only
        $OUTPUT_AUTOFLUSH = 1;
        exec(@cmd) || die "Can't exec program " . join(' ', @cmd) . ": $!";
        # NOTREACHED
    }
    # print STDOUT join("\n", @res) , "\n" ;
    return @res ;
}

# --------------------------------------------------------------------------------
# this function launch another application and returns the lines found by grep in its standard output
sub execute_it_grep_stdout {
    my $grep_str = shift ;
    my @cmd = @_ ;
    my @res = () ;
    my $sleep_count = 0;
    my $pid = undef;
    do {
        $pid = open(KID_TO_READ, "-|");
        unless (defined $pid) {
            warn "cannot fork: $!";
            die "bailing out" if $sleep_count++ > 6;
            sleep 10;
        }
    } until defined $pid;
    if ($pid) {   # parent

        local $SIG{INT} = local $SIG{QUIT} = local $SIG{PIPE} =
            sub {
                my $sig = shift ;
                print STDERR "Process $$ caught a SIG${sig}.\n" ;
                print STDERR "Killing process ${pid}.\n" ;
                kill $sig, $pid ;
                waitpid($pid ,0) ;
                exit 2 ;
            } ;

        while (<KID_TO_READ>) {
            chomp $_ ;
            # We strip newline (LF, NL) ; return (CR) ; form feed (FF)
            s/[\n\r\f]//g ;
            if (/$grep_str/) { push (@res, $_) } ;
        }
        unless (close(KID_TO_READ)) {
            $exit_value = $? >> 8 ;
            $signal_num = $? & 127 ;
            print STDERR join(' ', @cmd), " failed: $?\n" ;
            print STDERR "exit_value: $exit_value\n" ;
            print STDERR "signal_num: $signal_num\n\n" ;
            if (($signal_num == 2) || ($signal_num == 125)) {
                print STDERR "Killing process ${pid}.\n" ;
                kill INT, $pid ;
                waitpid($pid ,0) ;
                exit 2 ;
            }
        }
    # end of parent
    }
    else {      # child
        ($EUID, $EGID) = ($UID, $GID); # suid only
        $OUTPUT_AUTOFLUSH = 1;
        exec(@cmd) || die "Can't exec program " . join(' ', @cmd) . ": $!";
        # NOTREACHED
    }
    # print STDOUT join("\n", @res) , "\n" ;
    return @res ;
}

# --------------------------------------------------------------------------------
# this function launch another application and returns its standard output and stderr
sub execute_it_errbrkhdl {
    my $errhdl = shift ;
    unless ($errhdl && ref($errhdl) eq 'CODE') {
        confess "usage: execute_it_errbrkhdl(CODEREF, CODEREF, ...)" ;
    }
    my $brkhdl = shift ;
    unless ($brkhdl && ref($brkhdl) eq 'CODE') {
        confess "usage: execute_it_errbrkhdl(CODEREF, CODEREF, ...)" ;
    }
    my @cmd = @_ ;
    my @res = () ;
    my $sleep_count = 0;
    do {
        $pid = open(KID_TO_READ, "-|");
        unless (defined $pid) {
            warn "cannot fork: $!";
            die "bailing out" if $sleep_count++ > 6;
            sleep 10;
        }
    } until defined $pid;
    if ($pid) {   # parent

        local $SIG{INT} = local $SIG{QUIT} = local $SIG{PIPE} =
            sub {
                my $sig = shift ;
                print STDERR "Parent process $$ caught a SIG${sig}.\n" ;
                print STDERR "Parent killing child process ${pid}.\n" ;
                kill $sig, $pid ;
                waitpid($pid ,0) ;
                # Break handler
                &$brkhdl() ;
                #DEBUG exit 2 ;
            } ;

        while (<KID_TO_READ>) {
            chomp $_ ;
            # We strip newline (LF, NL) ; return (CR) ; form feed (FF)
            s/[\n\r\f]//g ;
            push (@res, $_) ;
        }
        unless (close(KID_TO_READ)) {
            $exit_value = $? >> 8 ;
            $signal_num = $? & 127 ;
            # No output because it might be done by &$errhdl or &$brkhdl
            # print STDERR join(' ', @cmd), " failed: $?\n" ;
            # print STDERR "exit_value: $exit_value\n" ;
            # print STDERR "signal_num: $signal_num\n\n" ;
            if (($signal_num == 2) || ($signal_num == 125)) {
                print STDERR "Parent killing child process ${pid}.\n" ;
                kill INT, $pid ;
                waitpid($pid ,0) ;
                # Break handler
                &$brkhdl() ;
            }
            else {
                # Error handler called with the status returned
                &$errhdl($?) ;
            }
        }
    # end of parent
    }
    else {      # child
        open(OLDERR, ">&STDERR") || die "Can't backup STDERR";
        open(STDERR, ">&STDOUT") || die "Can't dup STDOUT";
        # turn off STDOUT buffering
        $OUTPUT_AUTOFLUSH = 1;
        ($EUID, $EGID) = ($UID, $GID); # suid only
        exec(@cmd) || die "Can't exec program " . join(' ', @cmd) . ": $!";
        # NOTREACHED
    }
    # print STDOUT join("\n", @res) , "\n" ;
    return @res ;
}

# --------------------------------------------------------------------------------
# this function launch another application and returns its standard output
sub execute_it_stdout_errbrkhdl {
    my $errhdl = shift ;
    unless (defined($errhdl) && (ref($errhdl) eq 'CODE')) {
        die "usage: execute_it_stdout_errbrkhdl(CODEREF, CODEREF, ...)" ;
    } ;
    my $brkhdl = shift ;
    unless (defined($brkhdl) && (ref($brkhdl) eq 'CODE')) {
        die "usage: execute_it_stdout_errbrkhdl(CODEREF, CODEREF, ...)" ;
    } ;
    my @cmd = @_ ;
    my @res = () ;
    my $sleep_count = 0;
    do {
        $pid = open(KID_TO_READ, "-|");

        unless (defined $pid) {
            warn "cannot fork: $!";
            die "bailing out" if $sleep_count++ > 6;
            sleep 10;
        }
    } until defined $pid;

    if ($pid) {   # parent
        local $SIG{INT} = local $SIG{QUIT} = local $SIG{PIPE} =
            sub {
                my $sig = shift ;
                print STDERR "Parent process $$ caught a SIG${sig}.\n" ;
                print STDERR "Parent killing child process ${pid}.\n" ;
                kill $sig, $pid ;
                waitpid($pid ,0) ;
                # Break handler
                &$brkhdl() ;
                #DEBUG exit 2 ;
            } ;

        while (<KID_TO_READ>) {
            chomp $_ ;
            # We strip newline (LF, NL) ; return (CR) ; form feed (FF)
            s/[\n\r\f]//g ;
            push (@res, $_) ;
        }
        unless (close(KID_TO_READ)) {
            $exit_value = $? >> 8 ;
            $signal_num = $? & 127 ;
            # No output because it might be done by &$errhdl or &$brkhdl
            # print STDERR join(' ', @cmd), " failed: $?\n" ;
            # print STDERR "exit_value: $exit_value\n" ;
            # print STDERR "signal_num: $signal_num\n\n" ;
            if (($signal_num == 2) || ($signal_num == 125)) {
                print STDERR "Parent killing child process ${pid}.\n" ;
                kill INT, $pid ;
                waitpid($pid ,0) ;
                # Break handler
                &$brkhdl() ;
            }
            else {
                # Error handler called with the status returned
                &$errhdl($?) ;
            }
        }
    # end of parent
    }
    else {      # child
        ($EUID, $EGID) = ($UID, $GID); # suid only

        open(OLDERR, ">&STDERR")    || die "Can't backup STDERR";
        open(STDERR, ">stderr_sim") || die "Can't redirect STDERR to stderr_sim";;
        $OUTPUT_AUTOFLUSH = 1;
        exec(@cmd) || die "Can't exec program " . join(' ', @cmd) . ": $!";
        # NOTREACHED
    }
    # print STDOUT join("\n", @res) , "\n" ;
    return @res ;
}

# --------------------------------------------------------------------------------
# this function return a string usable in a filename
# from another string which is a set of compiling options
sub opt_to_str {
    my $CFLAGS = shift ;
    my @flg_list = ($CFLAGS =~ /([^ \t\"\']+|\"[^\"]*\"|\'[^\']*\')/gsx) ;
    $CFLAGS = join("_", sort(@flg_list)) ;
    $CFLAGS =~ tr/a-zA-Z0-9/_/cs ;
    $CFLAGS =~ s/_+$// ;
    $CFLAGS =~ s/^$/_/ ;
    return $CFLAGS ;
}

# --------------------------------------------------------------------------------
# this function return a table of versions for respectively:
# scc, cobj, icode, llt, asmsc100, sc100-ld,
#
sub sc_tools_versions {

    #returned value
    my @versions = () ;

    # COMMAND to launch to get the version
    my %cmd = (
        'scc'          => ['scc'],
        'cobj'         => ['cobj'],
        'mwfe'         => ['mwfe'],
        'icode'        => ['icode'],
        'llt'          => ['llt', '-v'],
        'asmsc100'     => ['asmsc100'],
        'sc100_ld'     => ['sc100-ld', '-V'],
        'runsc100'     => ['runsc100', '-v'],
        'sc100_sim'    => ['sc100-sim', '-version', '--'],
        'disasmsc100'  => ['disasmsc100'],
        'java'         => ['java', '-version']

    ) ;

    # Separator to concat the results when a tool version consists in multiple lines
    our $sep_multi = ' - ' ;

    # EXAMPLES :
    # scc ->       StarCore C Compiler vMtwk.Production 1.5        (build 020102-1433)
    # cobj ->      Cobj internal delivery reference is 1.12
    # icode ->     Icode internal delivery reference is X1.52
    # llt ->       StarCore LLT Version 1.1.1, Compiled on Thu Feb 21 18:44:29 2002
    #              Internal release version: MDCR_4_Thu Feb 21 18:44:24 2002
    # asmsc100 ->  Metrowerks StarCore 100 Assembler  Version 6.4.3
    # sc100-ld ->  sc100-ld version 1.3.4
    # runsc100 ->  runsc100 version 1.39 -- Mar 25 2002
    # sc100-sim -> sc100-sim (FastSim) version 1.4.5e
    #              Copyright (C) Agere Systems 1999-2001.  All Rights Reserved.
    #              Generated with Sleipnir version 1.3.0
    #              From model version 3.16 (2001/12/03 18:58:51)

    # STRING to search to obtain the line containing the version
    my %search = (
        'scc'         => qr/StarCore C\+?\+? Compiler vMtwk.Production/os ,
        'cobj'        => qr/Cobj internal delivery reference/os ,
		'mwfe'        => qr/Runtime Built:/os,
        'icode'       => qr/Icode internal delivery reference/os ,
        'llt'         => qr/version/osi ,
        'asmsc100'    => qr/version/osi ,
        'sc100_ld'    => qr/version/osi ,
        'runsc100'    => qr/(runsc100|simulator)\s*version/osi ,
        'sc100_sim'   => qr/sc100-sim.*\sversion/osi ,
        'disasmsc100' => qr/version/osi
    ) ;

    sub e_scc         { $p = shift ; $p =~ s/^StarCore (C\+?\+?) Compiler vMtwk.Production *(\S*)\s.*Build\s*(\S*)\s*\(([^\)]*)\).*$/$1${sep_multi}$2${sep_multi}$3${sep_multi}$4/gi ; return $p } ;
    sub e_cobj        { $p = shift ; $p =~ s/^Cobj internal delivery reference is +(.*)$/$1/gi ; return $p } ;
    sub e_mwfe        { $p = shift ; $p =~ s/^Runtime Built: +(.*)$/$1/gi ; return $p } ;
    sub e_icode       { $p = shift ; $p =~ s/^Icode internal delivery reference is +(.*)$/$1/gi ; return $p } ;
    sub e_llt         { $p = shift ; $p =~ s/^.*version[:]?\s*([^, ]*)( *[\w]* *[0-9]*)[, ].*$/$1$2/gi ; return $p } ;
    sub e_asmsc100    { $p = shift ; $p =~ s/^.*version\s*([^\s]*).*$/$1/gi ; return $p } ;
    sub e_sc100_ld    { $p = shift ; $p =~ s/^.*version\s*(.*)$/$1/gi ; return $p } ;
    sub e_runsc100    { $p = shift ; $p =~ s/^.*version\s*([^\s]*)[\s\-]*(.*)\s*$/$1${sep_multi}$2/gi ; return $p } ;
    sub e_sc100_sim   { $p = shift ; $p =~ s/^.*version\s*([^\s]*).*$/$1/gi ; return $p } ;
    sub e_disasmsc100 { $p = shift ; $p =~ s/^.*version\s*([^\s]*)\s*([^\s]*).*$/$1${sep_multi}$2/gi ; return $p } ;

    # RE to extract the version reference
    my %extract = (
        'scc'         => \&e_scc,
        'cobj'        => \&e_cobj,
        'mwfe'        => \&e_mwfe,
        'icode'       => \&e_icode,
        'llt'         => \&e_llt,
        'asmsc100'    => \&e_asmsc100,
        'sc100_ld'    => \&e_sc100_ld,
        'runsc100'    => \&e_runsc100,
        'sc100_sim'   => \&e_sc100_sim,
        'disasmsc100' => \&e_disasmsc100
    ) ;

    SCC_COMPONENTS:
    foreach my $target ('scc', 'cobj', 'mwfe', 'icode', 'llt', 'asmsc100', 'sc100_ld', 'runsc100', 'sc100_sim', 'disasmsc100') {

        my $status = 0 ;
        my $brk = 0 ;

        my (@lines) = grep(/$search{$target}/i,
                            execute_it_errbrkhdl(sub {$status = shift}, sub {$brk = 1}, @{$cmd{$target}})) ;

        exit 2 if ($brk) ;

        if ($status) {
            $exit_value = $? >> 8 ;
            $signal_num = $? & 127 ;

#            print "$target exit_value == $exit_value\n" ;
#            print "$target signal_num == $signal_num\n\n" ;
            if (($exit_value == 2) and ($signal_num == 0)) {

                push(@versions, "Error: cannot find $target") ;
                next SCC_COMPONENTS ;
            }
        }

        foreach $line (@lines) {
            $line = $extract{$target}($line) ;
            if ($line eq '') {
                $line = 'unknown' ;
            }
        }

        push(@versions, join($sep_multi, @lines)) ;
    }

    return @versions
}

# --------------------------------------------------------------------------------
# this function expands system variables used in a string:

sub expand_sys_vars {

    my $string = shift ;

    # We search for system variables in the test path and do the replacement
    my (@extvars) = ($string =~ /\$\{?\w+\}?/gsx) ;
    foreach my $var (@extvars) {
       $var =~ s/^\$// ;
       $var =~ s/^\{// ;
       $var =~ s/\}$// ;
       if (exists($ENV{$var})) {
           $string =~ s/\$\{?$var\}?/$ENV{$var}/g ;
       }
    }
    return $string ;
}
# --------------------------------------------------------------------------------
# this function returns if the current application is running in the foreground
# (and can interract with the user) or in the background.

sub is_foreground {

    open(TTY, "/dev/tty") or die $!;
    $tpgrp = tcgetpgrp(fileno(*TTY));
    $pgrp = getpgrp();
    return ($tpgrp == $pgrp) ;
}
# -------------------------------------------------------------------------------------
# This function removes the surrounded quotes
sub no_quote_surr {
    my $s = shift ;
    if ($s =~  /^[\s]*\'([^\']+)\'[\s]*$/) {
        $s =~ s/^[\s]*\'([^\']+)\'[\s]*$/$1/ ;
    }
    elsif ($s =~ /^[\s]*\"([^\"]+)\"[\s]*$/) {
          $s =~ s/^[\s]*\"([^\"]+)\"[\s]*$/$1/ ;
    }
    return $s ;
}

# This function returns the list with its elements surrounded with ' or "
# when containing a spc character
# This is usefull to trace to STDOUT the parameter of an execute or system command
sub quotes_surround {
    my @list = @_ ;
    map { if (/\s/) {unless (/\"/) {$_="\"$_\""} elsif (/\'/) {$_="'$_'"}}}  @list ;
    return @list ;
}

# ------------------ End of library ----------------------------------

1 ;









