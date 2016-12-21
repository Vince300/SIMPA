#!/usr/bin/env perl

# version:              1.0
# date of creation:     29/10/2003
# date of modification: 26/11/2003
# author:               Guerte Yves
# usage:                run_tests.pl
# -------------------------------------------------------------------------------------
use POSIX ;
use FileHandle ;
use IO::Handle ;
use Sys::Hostname;
use Cwd qw(cwd chdir abs_path ) ;
use File::Basename ;
use Socket;
use English ;
use Getopt::Long qw(:config no_ignore_case permute pass_through) ;


# The runtest directory is $NEW_QA_ROOT/runtest directory
#
if (exists($ENV{'NEW_QA_ROOT'}) and exists($ENV{'QA_TOOLS'})) {

    use lib "$ENV{'QA_TOOLS'}/mutex" ;
    use semaphores ;
    use lib "$ENV{'QA_TOOLS'}/libperl" ;
    use tools ;

    $NEW_QA_ROOT =  $ENV{'NEW_QA_ROOT'} ;
    $QA_TOOLS    =  $ENV{'QA_TOOLS'} ;
    $runtest_dir = "$NEW_QA_ROOT/runtest" ;
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
    $host = $ENV{'HOST'} ;
}
else {
    $host = hostname() ;
}
$host =~ tr/[A-Z]/[a-z]/ ;

my ($name,$passwd,$uid,$gid,$quota,$comment,$gcos,$dir,$shell,$expire) = getpwuid($<) ;
$login = getlogin || $name || 'qatools' ;

$PC = (sys_kind() eq 'PC') ;
# To handle Windows paths with dirname('C:\Cygwin\home')
fileparse_set_fstype('MSWin32') if ($PC);

# --------------------------- CONFIGURATION ---------------------------------------------
# username on remote computers
my $QA_USER = 'qatools' ;

# --------------------------- MAN -------------------------------------------------------
# Manual

sub man {
    print STDOUT "usage: $scriptname [OPTIONS]* <session_filename> \n" ;
    print STDOUT "\n" ;
    print STDOUT "OPTIONS:\n" ;
    print STDOUT "-h,  -help     to get this help message,\n" ;
    print STDOUT "-r,  -run_id   [RUN_ID]   version string of this test,\n" ;
    print STDOUT "-c,  -computer [COMPUTER_ID] (can occur many times).\n" ;
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
@p_computers    = () ;
@unknown_params = () ;

sub add_unknown_params {
    push(@unknown_params, @_);
}

$ok_params = GetOptions('r|run_id=s'       => \$run_id,
                        'c|computer=s'     => \@p_computers,
                        'd|debug'          => \$debug,
                        'h|help'           => \$help,
                        '<>'               => \&add_unknown_params) ;

# --------------------------------------------------------
# Are all the parameters OK ?
#
if ($#unknown_params != 0) {
    $ok_params = 0 ;
}
else {
    $session_filename = $unknown_params[0] ;
}

if ($help) {
    man() ;
    exit 0 ;
}

unless ($ok_params) {
    man() ;
    exit 1 ;
}

# --------------------------- WE READ THE INPUT FILE ------------------------------------

my @lines = read_goodlines($session_filename) ;

my @common_opt = () ;
my @computers  = () ;
my $i_comp     = $#computers ;
my @options    = () ;

my $flag_common_opt = 0 ;
my $curr_computer   = $host ;

my $i_line = 0 ;
my $line = $lines[$i_line] ;
LINE_LOOP:
while ($i_line <= $#lines) {
    # If beginning of [common_options]
    if ($line =~ /^\s*\[common_options\]\s*/i ) {
        $flag_common_opt = 1 ;
        $line =~ s/^\s*\[common_options\]\s*//i ;
        next LINE_LOOP if  ($line eq '') ;
    }
    # If beginning of [<computer>]
    if ($line =~ /^\s*\[(\w)\]\s*/i ) {
        $flag_common_opt = 0 ;
        $curr_computer = $LAST_PAREN_MATCH ;
        $line =~ s/^\s*\[\w\]\s*//i ;
        next LINE_LOOP if  ($line eq '') ;
    }

    # Beginning of a real line
    my (@tokens) = ($line =~ /([^ \t\(\),\"\']+|[\(\),]|\"[^\"]*\"|\'[^\']*\'|\[[^\]]*\])/gsx) ;
    print STDOUT 'tokens == ', join(', ', @tokens), "\n" if ($debug) ; # DEBUG

    my $i_tok = 0 ;
    TOKEN_LOOP:
    while ($i_tok <= $#tokens) {
        my $token = $tokens[$i_tok] ;

        # If definition of a computer specific part
        if (($token eq '[') and ($i_tok + 2 <= $#tokens)) {
            if ($tokens[$i_tok + 2] eq ']') {
                $curr_computer = $tokens[$i_tok + 1] ;
                # print STDOUT "New \$curr_computer == $curr_computer\n" if ($debug) ; # DEBUG
                $i_comp ++ ;
                $computers[$i_comp]  = $curr_computer ;
                @{$options[$i_comp]} = () ;
                $i_tok += 2 ;
                $flag_common_opt = 0 ;
                next TOKEN_LOOP ;
            }
        }
        elsif (($token =~ /^\[([^\[]+)$/i) and ($i_tok + 1 <= $#tokens)) {
            if ($tokens[$i_tok + 1] eq ']') {
                $curr_computer = $LAST_PAREN_MATCH ;
                # print STDOUT "New \$curr_computer == $curr_computer\n" if ($debug) ; # DEBUG
                $i_comp ++ ;
                $computers[$i_comp]  = $curr_computer ;
                @{$options[$i_comp]} = () ;
                $i_tok += 1 ;
                $flag_common_opt = 0 ;
                next TOKEN_LOOP ;
            }
        }
        elsif ($token =~ /^\[([^\[]+)\]$/i) {
                $curr_computer = $LAST_PAREN_MATCH ;
                # print STDOUT "New \$curr_computer == $curr_computer\n" if ($debug) ; # DEBUG
                $i_comp ++ ;
                $computers[$i_comp]  = $curr_computer ;
                @{$options[$i_comp]} = () ;
                $flag_common_opt = 0 ;
                next TOKEN_LOOP ;
        }
        elsif ($token =~ /\w+=$/) {
            if ($i_tok < $#tokens) {
                $token .= no_quote_surr($tokens[$i_tok + 1]) ;
                $i_tok += 1 ;
            }
        }

        if ($flag_common_opt) {
            push(@common_opt, $token) ;
        }
        else {
            push(@{$options[$i_comp]}, $token) ;
        }
    } continue { $i_tok++ } ;

} continue { $i_line++ ; $line = $lines[$i_line] } ;

print STDOUT "\n", "\$common_opt == ", join(' ', @common_opt), "\n" if ($debug) ; # DEBUG

# Computer in session file
print STDOUT "Defined computers == ", join(', ', @computers), "\n" if ($debug) ; # DEBUG


if (@p_computers) {
    # We verify that computers in parameters are in the session file
    my $i_comp = 0 ;
    while ($i_comp <= $#p_computers) {
        my $computer = $p_computers[$i_comp] ;
        unless (grep(/^$computer$/, @computers)) {
            print STDERR "ERROR: the computer $computer is not in $session_filename, it is removed from the list.\n" ;
            splice(@p_computers, $i_comp, 1) ;
        }
        else {
            $i_comp++ ;
        }
    }
    unless (@p_computers) {
        print STDERR "ERROR: no computer defined to run the tests." ;
        exit 1 ;
    }
    else {
        print STDOUT "Runned computers == ", join(', ', @p_computers), "\n" if ($debug) ; # DEBUG
    }

    # We remove test data about computers that are not in parameters
    my $i_comp = 0 ;
    while ($i_comp <= $#computers) {
        my $computer = $computers[$i_comp] ;
        unless (grep(/^$computer$/, @p_computers)) {
            splice(@computers, $i_comp, 1) ;
            splice(@options,   $i_comp, 1) ;
        }
        else {
            $i_comp++ ;
        }
    }
}

# We test if the computers really exist and we remove not selected ones
my $i_comp = 0 ;
while ($i_comp <= $#computers) {
    my $computer = $computers[$i_comp] ;
    if ($debug) {
        my @val = @{$options[$i_comp]} ; # DEBUG
        print STDOUT "$computer == ", join(' ', @val), "\n" ; # DEBUG
    }
    my $rhostaddr = inet_aton($rhostname) ;
    if (not defined($rhostaddr)) {
        print STDERR "The host $rhostname is unknown, it is removed from the list.\n" ;
        splice(@computers, $i_comp, 1) ;
    }
    else {
        $i_comp++ ;
    }
}
print STDOUT "\n" if ($debug) ; # DEBUG
unless (@computers) {
    print STDERR "ERROR: no computer defined to run the tests." ;
    exit 1 ;
}

# -------------------------------------------------------------------------------------
# We compute a new run_id if not told by the caller
#
unless (defined($run_id)) {
    my $status = 0 ;
    my $brk = 0 ;
    my @cmd = ('get_run_id.pl') ;

    my @lines = execute_it_stdout_errbrkhdl(sub {$status = shift}, sub {$brk = 1}, @cmd) ;
    if ($brk) {
        exit 2 ;
    }
    elsif ($status) {
        print STDERR "ERROR: fail accessing to the run_id counter.\n" ;
        exit 1 ;
    }
    elsif ($lines != 0) {
        print STDERR "ERROR: fail accessing to the run_id counter.\n" ;
        exit 1 ;
    }
    else {
        $run_id = $lines[0] ;
    }
}

# -----------------------------------------------------------------------------
# Function that gets and returns a passwords

sub get_passwd {

    my ($msg_prompt) = shift ;
    my ($password) = "" ;

    open(TTY, "/dev/tty") or die $!;
    $tpgrp = tcgetpgrp(TTY);
    $pgrp = getpgrp();
    if ($tpgrp == $pgrp) {
        # foreground
        system "stty -echo";
        print $msg_prompt ;
        chop($password = <STDIN>) ;
        print "\n";
        system "stty echo";
    } else {
        # background
        chop($password = <STDIN>) ;
    }
    return $password ;
} # end get_passwd


# -----------------------------------------------------------------------------
# Function that launches a command that requires a passwords in its STDIN

sub launch_with_pass {
    my $pass = shift ;
    my @cmd = @_ ;

    my $sleep_count = 0 ;
    my $pid = undef ;
    my $KID_TO_WRITE = undef ;
    do {
        $pid = open($KID_TO_WRITE, "|-");
        unless (defined $pid) {
            warn "cannot fork: $!";
            die "bailing out" if $sleep_count++ > 6;
            sleep 10;
        }
    } until defined $pid;

    if ($pid) {  # parent
        local $SIG{INT} = local $SIG{QUIT} = local $SIG{PIPE} =
            sub {
                my $sig = shift ;
                print STDERR "Process $$ caught a SIG${sig}.\n" ;
                print STDERR "Killing process ${pid}.\n" ;
                kill $sig, $pid ;
                waitpid($pid ,0) ;
                exit 2 ;
            } ;

        if (defined($pass)) {
            print $KID_TO_WRITE $pass, "\n" ;
        }
        else {
            print $KID_TO_WRITE "\n" ;
        }

        # Another fork to return after launching
        my $kidpid = undef ;
        die "can't fork: $!" unless defined($kidpid = fork()) ;
        if ($kidpid) {
            local $SIG{INT} = local $SIG{QUIT} = local $SIG{PIPE} =
                sub {
                    my $sig = shift ;
                    print STDERR "Process $$ caught a SIG${sig}.\n" ;
                    print STDERR "Killing process ${kidpid}.\n" ;
                    kill $sig, $kidpid ;
                    waitpid($kidpid ,0) ;
                    exit 2 ;
                } ;
            print STDOUT $cmd[0], " launched with pid == $pid.\n\n" ;
            $pid = undef ;
        }
        else {
            close($KID_TO_WRITE) || warn $cmd[0] . " exited $?" ;
            waitpid($pid, 0) ;
            exit ;
        }

    } else {     # child
        exec(@cmd) ;
    }
}

# -----------------------------------------------------------------------------
# We store the session in the archives
sub give_shareddir {
    my @options = @_ ;

    SEARCH_DIR:
    foreach my $i (0 .. $#options - 1) {
        my $opt = $options[$i] ;

        return $options[$i + 1] if ($opt =~ /^(\-local_shareddrive|\-local_shareddir)$/i) ;
        return


# --------------------------- WE LAUNCH THE VALIDATION SCRIPT ---------------------------


# Do we need to get the password for
my $pass = undef ;
TEST_NEED_PASS:
foreach my $computer (@computers) {
    if (($host ne $computer) or ($login ne $QA_USER)) {
        $pass = get_passwd("Password for ${QA_USER}: ") ;
        last TEST_NEED_PASS ;
    }
}


LOOP_LAUNCH:
foreach my $i_comp (0 .. $#computers) {

    my $computer = $computers[$i_comp] ;
    my @launch_opt = @{$options[$i_comp]} ;

    unshift(@launch_opt, @common_opt) ;
    unshift(@launch_opt, '-remote', $computer) if (($host ne $computer) or ($login ne $QA_USER)) ;

    my @cmd = ('new_validation.csh', '-run_id', $run_id, map(quotemeta, @launch_opt)) ;
    print STDOUT join(' ', @cmd), "\n" ;

#    launch_with_pass($pass, @cmd) ;
    my $runcmd = join(' ', 'echo', quotemeta($pass), '|', @cmd, '&') ;
    system($runcmd) ;

    sleep 10 ;
}

