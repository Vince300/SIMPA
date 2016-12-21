#!/usr/bin/env perl

# version:              1.0
# date of creation:     29/10/2003
# date of modification: 29/10/2003
# author:               Guerte Yves
# usage:                get_run_id.pl
# -------------------------------------------------------------------------------------
use POSIX ;
use FileHandle ;
use IO::Handle ;
use Sys::Hostname;
use Cwd qw(cwd chdir abs_path ) ;
use File::Basename;
use Socket;

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
my $login = getlogin || $name || 'qatools' ;

$PC = (sys_kind() eq 'PC') ;
# To handle Windows paths with dirname('C:\Cygwin\home')
fileparse_set_fstype('MSWin32') if ($PC);

# --------------------------------------------------------------------------------
#
# Flag to indicate that a file is locked
%is_locked_by_me = () ;

# Directory in $NEW_QA_ROOT where to find default files
$default_dir = 'defaults' ;

# Name of the file containing the user name of owner of the run_id counter
$counter_owner_fname = 'counter_owner.txt' ;

# Name of the file containing the host name of the computer supporting the run_id counter
$counter_host_fname = 'counter_host.txt' ;

# Prefix when the access to the counter_owner@counter_host fails
# It is then added to the run_id returned
$fail_prefix = '-' ;

# -------------------------------------------------------------------------------------
# Secured lock/unlock against user break
#
sub sec_lock {
    my $FILE = shift(@_) ;
    if (! ($FILE =~ '^/')) {
        my $cur = cwd() ;
        chomp $cur ;
        $FILE = $cur . '/' . $FILE ;
    }
    if (not($is_locked_by_me{$FILE})) {
        {
        use sigtrap 'handler' => 'IGNORE', 'error-signals';
        use sigtrap 'handler' => 'IGNORE', 'normal-signals';
        use sigtrap 'handler' => 'IGNORE', 'old-interface-signals';
#        local $SIG{INT}  = 'IGNORE' ;
#        local $SIG{QUIT} = 'IGNORE' ;
#        local $SIG{PIPE} = 'IGNORE' ;
        $is_locked_by_me{$FILE} = lock($FILE) ;
        use sigtrap 'handler' => \&my_handler, 'error-signals';
        use sigtrap 'handler' => \&my_handler, 'normal-signals';
        use sigtrap 'handler' => \&my_handler, 'old-interface-signals';
    }
    }
    return ($is_locked_by_me{$FILE}) ;
}
sub sec_unlock {
    my $FILE = shift(@_) ;
    if (! ($FILE =~ '^/')) {
        my $cur = cwd() ;
        chomp $cur ;
        $FILE = $cur . '/' . $FILE ;
    }
    if ($is_locked_by_me{$FILE}) {
        {
        use sigtrap 'handler' => 'IGNORE', 'error-signals';
        use sigtrap 'handler' => 'IGNORE', 'normal-signals';
        use sigtrap 'handler' => 'IGNORE', 'old-interface-signals';
#        local $SIG{INT}  = 'IGNORE' ;
#        local $SIG{QUIT} = 'IGNORE' ;
#        local $SIG{PIPE} = 'IGNORE' ;
        $is_locked_by_me{$FILE} = not(unlock($FILE)) ;
        use sigtrap 'handler' => \&my_handler, 'error-signals';
        use sigtrap 'handler' => \&my_handler, 'normal-signals';
        use sigtrap 'handler' => \&my_handler, 'old-interface-signals';
        }
    }
    return not($is_locked_by_me{$FILE}) ;
}
sub sec_clean_locks {
    while (($file, $key) = each(%is_locked_by_me)) {
        if ($key) {
                sec_unlock("$file") ;
            }
        }
}

# -------------------------------------------------------------------------------------
# in case of user break
#
sub my_kill_handler { # 1st argument is signal name
    my($sig) = @_ ;
    print STDERR "Caught a SIG$sig in my_kill_handler\n" ;
    close(KID_TO_READ) ; # Broken pipe
    sec_clean_locks ;
}
sub my_handler {		# 1st argument is signal name
    my($sig) = @_ ;
    print STDERR "Caught a SIG$sig\n" ;
    close(KID_TO_READ) ; # Broken pipe

    my %was_locked_by_me =  %is_locked_by_me ;
    sec_clean_locks ;
}

use sigtrap 'handler' => \&my_handler, 'error-signals';
use sigtrap 'handler' => \&my_handler, 'normal-signals';
use sigtrap 'handler' => \&my_handler, 'old-interface-signals';

use sigtrap 'handler' => \&my_kill_handler, 'KILL';

#DEBUG $SIG{'INT'}  = \&my_handler ;
#DEBUG $SIG{'QUIT'} = \&my_handler ;
#DEBUG $SIG{'PIPE'} = \&my_handler ;

# --------------------------------------------------------------------------------
# Returns local counter value
sub get_local_run_id {
    my $run_id = 0 ;
    my $run_id_fname = "$runtest_dir/current_run_id" ;

    # lock the file "current_run_id"
    unless (sec_lock("$run_id_fname")) {
        print STDERR "Waiting to access to $run_id_fname\n" ;
        while (! sec_lock("$run_id_fname")) {sleep 5} ;
    }
    if (-f "$run_id_fname") {
        if (open RUN_ID_FILE, "< $run_id_fname") {
            my $line = <RUN_ID_FILE> ;
            chomp $line ;
            $line =~ tr/\015//d ;
            $line =~ s/^\s+//;
            $line =~ s/\s+$//;
            ($run_id) = ($line =~ /([0-9]+)/) ;
            close RUN_ID_FILE || warn "Error in closing $run_id_fname" ;
        }
        else { warn "Error opening $run_id_fname" ; }
    }
    else { print STDERR "The file $run_id_fname doesn't exist. I create it.\n" ; }

    if (open RUN_ID_FILE, "> $run_id_fname") {
        $run_id = $run_id + 1 ;
        $run_id = sprintf '%04d', $run_id ;
        print RUN_ID_FILE $run_id, "\n" ;
        close RUN_ID_FILE || warn "Error in closing $run_id_fname" ;
    }
    else {
        warn "Error in opening $run_id_fname" ;
    }
    # unlock the file "current_run_id"
    sec_unlock("$run_id_fname") ;
    return $run_id ;
}
# --------------------------------------------------------------------------------
# Returns local counter value
sub set_local_run_id {
    my $p_run_id = shift ;
    my $run_id = 0 ;
    my $run_id_fname = "$runtest_dir/current_run_id" ;

    # lock the file "current_run_id"
    unless (sec_lock("$run_id_fname")) {
        print STDERR "Waiting to access to $run_id_fname\n" ;
        while (! sec_lock("$run_id_fname")) {sleep 5} ;
    }
    if (-f "$run_id_fname") {
        if (open RUN_ID_FILE, "< $run_id_fname") {
            my $line = <RUN_ID_FILE> ;
            chomp $line ;
            $line =~ tr/\015//d ;
            $line =~ s/^\s+//;
            $line =~ s/\s+$//;
            ($run_id) = ($line =~ /([0-9]+)/) ;
            close RUN_ID_FILE || warn "Error in closing $run_id_fname" ;
        }
        else { warn "Error opening $run_id_fname" ; }
    }
    else { print STDERR "The file $run_id_fname doesn't exist. I create it.\n" ; }

    if (open RUN_ID_FILE, "> $run_id_fname") {
        $run_id = $run_id + 1 ;
        $run_id = $p_run_id if ($p_run_id > $run_id) ;
        $run_id = sprintf '%04d', $run_id ;
        print RUN_ID_FILE $run_id, "\n" ;
        close RUN_ID_FILE || warn "Error in closing $run_id_fname" ;
    }
    else {
        warn "Error in opening $run_id_fname" ;
    }
    # unlock the file "current_run_id"
    sec_unlock("$run_id_fname") ;
    return $run_id ;
}
# --------------------------------------------------------------------------------
sub create_C_OWNER {

    unless(open C_OWNER, "> $NEW_QA_ROOT/$default_dir/$counter_owner_fname") {
        print STDERR 'Error creating $NEW_QA_ROOT/'."$default_dir/$counter_owner_fname", "\n" ;
    }
    else {
        print C_OWNER $login, "\n" ;
        close C_OWNER ;
    }
}
# --------------------------------------------------------------------------------
sub create_C_HOST {

    unless(open C_HOST, "> $NEW_QA_ROOT/$default_dir/$counter_host_fname") {
        print STDERR 'Error creating $NEW_QA_ROOT/'."$default_dir/$counter_host_fname", "\n" ;
    }
    else {
        print C_HOST $host, "\n" ;
        close C_HOST ;
    }
}
# --------------------------------------------------------------------------------
#                          MAIN
#
#    * If the configuration files does not exist or contain no valid username and hostname,
#      then the local counter is locked, increased and its negative value is returned on stdout.
unless (-d "$NEW_QA_ROOT/defaults") {
    print STDERR 'Warning: $NEW_QA_ROOT/defaults directory does not exist.', "\n" ;
    print STDERR '         creating $NEW_QA_ROOT/defaults', "\n" ;
    print STDERR '         using local $NEW_QA_ROOT/runtest/current_run_id', "\n" ;
    system('mkdir', '-p', "$NEW_QA_ROOT/$default_dir") ;

    create_C_OWNER() ;
    create_C_HOST() ;
    print STDOUT get_local_run_id(), "\n" ;
    exit 0 ;
}
else {
    our $c_owner = $login ;
    our $c_host =  $host ;
    
    GET_DATA: {
        unless (-f "$NEW_QA_ROOT/$default_dir/$counter_owner_fname") {
            create_C_OWNER() ;
        }
        else {
            my @owner_lines = read_goodlines("$NEW_QA_ROOT/$default_dir/$counter_owner_fname") ;
            
            # Error if more than 1 line
            if ($#owner_lines > 0) {
                print STDERR 'Error reading $NEW_QA_ROOT'."/$default_dir/$counter_owner_fname\n" ;
                print STDOUT $fail_prefix, get_local_run_id(), "\n" ;
            }
            elsif ($#owner_lines < 0) {
            	create_C_OWNER() ;
            }
            else {
                $c_owner = $owner_lines[0] ;
            }
        }
        
        unless (-f "$NEW_QA_ROOT/$default_dir/$counter_host_fname") {
            create_C_HOST() ;
        }
        else {
            my @host_lines  = read_goodlines("$NEW_QA_ROOT/$default_dir/$counter_host_fname") ;
            # Error if more than 1 line
            if ($#host_lines > 0 ) {
                print STDERR 'Error reading $NEW_QA_ROOT'."/$default_dir/$counter_host_fname\n" ;
                print STDOUT $fail_prefix, get_local_run_id(), "\n" ;
            }
            elsif ($#host_lines < 0) {
            	create_C_HOST() ;
            }
            else {
                $c_host = $host_lines[0] ;
            }
        }
    }

#    * if the current user is <counter_owner> and the local host is <counter_host> then the counter is locked, increased and its value is returned on stdout.

    my $same_host = 1 ;
    TEST_SAME_HOST: {

        # Same host if same hostname
        last TEST_SAME_HOST if (lc($c_host) eq lc($host)) ;

        # ERROR if hostname unknown
        my $ip_c_host = inet_aton($c_host) ;
        if (not defined($ip_c_host)) {
            print STDERR "ERROR: host $c_host not found. Using localhost and current user." ;
            print STDOUT $fail_prefix, get_local_run_id(), "\n" ;
            exit 0 ;
        }

        # Same host if localhost
        my $ipstr_c_host = inet_ntoa($ip_c_host) ;
        last TEST_SAME_HOST if ($ipstr_c_host eq '127.0.0.1') ;

        # Same host if same IP adress
        my $ipstr_host = inet_ntoa(inet_aton($host)) ;
        last TEST_SAME_HOST if ($ipstr_host eq $ipstr_c_host) ;

        # else: not same host
        $same_host = 0 ;
    }
    #
    
    if ((lc($c_owner) eq lc($login)) and $same_host) {
        print STDOUT get_local_run_id(), "\n" ;
        exit 0 ;
    }
    else {

#    * Else if the current user is not <counter_owner> or the local host is not <counter_host> then the script launches a remote get_run_id.pl with rsh:
        my $status = 0 ;
        my $brk = 0 ;
        my @cmd = ('rsh', '-l', $c_owner, $c_host, 'setenv','printexitvalue', ';', 'get_run_id.pl' ) ;

        my @lines = execute_it_errbrkhdl(sub {$status = shift}, sub {$brk = 1}, @cmd) ;
        #          o if the remote get_run_id.pl fails, then the local counter is locked, increased and its negative value is returned on stdout.
        exit 2 if ($brk) ;
        if ($status) {
            print STDERR "ERROR: fail accessing on $c_host as $c_owner.\n" ;
            print STDOUT $fail_prefix, get_local_run_id(), "\n" ;
            exit 0 ;
        }
        else {
            my @exit = grep(/Exit\s[1-9][0-9]*/, @lines) ;
            if (@exit) {
                print STDERR "ERROR: fail status exited on $c_host as $c_owner.\n" ;
                print STDOUT $fail_prefix, get_local_run_id(), "\n" ;
                exit 0 ;
            }
            else {
                my @value = grep (/\d+$/, @lines) ;
                unless (@value) {
                    print STDERR "ERROR: fail status exited on $c_host as $c_owner.\n" ;
                    print STDOUT $fail_prefix, get_local_run_id(), "\n" ;
                    exit 0 ;
                }
        #          o if the remote get_run_id.pl succeeds, then the local counter is locked, updated by the remote value if this one is greater.
                else {
                    set_local_run_id($value[0]) ;
                    print STDOUT $value[0], "\n" ;
                    exit 0 ;
                }
            }
        }
    }
}

exit 0 ;
# -------------------------------------------------------------------------------------
# Updates :
#