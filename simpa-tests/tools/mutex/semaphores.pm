package main ;

use Fcntl ':flock' ; # import LOCK_* constants
use FileHandle;

# ---------------------------------------------------------------------------------------
# The only parameter of "lock" is the string filename
# it returns 1 if OK
#            0 if already locked
# else it dies.
#
sub lock {

    my $FILE = shift(@_) ;
    my $LOCK = $FILE . '.lock' ;
    my $SEMAPHORE = $FILE . '.locklock' ;

    umask 002 ;
    
    open S, "> $SEMAPHORE" or die "Can't open the semaphore file.\n" ;
    unless (flock (S, LOCK_EX | LOCK_NB)) {
       print STDOUT "Waiting for access to $LOCK.\n" ;
       unless (flock (S, LOCK_EX)) { die "Can't lock $SEMAPHORE to access to $LOCK.\n" } ;
    }
    
    if ( -f $LOCK ) {
        $result = 0 ;
    }
    else {
        open L, "> $LOCK" or die "Can't open the file $LOCK\n" ;
        autoflush L 1 ;
        my $ppid = getppid() ;
        my $now_string = localtime ;
        print L "Pid == $$\n", "PPid == ${ppid}\n", "localtime == ${now_string}\n" ;
        close L ;
        
        $result = 1 ;
    }
    
    flock (S, LOCK_UN) ;
    close S ;
    return $result ;
}


# ---------------------------------------------------------------------------------------
# The only parameter of "unlock" is the string filename
sub unlock {

    my $FILE = shift(@_) ;
    my $LOCK = $FILE . '.lock' ;
    my $SEMAPHORE = $FILE . '.locklock' ;
    
    umask 002 ;
    
    open S, "> $SEMAPHORE" or die "Can't open the semaphore file.\n" ;
    unless (flock (S, LOCK_EX | LOCK_NB)) {
       print STDOUT "Waiting for access to $LOCK.\n" ;
       unless (flock (S, LOCK_EX)) { die "Can't lock $SEMAPHORE to access to $LOCK.\n" } ;
    }
    
    if (-f $LOCK) {
       unlink $LOCK ;
    }
    else {
       print STDERR "File $FILE already unlocked.\n"
    }
    
    flock (S, LOCK_UN) ;
    close S ;
}

# ---------------------------------------------------------------------------------------
# Value returned by the package
1 ;
