#!/usr/bin/env perl

# version:              1.1
# date of creation:     05/02/2003
# date of modification: 21/05/2003
# author:               Guerte Yves
# usage:                tar_NEW_QA_from_scn.pl -tar <tar_filename> [-d macro] [ -mute ] ( -split_cpus | \{-cpu <computer_symbolic_name>\}* ) scenario_file
#                       it includes the generic test directories.
# -------------------------------------------------------------------------------------
use POSIX ;
use FileHandle ;
use IO::Handle ;
use Sys::Hostname;
use File::Temp qw/tempfile/ ;
use Cwd qw(cwd chdir abs_path ) ;
use File::Basename;

# The runtest directory is $NEW_QA_ROOT/runtest directory
#
if (exists($ENV{'NEW_QA_ROOT'}) and exists($ENV{'QA_TOOLS'})) {

    use lib "$ENV{'QA_TOOLS'}/mutex" ;
    use semaphores ;
    use lib "$ENV{'QA_TOOLS'}/libperl" ;
    use tools ;

    unless(eval{$qa_root = abs_path("$ENV{'NEW_QA_ROOT'}")}) {
        print STDERR "ERROR: '$ENV{'NEW_QA_ROOT'}': No such directory.\n" ;
        exit 1 ;
    }
    $qa_root =~ s/\/*$// ;
    $runtest_dir = "$qa_root/runtest" ;
}
else {
    print STDERR "Variables NEW_QA_ROOT and QA_TOOLS must be set !\n" ;
    exit 1
}

autoflush STDOUT 1 ;
autoflush STDERR 1 ;

umask 002 ;

$PWD = cwd() ;

# Status returned by 'find' command when no file was found
$find_nothing_status = 256 ;

# Array of all the paths to acces the tests to do
@run_paths    = () ; # to access:  $path = $run_paths[i]
#
# Array of all the paths to acces the tests already done
@runned_paths = () ;
#
# array indexed by test-path of array of the options of the test
%options      = () ; # to access:  "$option number i for $path" = ${$options{$path}}[i]

# Definition of all the variables of the scenario
# by a list of tokens (a token is a string)
%strl_defvars = () ;
#
# by disjunction of conjunctions of tokens (array oy arrays of tokens)
%defvars      = () ;

# -------------------------------------------------------------------------------------
# function which converts a disjunction of conjunctions (an array of arrays)
# into a printable string
#
sub str_orand {
    my @orand = @_ ;
    my $str_orand = "(" ;

    if ($#orand >= 0) {
        for ($i=0 ; $i <= $#orand - 1 ; $i++ ) {
            if ($#{$orand[$i]} >= 0) {
                $str_orand .= "[" . join(' ', @{$orand[$i]}) . "] + " ;
            }
            else {
                $str_orand .= "[] + " ;
            }
        }
        $str_orand .= "[" . join(' ', @{$orand[$#orand]}) . "]" ;
    }
    $str_orand .= ")" ;
    return $str_orand ;
}
# -------------------------------------------------------------------------------------
# function which makes a "and" between two disjunctions of conjuntions
#
sub and_disj {
    my @or_and1 = @{$_[0]} ;
    my @or_and2 = @{$_[1]} ;

    if (($#or_and1 < 0) || (($#or_and1 == 0) && ($#{$or_and1[0]} < 0))) {
        return @or_and2 ;
    }
    elsif (($#or_and2 < 0) || (($#or_and2 == 0) && ($#{$or_and2[0]} < 0))) {
        return @or_and1 ;
    }
    else {
        my @or_and = () ;
        my $id_or  = 0 ;

        for ($id1=0 ; $id1 <= $#or_and1 ; $id1++) {
            for ($id2=0 ; $id2 <= $#or_and2 ; $id2++) {

                @{$or_and[$id_or]} = (@{$or_and1[$id1]}, @{$or_and2[$id2]}) ;
                $id_or++ ;
            }
        }
        return @or_and ;
    }
} # end sub and_disj

# -------------------------------------------------------------------------------------
# function which converts a list of tokens with ' '=and  ','=or
# into a disjunction of confunction (an array of arrays )
#
sub parse_orand {
    my @toklist = @_ ;
    my @orand = ([]) ;

    # index where we are writing a "or" expression
    my $id_or  = 0 ;

    # index until which we are writing a "and" expression
    my $id_and = 0 ;

    # No token
    if ( $#toklist < 0 ) {
        return ([@orand], [@toklist]) ;
    }
    # End of paren = empty list
    elsif ( $toklist[0] eq ')' ) {
        # shift @toklist ;
        # print STDERR "Error with variable definition in parenthesis.\n" ;
        # print STDERR "Rest to analyse: " . join(' ', @toklist) . "\n" ;
        return ([@orand], [@toklist]) ;
    }
    # Only one token
    elsif ($#toklist == 0 ) {
        return ([[@toklist]], []) ;
    }
    else {
        while (($#toklist >= 0) && ($toklist[0] ne ')')) {
            if ($toklist[0] eq ',') {
                shift @toklist ;
                # $id_or++ ;
                $id_or = $id_and + 1 ;
                $id_and = $id_or ;
                @{$orand[$id_or]} = () ;
            }
            elsif ($toklist[0] eq '(') {
                shift @toklist ;
                my @res_and_toklist = parse_orand(@toklist) ;
                my @orand2  = @{$res_and_toklist[0]} ;
                @toklist    = @{$res_and_toklist[1]} ;
                if ($toklist[0] ne ')') {
                    print STDERR "Error with variable definition in parenthesis.\n" ;
                    print STDERR "Rest to analyse: " . join(' ', @toklist) . "\n" ;
                    return ([@orand], [@toklist]) ;
                }
                else {
                    shift @toklist ;
                    my @current_and = @orand[$id_or .. $id_and] ;
                    my @orand3 = and_disj([@current_and], [@orand2]) ;
                    $id_and = $id_or + $#orand3 ;
                    for ($i=0 ; $i <= $#orand3 ; $i++ ) {
                        @{$orand[$id_or + $i]} = @{$orand3[$i]} ;
                    }
                } # end if $toklist[0] ne ')')
            } # end if ($toklist[0] eq ',')
            else {
                my @orand2 = ([$toklist[0]]) ;

                my @current_and = @orand[$id_or .. $id_and] ;

                my @orand3 = and_disj([@current_and], [@orand2]) ;

                $id_and = $id_or + $#orand3 ;
                for ($i=0 ; $i <= $#orand3 ; $i++ ) {
                    @{$orand[$id_or + $i]} = @{$orand3[$i]} ;
                }
                shift @toklist ;
            }
        } # end while (($#toklist >= 0) && ($toklist[0] ne ')'))
        return ([@orand], [@toklist]) ;
    } # end if ( $#toklist < 0 )
} # end sub parse_orand


# -------------------------------------------------------------------------------------
# This function returns the list with its elements surrounded with ' or "
# when containing a spc character
# This is usefull to trace to STDOUT the parameter of an execute or system command
sub quotes_surround {
    my @list = @_ ;
    map {if (/\s/) {unless (/\"/) {$_="\"$_\""} else {$_ = "'$_'"}}}  @list ;
    return @list ;
}

# -------------------------- BEGINNING OF THE MAIN ------------------------------------
# analyzing the parameters
#
$scenario_fname = '' ;
$tarname        = '' ;
$split_cpus     = 0  ;
@macrodef       = () ;
@o_args         = () ;
$mute           = 0  ;

# hash-table with cpu-id as key, of array of test path
%cpu_paths    = () ;

# array of cpu_ids target for the tar
@cpu_targets  = () ;

while ($#ARGV >= 0) {

    SWITCH_ARGS: {

        if ($ARGV[0] =~ /^(-h|-help)$/i ) {
                                       $help = 1 ;
                                       shift @ARGV ;
                                       last SWITCH_ARGS ;
        }
        if ($ARGV[0] =~ /^(-s|-split_cpus)$/i ) {
                                       $split_cpus = 1 ;
                                       shift @ARGV ;
                                       if (@cpu_targets) {
                                           print STDERR "Error: -cpu and -split_cpus cannot be together.\n" ;
                                           $help = 1 ;
                                       }
                                       last SWITCH_ARGS ;
        }
        if ($ARGV[0] =~ /^-cpu$/i ) {
                                       shift @ARGV ;
                                       if ($#ARGV >= 0) {
                                           my $cpu_target = lc(quotemeta(shift @ARGV)) ;
                                           $cpu_target =~ s/^\s+//;
                                           $cpu_target =~ s/\s+$//;
                                           push(@cpu_targets, $cpu_target) ;
                                           if ($split_cpus == 1) {
                                               print STDERR "Error: -cpu and -split_cpus cannot be together.\n" ;
                                               $help = 1 ;
                                           }
                                       }
                                       else {
                                           print STDERR "Error with the '-cpu' parameter.\n" ;
                                           $help = 1 ;
                                       }
                                       last SWITCH_ARGS ;
        }
        if ($ARGV[0] =~ /^(-t|-tar)$/i ) {
                                       shift @ARGV ;
                                       if ($#ARGV >= 0) {
                                           $tarname = shift @ARGV ;
                                       }
                                       else {
                                           print STDERR "Error with the '-tar' parameter.\n" ;
                                           $help = 1 ;
                                       }
                                       last SWITCH_ARGS ;
        }
        if ($ARGV[0] =~ /^-mute$/i ) {
                                       $mute = 1 ;
                                       shift @ARGV ;
                                       last SWITCH_ARGS ;
        }
        if ($ARGV[0] =~ /^(-d|-def)$/i ) {
                                       shift @ARGV ;
                                       if ($#ARGV >= 0) {
                                           push(@macrodefs, shift @ARGV) ;
                                       }
                                       else {
                                           print STDERR "Error with the 'def' parameter.\n" ;
                                           $help = 1 ;
                                       }
                                       last SWITCH_ARGS ;
        }
        push (@o_args, (shift @ARGV)) ;

    }
}

if ($#o_args >= 1) {
    print STDERR "Unknown parameters: ", join(' ', @o_args), "\n" ;
    $help = 1 ;
}
elsif ($#o_args == 0) {
    $scenario_fname = $o_args[0] ;
}
if ($tarname eq '') {
    print STDERR "Tar filename ('-tar' parameter) is mandatory.\n" ;
    $help = 1 ;
}
if ($scenario_fname eq '') {
    print STDERR "Scenario file is mandatory.\n" ;
    $help = 1 ;
}

if ($help) {
    my $scriptname = $0 ;
    $scriptname =~ s/[^\/]*\///g ;
    print STDOUT "Syntax:\n" ;
    print STDOUT "$scriptname -tar <tar_filename> [-d macro] [ -mute ] ( -split_cpus | \{-cpu <computer_symbolic_name>\}* ) scenario_file\n" ;
    exit 1 ;
}

print STDOUT "Targets cpus are : ", join(', ', @cpu_targets), "\n" unless ($mute) ; # DEBUG

# -------------------------------------------------------------------------------------
# We read the scenario file

$cpp_cmd = 'scn_cpp.pl' ;
$cpp_cmd = join(' -I ', $cpp_cmd, quotemeta(dirname($scenario_fname)), quotemeta("$runtest_dir/scenarios")) ;
$cpp_cmd = join(' -D', $cpp_cmd, map(quotemeta, @macrodefs)) ;

# DEBUG print STDOUT "\n", "${cpp_cmd} < ${scenario_fname}\n\n" unless ($mute) ;
open SCENARIO, "$cpp_cmd <$scenario_fname |" or die "Can't start scn_cpp.pl on the scenario file ${scenario_fname}: $!\n" ;

chdir "$runtest_dir" ;

READ_SCENARIO:
while (my $line = <SCENARIO>) {
   chomp ($line) ;

   # We suppress comments, leading and ending spaces
   #
   $line =~ s/([^\\])#.*$/$1/;
   $line =~ s/^\s+//;
   $line =~ s/\s+$//;

   # test of - empty line or comment,
   #         - def of variable,
   #         - def of run_all path and options
   #
   SWITCH_LINE: {
       if ((length($line) == 0) || ($line =~ '^#')) {
           # print STDERR "Empty line or comment.\n" ;
           last SWITCH_LINE ;
       }
       if ($line =~ '^@') {
           ($line_cpu, $line) = ($line =~ /^@([^\s]+)[\s]+(.*)$/gs) ;
           $line_cpu = lc(quotemeta($line_cpu)) ;
           if (@cpu_targets) {
               unless (grep (/^${line_cpu}$/i, @cpu_targets)) {
                    # print STDERR "Line for another cpu.\n" ;
                    last SWITCH_LINE ;
               }
           }
       }
       else {
           $line_cpu = '' ;
       }

       # We search for system variables
       my $expanded_line = expand_sys_vars($line) ;
       my (@items) = ($expanded_line =~ /(^[^=\"\s]+)\s*=\s*(.*)\s*$/gs) ;

       # If it is a definition of a variable
       if ($#items == 1) {

           my $varname = $items[0] ;
           my $vardef  = $items[1] ;

           # Separating tokens
           # my (@tokens) = ($vardef =~ /([^ \t\(\),\"]+|[\(\),]|\"[^\"]+\")/gsx) ;
           my (@tokens) = ($vardef =~ /([^ \t\(\),\"\']+|[\(\),]|\"[^\"]*\"|\'[^\']*\')/gsx) ;

           #applying previous definitions
           for ($itok=0 ; $itok <= $#tokens ; $itok++) {
               my $tokname = $tokens[$itok] ;
               if (exists($strl_defvars{$tokname})) {

                   my @strl_deftok  = @{$strl_defvars{$tokname}} ;
                   unshift(@strl_deftok, '(') ;
                   push(@strl_deftok, ')') ;
                   splice(@tokens, $itok, 1, @strl_deftok) ;
               }
           }
           @{$strl_defvars{$varname}} = @tokens ;

           # Parsing the token list
           my @orand_and_toklist = parse_orand(@tokens) ;

           my @orand_r   = @{$orand_and_toklist[0]} ;
           my @toklist_r = @{$orand_and_toklist[1]} ;

           if ($#toklist_r >= 0) {
               print STDERR "Variable definition not entirely parsed ($#toklist_r).\n" ;
               print STDERR "Rest = " . join(' | ', @toklist_r) . "\n" ;
               print STDERR "Rest = (" . join(' | ', @{$toklist_r[0]}) . ")\n" ;
           }

           @{$defvars{$varname}} = @orand_r ;

           last SWITCH_LINE ;
       } # end if ($#items == 1) => definition of a variable

       PATH_AND_OPTIONS: {
           # a word (neither '"' nor " ") and the rest
           my (@items) = ($expanded_line =~ /(^[^\"\s]+)\s*(.*)\s*$/gs) ;

           my $item_path   = $items[0] ;
           my $str_options = $items[1] ;

           # Separating tokens
           # my (@tokens) = ($str_options =~ /([^ \t\(\),\"]+|[\(\),]|\"[^\"]+\")/gsx) ;
           my (@tokens) = ($str_options =~ /([^ \t\(\),\"\']+|[\(\),]|\"[^\"]*\"|\'[^\']*\')/gsx) ;

           #applying previous definitions
           for ($itok=0 ; $itok <= $#tokens ; $itok++) {
               my $tokname = $tokens[$itok] ;
               if (exists($strl_defvars{$tokname})) {

                   my @strl_deftok  = @{$strl_defvars{$tokname}} ;
                   unshift(@strl_deftok, '(') ;
                   push(@strl_deftok, ')') ;
                   splice(@tokens, $itok, 1, @strl_deftok) ;
               }
           }

           # Parsing the token list
           my @orand_and_toklist = parse_orand(@tokens) ;

           my @orand_r   = @{$orand_and_toklist[0]} ;
           my @toklist_r = @{$orand_and_toklist[1]} ;

           if ($#toklist_r >= 0) {
               print STDERR "Variable definition not entirely parsed ($#toklist_r).\n" ;
               print STDERR "Rest = " . join(' | ', @toklist_r) . "\n" ;
               print STDERR "Rest = (" . join(' | ', @{$toklist_r[0]}) . ")\n" ;
           }

           my @paths = glob "$item_path/run_all" ;
           foreach my $path (@paths) {
               $path =~ s/\/run_all$// ;
           }
           if ($#paths >= 0) {
               if (($#paths == 0) && (not( -d $paths[0]))) {
                   print STDERR  "Master script $paths[0]/run_all doesn't exist.\n\n" ;
               }
               else {
                   foreach my $path (@paths) {
                       my $pathexpr = quotemeta($path) ;
                       unless (grep(/^${pathexpr}$/, @run_paths)) {
                           push (@run_paths, $path) ;
                       }
                       my $nb_variants = $#{$options{$path}} + 1 ;

                       for ($i=0 ; $i <= $#orand_r ; $i++ ) {

                           my @opt_this_path = @{$orand_r[$i]} ;

                           foreach my $opt (@opt_this_path) {
                               # search for system variables in the options and do the replacement
                               $opt = expand_sys_vars($opt) ;
                           }
                           @{$options{$path}[$nb_variants + $i]} = @opt_this_path ;
                       }
                       # We store the information that the cpu will do this test
                       if (! $split_cpus or ($line_cpu eq '')) {
                           my $pathexpr = quotemeta("runtest/$path") ;
                           unless (grep(/^${pathexpr}$/, @{$cpu_paths{''}})) {
                               push(@{$cpu_paths{''}}, "runtest/$path") ;
                               print STDOUT "We will tar runtest/$path for all.\n" unless ($mute) ; # DEBUG
                           }
                       }
                       else {
                           if (! @cpu_targets or (grep(/^${line_cpu}$/i, @cpu_targets))) {
                               my $pathexpr = quotemeta("runtest/$path") ;
                               unless (grep(/^${pathexpr}$/,@{$cpu_paths{$line_cpu}})) {
                                   push(@{$cpu_paths{$line_cpu}}, "runtest/$path") ;
                                   print STDOUT "We will tar runtest/$path for $line_cpu.\n" unless ($mute) ; # DEBUG
                               }
                           }
                       }
                   } # end foreach $path (@paths)
               } # end if (($#paths == 0) && ( -d "$paths[0]"))
           }
           else {
               print STDERR  "Path $runtest_dir/$item_path doesn't exist.\n\n" unless ($mute) ;
           } # end if ($#paths >= 0)
       } # end of PATH_AND_OPTIONS
   } # end of test of SWITCH_LINE
} # end of while <SCENARIO> (not eof)
close SCENARIO ;

# If there was a -split_cpus option and lines without @cpu prefix,
# we must add these paths to all cpus
if ($split_cpus and @{$cpu_paths{''}}) {

    my @paths_forall = @{$cpu_paths{''}} ;
    foreach my $cpu (keys(%cpu_paths)) {
        unless ($cpu eq '') {
            foreach my $path (@paths_forall) {
                my $pathexpr = quotemeta("runtest/$path") ;
                unless (grep(/^${pathexpr}$/, @{$cpu_paths{$cpu}})) {
                    push(@{$cpu_paths{$cpu}}, $path) ;
                    print STDOUT "We will tar $path for $cpu.\n" unless ($mute) ; # DEBUG
                }
            }
        }
    }
    delete $cpu_paths{''} ;
}

# -------------------------------------------------------------------------------------
# TAR

chdir $qa_root ;

TAR_CPUS_LOOP:
foreach my $cpu (keys(%cpu_paths)) {

    # We list the files that must not be included in the tar file
    my ($EXCL, $excl_flist_fname) = tempfile("excl_XXXX", DIR=>"/tmp", OPEN=>1, UNLINK=>0) ;
    unless (defined($EXCL)) {
        warn "ERROR: cannot open temporary file in /tmp." ;
    }
    else {
        binmode $EXCL ;
    }

    my $nb_tests = $#{$cpu_paths{$cpu}} ;
    foreach $path (@{$cpu_paths{$cpu}}) {

        my @args = ('find', "$path", '(', '-name', 'report_*', '-o', '-name', 'fail_report*', '-o', '-name', '*.lock',
                                    '-o', '-name', '*.obj',    '-o', '-name', '*.s[1l]',      '-o', '-name', '*.el[bnd]',
                                    '-o', '-name', '*.map',    '-o', '-name', 'stdout_sim',   '-o', '-name', 'stderr_sim',
                                    '-o', '-name', '*.bak',    '-o', '-name', '*.bck',        '-o', '-name', '*~',
                                    '-o', '-name', '.bak',     '-o', '-name', 'T',            '-o', '-name', '*.trc',
                                    '-o', '-name', '*.o',      '-o', '-name', '*.exe',        '-o', '-name', 'self_test.txt',
                                    ')',
                            '-print') ;

        #DEBUG print STDOUT join(' ', quotes_surround(@args)), "\n" unless ($mute) ;
        my $status = 0 ;
        my @res = execute_it_stdout_errbrkhdl(sub {$status = shift}, sub {close $EXCL ; unlink $excl_flist_fname ; exit 2}, @args) ;

        # status is 256 if no file found
        if ($status and ($status != $find_nothing_status)) {
            my $exit_value = $status >> 8 ;
            my $signal_num = $status & 127 ;
            print STDERR join(' ', @args), " failed: $status\n" ;
            print STDERR "exit_value: $exit_value\n" ;
            print STDERR "signal_num: $signal_num\n" ;
            if (($signal_num == 2) || ($signal_num == 125)) {
                close $EXCL ;
                unlink $excl_flist_fname ;
                exit 2 ;
            }
        }

        foreach my $dir_nosens ("$path/bin", "$path/outputs", "$path/obj", "$path/dasm") {
            if ( -d $dir_nosens ) {
                @args = ('find', $dir_nosens, '-type', 'f', '-print') ;
                $status = 0 ;
                push(@res, execute_it_stdout_errbrkhdl(sub {$status = shift}, sub {close $EXCL ; unlink $excl_flist_fname ; exit 2}, @args)) ;

                # status is 256 if no file found
                if ($status and ($status != $find_nothing_status)) {
                    my $exit_value = $status >> 8 ;
                    my $signal_num = $status & 127 ;
                    print STDERR join(' ', @args), " failed: $status\n" ;
                    print STDERR "exit_value: $exit_value\n" ;
                    print STDERR "signal_num: $signal_num\n" ;
                    if (($signal_num == 2) || ($signal_num == 125)) {
                        close $EXCL ;
                        unlink $excl_flist_fname ;
                        exit 2 ;
                    }
                }
            }
        }

        # We remove duplicates
        @res = nodup(@res) ;
        if ($EXCL) {
            foreach my $fname (@res) {
                print $EXCL $fname, "\n" ;
            }
        }
    } # end foreach $path (@{$cpu_paths{$cpu}})

    my @plum_exe=glob('runtest/standards/plumhall/v[0-9]*/plum_reports_scripts/{score,src,summary,txtchk,phchk,unarc}{,.exe}') ;
    if ($EXCL) {
        foreach my $fname (@plum_exe) {
            print $EXCL $fname, "\n" ;
        }
    }

    chdir $PWD ;

    # We tar all the directories for the computer $cpu
    my $tmp_tarname = $tarname ;
    $tmp_tarname = "${cpu}_" . $tmp_tarname if ( $split_cpus and ($cpu ne '')) ;
    unlink $tmp_tarname ;

    # We add the generic test directories
    push(@{$cpu_paths{$cpu}}, 'runtest/generic_test', 'runtest/Xicode-F', 'runtest/scenarios') ;

    my @args = ('tar', 'cfX' , $tmp_tarname, $excl_flist_fname) ;
    foreach my $path (@{$cpu_paths{$cpu}}) {
        push(@args, '-C', $qa_root, $path) ;
    }
    print STDOUT join(' ', quotes_surround(@args)), "\n" unless ($mute) ; # DEBUG
    unless (system(@args) == 0) {
        $exit_value = $? >> 8 ;
        $signal_num = $? & 127 ;
        print STDERR join(' ', @args), " failed: $?\n" ;
        print STDERR "exit_value: $exit_value\n" ;
        print STDERR "signal_num: $signal_num\n" ;
        if (($signal_num == 2) || ($signal_num == 125)) {
            close $EXCL ;
            unlink $excl_flist_fname ;
            exit 2 ;
        }
    }
    close $EXCL ;
    unlink $excl_flist_fname ;
}

# -------------------------------------------------------------------------------------

FIN_run_allapp:
exit 0 ;
