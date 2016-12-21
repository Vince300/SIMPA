#!/usr/bin/env perl


# version:              1.0
# date of creation:     23/11/2004
# date of modification: 23/11/2004
# author:               Guerte Yves
# usage:                clean_running.pl <dir>
# -------------------------------------------------------------------------------------
use POSIX ;
use FileHandle ;
use IO::Handle ;
use Sys::Hostname;
use Cwd qw(cwd chdir abs_path ) ;
use File::Basename;
use File::Temp qw/ tempdir / ;
use File::Path ;

# The runtest directory is $NEW_QA_ROOT/runtest directory
#
if (exists($ENV{'QA_TOOLS'})) {

    use lib "$ENV{'QA_TOOLS'}/libperl" ;
    use tools ;
}
else {
    print STDERR "Variable QA_TOOLS must be set !\n" ;
    exit 1
}

my $launching_dir = cwd() ;

autoflush STDOUT 1 ;
autoflush STDERR 1 ;

my $online = (-t STDIN && -t STDOUT) ;

umask 002 ;

$scriptname = $0 ;
$scriptname =~ s/[^\/]*\///g ;

if (exists($ENV{'HOST'})) {
    $HOST = $ENV{'HOST'} ;
}
else {
    $HOST = hostname(); ;
}
$HOST =~ tr/[A-Z]/[a-z]/ ;

$PC = (sys_kind() eq 'PC') ;
# To handle Windows paths with dirname('C:\Cygwin\home')
fileparse_set_fstype('MSWin32') if ($PC);

my $status_to_return = 0;
# -------------------------- BEGINNING OF THE MAIN ------------------------------------
# analyzing the parameters

my $help = undef;


while ($#ARGV >= 0) {

    SWITCH_ARGS: {

        if ($ARGV[0] =~ /^(-h|-help)$/i ) {
                                       $help = 1 ;
                                       shift @ARGV ;
                                       last SWITCH_ARGS ;
        }
        push (@o_args, (shift @ARGV)) ;

    }
}

if (($#o_args != 0) && not($help)) {
    print STDERR "ERROR: only one parameter, the directory.";
    $status_to_return = 1;
    $help = 1;
}

if ($#o_args == 0) {
    if (! -d $o_args[0]) {
        print STDERR "ERROR: the only parameter must be a valid directory.";
        $status_to_return = 1;
        $help = 1;
    }
}

if ($help) {
    print STDOUT "Syntax:\n" ;
    print STDOUT "$scriptname <dir>\n\n" ;
    print STDOUT "Removes running trace files from <dir> directory when all tests are finished.\n" ;
    exit $status_to_return ;
}

# -------------------------- We list the files
my $dir = $o_args[0];

my @files = glob "${dir}/*.running.v*" ;
foreach my $file (@files) {
    $file =~ s/^.*\.running\.v(\d+)_.*$/$1/g ;
}
my @running_values = nodup(@files) ;

print STDOUT "IDs of running tests: ", join (', ', sort(@running_values)), "\n\n" ;

@files = glob "${dir}/*.finished.v*" ;

foreach my $id (@running_values) {
    @files = grep(!/^.*\.finished\.v${id}_.*$/, @files) ;
}

if ($#files >= 0) {
    print STDOUT "Files to remove:\n";
    foreach my $file (@files) {
	print STDOUT $file, "\n";
    }
    print STDOUT "\n";

    my $answer = 'z' ;
    if ($online) {
	while (not($answer eq '' || $answer =~ /o|y|n/i)) {
            print STDOUT "Do you want to delete all these trace files ? o|y/n [y] " ;
	    $answer = <STDIN> ;
	    chomp $answer ;
	}
    }
    if ($answer eq '' || $answer =~ /z|o|y/i) {
	unlink @files;
	print STDOUT "Files deleted.\n";
    }
}
else {
    print STDOUT "No file to delete.\n";
}
exit $status_to_return ;
