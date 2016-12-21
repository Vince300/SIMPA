#!/usr/bin/env perl

# version:              1.8
# date of creation:     17/04/2001
# date of modification: 25/02/2004
# author:               Guerte Yves
# usage:                new_allapp_reports_pack.pl -v <version> [-i <cpu_id>] [-tar] <scenario>
# -------------------------------------------------------------------------------------
use POSIX ;
use FileHandle ;
use IO::Handle ;
use Sys::Hostname ;
use Cwd qw(cwd chdir abs_path ) ;
use File::Basename ;

# The runtest directory is $NEW_QA_ROOT/runtest directory
#
if (exists($ENV{'NEW_QA_ROOT'}) and exists($ENV{'QA_TOOLS'})) {

    use lib "$ENV{'QA_TOOLS'}/mutex" ;
    use semaphores ;
    use lib "$ENV{'QA_TOOLS'}/libperl" ;
    use tools ;

    unless(eval{$runtest_dir = abs_path("$ENV{'NEW_QA_ROOT'}/runtest")}) {
        print STDERR "ERROR: '$ENV{'NEW_QA_ROOT'}/runtest': No such directory.\n" ;
        exit 1 ;
    }
    $runtest_dir =~ s/\/*$// ;
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
    $HOST = $ENV{'HOST'} ;
}
else {
    $HOST = hostname() ;
}
$HOST =~ tr/[A-Z]/[a-z]/ ;

$PC = (sys_kind() eq 'PC') ;
# To handle Windows paths with dirname('C:\Cygwin\home')
fileparse_set_fstype('MSWin32') if ($PC);

# Name of the master scripts (enter point for each test directory)
$run_all_script    = 'run_all.pl' ;
$qt_run_all_script = quotemeta ($run_all_script) ;
# --------------------------------------------------------------------------------
#
# Array of all the paths to acces the tests to do
@run_paths    = () ; # to access:  $path = $run_paths[i]
#
# Array of all the paths to acces the tests already done
@runned_paths = () ;
#
# array indexed by test-path of array of the options of the test
# %options      = () ; # to access:  "$option number i for $path" = ${$options{$path}}[i]

# Definition of all the variables of the scenario
# by a list of tokens (a token is a string)
%strl_defvars = () ;
#
# by disjunction of conjunctions of tokens (array oy arrays of tokens)
%defvars = () ;

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

# function which format a number on 2 characters
sub fmt_2car {
    return substr('0' . $_[0], -2)
}

($sec,$min,$hour,$mday,$mon,$year,undef,undef,undef) = localtime(time);
# $year -= 100 ; $year = fmt_2car($year) ;
$year += 1900 ;
$mon  += 1 ;
# $date = fmt_2car($mon) . "-" . fmt_2car($mday) . "-" . fmt_2car($year) ;
$date = $year . '/' . fmt_2car($mon) . '/' . fmt_2car($mday)
        . ' - ' . fmt_2car($hour) . ':' . fmt_2car($min) . ':' . fmt_2car($sec)  ;

# -------------------------------------------------------------------------------------
sub line_report {
    my ($report_fhdl, $descr, $in_file, $status, $size, $nb_cyc, @others) = @_ ;

    my ${max_targets_l} = 10 ;
    my ${max_in_files_l} = 10 ;
    my $others_str = join(' ', @others);

    printf { $report_fhdl } "%        ${max_targets_l}s, %${max_in_files_l}s;%                20s;%      9s;%           15s%s\n", $descr, $in_file, $status, $size, $nb_cyc, $others_str ;
}

sub head_report {
    my $a_file_hdl   = shift ;

    line_report ($a_file_hdl,
                                     'Target', 'Input file',            'Status','Size (b)', 'Num of cycles', 'Num of cycles/fr, ...'
                ) ;
    print  $a_file_hdl "---------------------------------------------------------------------------------------------------\n" ;
}

sub end_report {
    my $a_file_hdl   = shift ;

    my ($num_fail, $sum_size, $sum_cycles, @others) = ('', '', '', [''] ) ;

    print  $a_file_hdl "---------------------------------------------------------------------------------------------------\n" ;
    line_report ($a_file_hdl,
                                   'Total',                  '', 'num F_A_I_L = '.$num_fail,$sum_size,       $sum_cycles, @others
                ) ;
    print  $a_file_hdl "\n\n" ;
}
# -------------------------------------------------------------------------------------
# function that writes the header of a missing test in a report in parameter
#
sub write_empty {

    my $a_file_hdl   = shift ;
    my $str15_title  = shift ;
    my $test_path    = shift ;

    my $test_mode    = 'MISSING' ;
    my $level        = 'MISSING' ;
    my $CFLAGS       = '' ;
    my $mand_CFLAGS  = 'MISSING' ;
    my @targets      = ('MISSING') ;
    my $makefile     = 'MISSING' ;
    my @make_options = ('MISSING') ;
    my $simulator    = 'MISSING' ;
    my @sim_options  = ('MISSING') ;
    my @param_files  = () ;

    foreach my $REPORT_FHDL ($a_file_hdl) {
        print  $REPORT_FHDL "**************************************************************\n" ;
        printf $REPORT_FHDL "*  Launch date: %44s *\n",                                    $date ;
        printf $REPORT_FHDL "*    Test name: %44s *\n",                                    $str15_title ;
        printf $REPORT_FHDL "* Test version: %44s *\n",                                    $version ;
        printf $REPORT_FHDL "*    Test path: %44s *\n",                                    $test_path ;
        print  $REPORT_FHDL "*                                                            *\n" ;
        printf $REPORT_FHDL "*    Test mode: %44s *\n",                                    $test_mode ;
        printf $REPORT_FHDL "*        Level: %44s *\n",                                    $level ;
        printf $REPORT_FHDL "*   CC options: %44s *\n",                                    $CFLAGS . ' ' . $mand_CFLAGS ;
        if (($#targets >= 0) or ($#targets <= 10)) {
        printf $REPORT_FHDL "*      Targets: %44s *\n",                                    $targets[0] ;
        foreach my $target (@targets[1..$#targets], @unknown_targets) {
        printf $REPORT_FHDL "*               %44s *\n",                                    $target ;
        }
        }
        else {
        printf $REPORT_FHDL "*      Targets: %44s *\n",                                    '<all>' ;
        foreach my $target (@unknown_targets) {
        printf $REPORT_FHDL "*               %44s *\n",                                    $target ;
        }
        }
        printf $REPORT_FHDL "*     Makefile: %44s *\n",                                    $makefile ;
        printf $REPORT_FHDL "* Make options: %44s *\n",                                    join(' ', @make_options) ;
        printf $REPORT_FHDL "*    Simulator: %44s *\n",                                    $simulator ;
        printf $REPORT_FHDL "* Sim. options: %44s *\n",                                    join(' ', @sim_options) ;
        if (@param_files) {
        printf $REPORT_FHDL "*  Param files: %44s *\n",                                    $param_files[0] ;
        foreach my $param_file (@param_files[1..$#param_files]) {
        printf $REPORT_FHDL "*               %44s *\n",                                    $param_file ;
        }
        }
        print  $REPORT_FHDL "**************************************************************\n\n" ;
    }
    head_report($a_file_hdl) ;
    line_report ($a_file_hdl,
                                     'MISSING', 'MISSING',            'MISSING','MISSING', 'MISSING', 'MISSING'
                ) ;
    end_report($a_file_hdl) ;
}

# -------------------------- BEGINNING OF THE MAIN ------------------------------------
# analyzing the parameters
#
$version        = '' ;
$scenario_fname = '' ;
$tar_report     = 0 ;
# pattern for cpu_id must match any, if not set in the parameters
$CPU_ID         = '.*' ;
$fill_empty     = 0 ;
@o_args         = () ;

while ($#ARGV >= 0) {

    SWITCH_ARGS: {

        if ($ARGV[0] =~ /^-v$/i ) {
                                       shift @ARGV ;
                                       if ($#ARGV >= 0) {
                                           $version = shift @ARGV ;
                                       }
                                       else {
                                           print STDERR "Error with the 'version' parameter.\n" ;
                                           $help = 1 ;
                                       }
                                       last SWITCH_ARGS ;
        }
        if ($ARGV[0] =~ /^(-h|-help)$/i ) {
                                       $help = 1 ;
                                       shift @ARGV ;
                                       last SWITCH_ARGS ;
        }
        if ($ARGV[0] =~ /^-i$/i ) {
                                       shift @ARGV ;
                                       if ($#ARGV >= 0) {
                                           $CPU_ID = quotemeta(shift @ARGV) ;
                                       }
                                       else {
                                           print STDERR "Error with the 'cpu_id' parameter.\n" ;
                                           $help = 1 ;
                                       }
                                       last SWITCH_ARGS ;
        }
        if ($ARGV[0] =~ /^-tar$/i ) {
                                       $tar_report = 1 ;
                                       shift @ARGV ;
                                       last SWITCH_ARGS ;
        }
        if ($ARGV[0] =~ /^(-f|-fill)$/i ) {
                                       $fill_empty = 1 ;
                                       shift @ARGV ;
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
if ($scenario_fname eq '') {
    print STDERR "Scenario file is mandatory.\n" ;
    $help = 1 ;
}

if ($help) {
    print STDOUT "Syntax:\n" ;
    print STDOUT "$scriptname -v <version> [-i <cpu_id>] [-tar] <scenario_file>\n" ;
    exit 1 ;
}

# -------------------------------------------------------------------------------------
# To remove the file that tells to stop the tests,
# that new_run_allapp.pl may not have been able to remove.

unlink "$runtest_dir/stop.$version" if ( -e "$runtest_dir/stop.$version" ) ;

# -------------------------------------------------------------------------------------
# opening all tests report file
#
$all_report     = "allapp_reports/allapp_report_$version" ;
$all_report_tar = "allapp_reports/allapp_report_${version}.tar" ;
unless (open ALLREPORT, "+<$runtest_dir/$all_report") {
    print STDERR "Can't open ${runtest_dir}/${all_report} for update: $!\n" ;
    print STDERR "Creating ${runtest_dir}/${all_report}\n" ;
    open ALLREPORT, "> $runtest_dir/$all_report" or die "Can't create ${runtest_dir}/${all_report}: $!" ;
}
autoflush ALLREPORT 1 ;

# positionment after the trace header
while ( defined($line = <ALLREPORT>) && ($line !~ /^Concatenation/) ) { }
$curpos = tell(ALLREPORT) ;
seek(ALLREPORT, $curpos, 0) ;
truncate(ALLREPORT, $curpos) ;
close ALLREPORT ;

open ALLREPORT, ">>$runtest_dir/$all_report" or die "Can't open ${runtest_dir}/${all_report}: $!\n" ;
autoflush ALLREPORT 1 ;
binmode ALLREPORT ;

if ($tar_report) {
    if ( -e "$runtest_dir/$all_report_tar" ) {
        @args = ('tar', 'uf' , "$runtest_dir/$all_report_tar", '-C', "$runtest_dir", "$all_report") ;
    }
    else {
        @args = ('tar', 'cf' , "$runtest_dir/$all_report_tar", '-C', "$runtest_dir", "$all_report") ;
    }
    unless (system(@args) == 0) {
        $exit_value = $? >> 8 ;
        $signal_num = $? & 127 ;
        print STDERR join(' ', @args), " failed: $?\n" ;
        print STDERR "exit_value: $exit_value\n" ;
        print STDERR "signal_num: $signal_num\n" ;
    }
}

# -------------------------------------------------------------------------------------
# We read the scenario file

$cpp_cmd = 'scn_cpp.pl' ;
$cpp_cmd = join(' -I ', $cpp_cmd, quotemeta(dirname($scenario_fname)), quotemeta("$runtest_dir/scenarios")) ;

chdir "$launching_dir" ;
# print STDOUT "\n", "${cpp_cmd} < ${scenario_fname}\n\n" ;
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
		   ($a_cpu_id, $line) = ($line =~ /^@([^\s]+)[\s]+(.*)$/gs) ;
		   if (defined($CPU_ID)) {
			   $a_cpu_id = lc(quotemeta($a_cpu_id)) ;
			   if ($a_cpu_id !~ /$CPU_ID/i) {
					# print STDERR "Line for another cpu.\n" ;
					last SWITCH_LINE ;
			   }
		   }
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

           my @paths = glob "$item_path/${qt_run_all_script}" ;
           foreach my $path (@paths) {
               $path =~ s/[\/]${qt_run_all_script}$// ;
               eval {$path = abs_path($path) ;} ;
               if ($@) {
                   print STDERR  "ERROR, master script $paths[0]/${run_all_script} doesn't exist.\n\n" ;
               }
           }
           if ($#paths >= 0) {
               if (($#paths == 0) and (not( -f "$paths[0]/${run_all_script}"))) {
                   print STDERR  "ERROR, master script $paths[0]/${run_all_script} doesn't exist.\n\n" ;
               }
               else {
                   foreach my $path (@paths) {

                      unless (grep(/^$path$/, @run_paths)) {
                          push (@run_paths, $path) ;
                      }
                      # my $nb_variants = $#{$options{$path}} + 1 ;

                      for ($i=0 ; $i <= $#orand_r ; $i++ ) {

                          my @opt_this_path = @{$orand_r[$i]} ;

                          foreach my $opt (@opt_this_path) {
                              # search for system variables in the options and do the replacement
                              $opt = expand_sys_vars($opt) ;
                          }
                          # @{$options{$path}[$nb_variants + $i]} = @opt_this_path ;
                      }
                   } # end foreach $path (@paths)
               } # end if (($#paths == 0) && ( -d "$paths[0]"))
           }
           else {
               print STDERR  "No test at path $runtest_dir/$item_path/ not found.\n" ;
               if ($fill_empty and ($item_path !~ /[\*\.]/)) {
                   push (@run_paths, "$runtest_dir/$item_path") unless (grep(/^$item_path$/, @run_paths)) ;
               }
           } # end if ($#paths >= 0)
       } # end of PATH_AND_OPTIONS
   } # end of test of SWITCH_LINE
} # end of while <SCENARIO> (not eof)
close SCENARIO ;

# -------------------------------------------------------------------------------------

$id_path = 0 ;

RUN_ALL:
while ($#run_paths >= 0) {

    chdir "$runtest_dir" ;
    my $run_path    = $run_paths[$id_path] ;
    my $tmp_runtest = $runtest_dir ;

    if ($#run_paths >= 0) {

        # Concatenation of the test report to the global report
        my $report = "$run_path/reports/report_$version" ;
        stat("$report") ;
        if ( -f _ && -r _ && -s _ ) {
            if (open REPORT, "< $report") {
                print ALLREPORT "\n\n" ;
                while (<REPORT>) {
                    tr/\015//d ;
                    print ALLREPORT ;
                } ;
                close REPORT ;
                if ($tar_report) {
                    my $rep_from_runtest = $report ;
                    $rep_from_runtest =~ s/^\Q${tmp_runtest}\E\/*//s ;

                    @args = ('tar', 'rf' , $all_report_tar, '-C', $tmp_runtest, $rep_from_runtest) ;
                    unless (system(@args) == 0) {
                        $exit_value = $? >> 8 ;
                        $signal_num = $? & 127 ;
                        print STDERR join(' ', @args), " failed: $?\n" ;
                        print STDERR "exit_value: $exit_value\n" ;
                        print STDERR "signal_num: $signal_num\n" ;
                    }
                }
            }
            else {
                print STDERR "File $report is unreadable.\n" ;
            }
        }
        push (@runned_paths, splice(@run_paths, $id_path, 1)) ;
        $id_path = 0 ;
    } # end if ($#run_paths >= 0)
} # end of while ($#run_paths >= 0)

# -------------------------------------------------------------------------------------

FIN_run_allapp:

close ALLREPORT ;
exit 0 ;
