#!/usr/bin/env perl
# version:              1.1
# date of creation:     15/04/2003
# date of modification: 06/10/2003
# author:               Guerte Yves
# usage:                scn_cpp.pl -Dmacro < $file_in.scn > $file_out.scn
# -------------------------------------------------------------------------------------

use POSIX ;
use FileHandle ;
use IO::File ;
use Getopt::Long qw(:config no_ignore_case permute pass_through);
use Cwd qw(cwd chdir abs_path ) ;
use File::Basename;

# The runtest directory is $NEW_QA_ROOT/runtest directory
#
if (exists($ENV{'NEW_QA_ROOT'}) and exists($ENV{'QA_TOOLS'})) {

    use lib "$ENV{'QA_TOOLS'}/libperl" ;
    use tools ;

    $runtest_dir = "$ENV{'NEW_QA_ROOT'}/runtest" ;
}
else {
    print STDERR "Variables NEW_QA_ROOT and QA_TOOLS must be set !\n" ;
    exit 1
}

autoflush STDOUT 1 ;
autoflush STDERR 1 ;

umask 002 ;

$scriptname = $0 ;
$scriptname =~ s/[^\/]*\///g ;

$PC = (sys_kind() eq 'PC') ;
fileparse_set_fstype('MSWin32') if ($PC);

# ----------------------------------------------------------------------
# Parameters parsing

@inc_dirs       = () ;
@unknown_params = () ;

sub add_unknown_params {
    push(@unknown_params, @_);
}

$ok_params = GetOptions('i|I=s'            => \@inc_dirs,
                        '<>'               => \&add_unknown_params) ;

# Parameters after "--" are not parsed
#
@params = (@unknown_params, @ARGV) ;

# ---------------------
# Include directories
#
@inc_dirs = split(/,/,join(',',@inc_dirs)) ;

$i_dir = $#inc_dirs ;
INC_DIRS_LOOP:
while ( $i_dir >= 0 ) {
    my $dir = $inc_dirs[$i_dir] ;
    if ( ( $dir =~ /^[\/\\]/ ) or ( $PC and ( $dir =~ /^[a-z]:[\/\\]/i ))) {
        eval {$dir = abs_path($dir) ;} ;
        if ($@) {
            print STDERR "Include directory not found: ${dir}\n\n" ;
            splice(@inc_dirs, $i_dir, 1)  ;
        }
    }
    $i_dir -- ;
}
unshift(@inc_dirs, cwd()) ;

# ----------------------------------------------------------------------
# this function search a file in included dirs if in relative form
sub find_file {
    my $fname = shift ;
    my @search_dirs = @_ ;

    my $found = undef ;
    my $basename = basename($fname) ;
    my $dirname  = dirname($fname) ;

    if ( ( $dirname =~ /^[\/\\]/ ) or ( $PC and ( $dirname =~ /^[a-z]:[\/\\]/i ))) {
        eval {$dirname = abs_path($dirname) ;} ;
        if ($@) {
            print STDERR "Directory not found: ${dirname}\n\n" ;
        }
        else {
            $fname = "$dirname/$basename" ;
            $found = $fname if ( -e $fname ) ;
        }
    }
    else {
        my @paths = map { $_ . "/$fname"} @search_dirs ;

        SEARCH_FILE:
        foreach my $f (@paths) {
            if ( -e $f ) {
                $found = $f ;
                last SEARCH_FILE ;
            }
        }

    }
    return $found ;
}
# ----------------------------------------------------------------------

$cppcmd = 'cpp -P -nostdinc' ;
$cppcmd = join(' -I ', $cppcmd, map(quotemeta, @inc_dirs)) ;
$cppcmd = join(' ',    $cppcmd, map(quotemeta, @params)) ;
# To allow the /* string that may occur in path, especially in the report_order.scn,
# we replace /\* by /* (inverse action was done before calling cpp)
my $sedcmd = 's/' . quotemeta('/\*') . '/' . quotemeta('/*') . '/g' ;
open(CPP, "|$cppcmd | sed -e '$sedcmd'") or die "Can't start ${cppcmd}: $!" ;
autoflush CPP 1 ;

sub process {
    my($input) = shift ;

    local $_ ;
    while (<$input>) {              # note use of indirection

        chomp ;
        s|^\s*\#.*$||g ;
        s|^\s*\%\s*|\#|g ;
# To allow the /* string that may occur in path, especially in the report_order.scn,
# we replace /* by /\*
        s|/[\*]|/\\*|g ;

        if (/^\s*\#\s*include\s*"(.*)"/) {

            # $1 is the include filename extracted
            my $fname = find_file($1, @inc_dirs) ;

            if ($fname) {
                my $fhandle = new IO::File ;
                unless (open($fhandle, $fname)) {
                    print STDERR "Can't open $fname: $!\n" ;
                    return ;
                }
                process($fhandle) ;
                close $fhandle ;
            }
        }
        else {
            print CPP $_, "\n" ;
        }
    }
}

process(*STDIN) ;

close CPP ;
exit 0 ;

