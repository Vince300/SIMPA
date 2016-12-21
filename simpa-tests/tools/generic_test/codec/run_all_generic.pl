#!/usr/bin/env perl

# version:              1.9
# date of creation:     22/11/2002
# date of modification: 14/03/2005
# author:               Guerte Yves
# usage:                run_all [MASTER SCRIPT OPTIONS] [COMPILER OPTIONS]  // see manual part

use POSIX ;
use FileHandle ;
use IO::Handle ;
use File::Copy ;
use File::Temp qw/tempfile/ ;
use Getopt::Long qw(:config no_ignore_case permute pass_through) ;
use Cwd qw(cwd chdir abs_path ) ;
use Sys::Hostname ;
use Scalar::Util qw(looks_like_number);

if (exists($ENV{'QA_TOOLS'})) {
    use lib "$ENV{'QA_TOOLS'}/libperl" ;
    use tools ;
    use run_sim ;
    use cflags_cygfilter ;
    use qa_xml ;

    unless(eval{$runtest_dir = abs_path("$ENV{'NEW_QA_ROOT'}/runtest")}) {
    print STDERR "ERROR: '$ENV{'NEW_QA_ROOT'}/runtest': No such directory.\n" ;
    exit 1 ;
    }
    $runtest_dir =~ s/\/*$// ;
}
else {
    print STDERR "\nERROR, the variable QA_TOOLS must be set !\n" ;
    exit 1
}

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

$test_path = cwd() ;
chomp $test_path ;
$test_path =~ s/^.*\/runtest\///i ;

$PC = (sys_kind() eq 'PC') ;

system('mkdir', '-p', "$runtest_dir/atomic_fail_reports") unless ( -d "$runtest_dir/atomic_fail_reports") ;

# --------------------------- OPTIONS ---------------------------------------------------
# What are the default targets
# and the other default environment values (directories, ...) ?
#
if ( -f 'run_all_params.pm' ) {
    use run_all_params ;
}
else {
    die "File 'run_all_params.pm' doesn't exist." ;
}

# input, outputs and ref directories
#
$input_dir  = '../inputs' ;
$output_dir = 'outputs' ;
$ref_dir    = '../ref' ;
#
# Their Regular Expression (for search use)
#
$in_d_re  = quotemeta($input_dir) ;
$out_d_re = quotemeta($output_dir) ;
$ref_d_re = quotemeta($ref_dir) ;

# --------------------------- WE READ MASTER SCRIPT POSSIBILITIES -----------------------

# We read from the library the simulators that are supported
$simul_list = join(', ', @sim_available) ;

# --------------------------- MAN -------------------------------------------------------
# Manual

sub man {
    print STDOUT "usage: $scriptname [MASTER SCRIPT OPTIONS] [--] [COMPILER OPTIONS]\n" ;
    print STDOUT "\n" ;
    print STDOUT "MASTER SCRIPT OPTIONS:\n" ;
    print STDOUT "-f,  -functional              functional test mode (exclusive with the -p option)\n" ;
    print STDOUT "-p,  -performance             performance test mode (exclusive with the -f option)\n" ;
    print STDOUT "-v,  -version     [VERSION]   version string of this test\n" ;
    print STDOUT "-l,  -level       [LEVEL]     level value among [skip, compile, light, full], default is full\n" ;
    print STDOUT "-t,  -target      [TARGET]    make target name (-target <target_name> can occur many times)\n" ;
    print STDOUT "-n,  -not, -notarget [TARGET]    skipped target name (-not <target_name> can occur many times)\n" ;
    print STDOUT "-m,  -makefile    [MAKEFILE]  makefile file name\n" ;
    print STDOUT "-mo, -make_option [MAKEFILE OPTION] (can occur many times)\n" ;
    print STDOUT "-s,  -simulator   [SIMULATOR] simulator reference among [${simul_list}]\n" ;
    print STDOUT "-so, -sim_option  [SIMULATOR OPTION] simulator option (can occur many times)\n" ;
    print STDOUT "-pf, -param_file  [FILENAME] file that appears in the compiler options, to include in the report\n" ;
    print STDOUT "-no_clean                     don't delete files after compilation nor execution\n" ;
    print STDOUT "-no_pre_clean                 don't delete files before compilation\n" ;
    print STDOUT "\n" ;
    print STDOUT "COMPILER OPTIONS are options passed to the compiler via the CFLAGS makefile parameter\n" ;
    print STDOUT "the \"--\" parameter is used to stop the parameters parsing:\n" ;
    print STDOUT "all the parameters that follow are compiler options (this allows -v, -l, -t, ...).\n" ;
    print STDOUT "\n" ;
}

# --------------------------- WE READ THE PARAMETERS ------------------------------------

# With no parameter: manual
#
if ($#ARGV == -1) {
        man() ;
        exit 1 ;
}
$empty          = undef ;
$scn_idx        = undef ;
$purify_test    = undef ;
$func_mode      = undef ;
$perf_mode      = undef ;
$version        = undef ;
$level          = undef ;
@p_targets      = () ;
@p_notargets    = () ;
$p_makefile     = undef ;
@make_options   = () ;
$simulator      = undef ;
@sim_options    = () ;
@param_files    = () ;
@options        = () ;
$no_clean       = undef ;
$no_pre_clean   = undef ;
$atomic_fail_reports = undef ;
@unknown_params = () ;

sub add_unknown_params {
    push(@unknown_params, @_);
}

$ok_params = GetOptions('p|perf'           => \$perf_mode,
                        'f|func'           => \$func_mode,
                        'empty'            => \$empty,
                        'scn_idx=s'        => \$scn_idx,
                        'purify'           => \$purify_test,
                        'v|version=s'      => \$version,
                        'l|level=s'        => \$level,
                        't|target=s'       => \@p_targets,
                        'n|not|notarget=s' => \@p_notargets,
                        'm|makefile=s'     => \$p_makefile,
                        'mo|make_option=s' => \@make_options,
                        's|simulator=s'    => \$simulator,
                        'so|sim_option=s'  => \@sim_options,
                        'pf|param_file=s'  => \@param_files,
                        'no_clean'         => \$no_clean,
                        'no_pre_clean'     => \$no_pre_clean,
                        'atomic_fail_reports'   => \$atomic_fail_reports,
                        '<>'               => \&add_unknown_params) ;


# --------------------------------------------------------
# Test mode
unless (defined $perf_mode) {
    unless (defined $func_mode) {
        $test_mode = $default_test_mode ;
        $func_mode = ($test_mode =~ /functional/) ;
        $perf_mode = ($test_mode =~ /performance/) ;
    }
    else {
        $test_mode = 'functional' ;
    }
}
else {
    if (defined $func_mode) {
        $test_mode = 'functional+performance' ;
        print STDERR "\nERROR, functional and performance test modes are not allowed simultaneously.\n" ;
        $ok_params = 0 ;

    }
    else {
        $test_mode = 'performance' ;
        # Forbidden for unit tests only (for codec, it is allowed)
        #
#unit_tests        print STDERR "\nERROR, performance test mode alone is not allowed for unit tests.\n" ;
#unit_tests        $ok_params = 0 ;
    }
}

# --------------------------------------------------------
# Version
unless (defined $version) {
    print STDERR "\nERROR, the version parameter is mandatory.\n" ;
    $ok_params = 0 ;
}

# --------------------------------------------------------
# Level
if (defined $level) {
    if ($level =~ /^(skip|compile|light|full)$/i) {
        $level = lc($level) ;
    }
    else {
        print STDERR "\nERROR, the level $level is unknown, assuming 'full'.\n" ;
        $level = full ;
    }
}
else {
    print STDERR "The level is not defined, assuming 'full'.\n" ;
    $level = full ;
}

# --------------------------------------------------------
# Targets with parameter -target target1,target2,etc
#
@p_targets   = nodup(split(/,/,join(',',@p_targets))) ;
@p_notargets = nodup(split(/,/,join(',',@p_notargets))) ;
#unit_tests    @targets = () ;
@targets = @default_targets ;
@unknown_targets = () ;


# We read the files_in_out_ref* files
#
SWITCH_LEVEL: {
    if ($level eq 'compile') {
        $fior_file = $fnames ;
        last SWITCH_LEVEL ;
    }
    elsif ($level eq 'light') {
        $fior_file = $fnames_light ;
        last SWITCH_LEVEL ;
    }
    elsif ($level eq 'full') {
        $fior_file = $fnames ;
        last SWITCH_LEVEL ;
    }
} # end SWITCH_LEVEL
@fior_lines = read_goodlines($fior_file) ;

# We extract the targets from the file lines
@fior_targets = @fior_lines ;
foreach my $t (@fior_targets) {
	$t =~ s/;.*$//g ;
	$t =~ s/^\s+//;
    $t =~ s/\s+$//;

    # We remove the optional simulation timeout
	if ($t =~ /<\s*\d+\s*$/) {
	   $t =~ s/<\s*\d+\s*$// ;
	   $t =~ s/\s+$//;
	}
}
@fior_targets = nodup(@fior_targets) ;

# We select the targets
if (@p_targets) {

    my $i_p_target = $#p_targets ;
    while ($i_p_target >= 0) {
        my $p_target = $p_targets[$i_p_target] ;

        unless (grep(/^$p_target$/, @fior_targets)) {
            splice(@p_targets, $i_p_target, 1) ;
            push(@unknown_targets, $p_target . ' (unknown)') ;
            print STDERR "\n\nERROR: the target \"$p_target\" doesn't exist in the file \"$fior_file\".\n\n" ;
        }
        $i_p_target-- ;
    }
    @targets = @p_targets ;
}
else {
    @targets = @fior_targets ;
}

# We unselect the targets
if (@p_notargets) {

    my $i_p_notarget = $#p_notargets ;
    while ($i_p_notarget >= 0) {
        my $p_notarget = $p_notargets[$i_p_notarget] ;

        unless (grep(/^$p_notarget$/, @fior_targets)) {
            splice(@p_notargets, $i_p_notarget, 1) ;
            print STDERR "\n\nWARNING: the target \"$p_notarget\" doesn't exist in the file \"$fior_file\".\n\n" ;
        }
        else {
            @targets=grep(!/^$p_notarget$/, @targets)
        }
        $i_p_notarget-- ;
    }
}

unless (@targets) {
    print STDERR "\n\nWARNING: there is no target to test in the parameter file nor in the parameters.\n\n" ;
}
# --------------------------------------------------------
# Makefile
if (defined $p_makefile) {
    $makefile = $p_makefile ;
}
else {
    $makefile = $default_makefile ;
}
if (! -f $makefile) {
    print STDERR "\nERROR, the makefile '$makefile' doesn't exist.\n" ;
    $ok_params = 0 ;
}

# --------------------------------------------------------
# Make options
@make_options = split(/,/,join(',',@make_options));
unless (@make_options) {
    # nothing to do
}

# --------------------------------------------------------
# Simulator
unless (defined $simulator) {
    $simulator = $default_simulator ; # defined in run_sim.pm
}
elsif (! grep(/^$simulator$/, @sim_available)) {
    $simulator .= " (unknown)" ;
    $unknown_simulator = 1 ;
}
# --------------------------------------------------------
# Simulator options
unless (@sim_options) {
    # nothing to do
}

# --------------------------------------------------------
# No_clean options
unless (defined $no_clean) {
    # nothing to do
}

# --------------------------------------------------------
# Parameter files that appear in the compiler options, to include in the report
@param_files = split(/,/,join(',',@param_files));
unless (@param_files) {
    # nothing to do
}

# --------------------------------------------------------
# Are all the parameters OK ?
#
unless ($ok_params) {
    man() ;
    exit 1 ;
}
# --------------------------------------------------------
# Parameters after "--" are compiler options
#
# We surround by " the parameters containing a space,
# we correct the file parameter of :
# -Xicode "-F <file>",
# -Xicode "-a <file>,
# -ma <file> application configuration file,
# -mc <file> machine configuration file,
# -mem <file> memory control file
#
if (@ARGV) {
    shift(@ARGV) if ($ARGV[0] eq '--') ;
}
@options = cflags_cygfilter(@unknown_params, @ARGV) ;

# --------------------------- WE COMPLETE OPTIONS WITH MAKEFILE CONTENT ---------------

# We read the names of the executable files
%exe_fnames = () ;
%dasm_exe_fnames = () ;

# If there exist eln targets
$eln_targets = 0 ;

$dasm_mode = undef ;

@res = () ;

unless ($empty) {
    @cmd = ('gmake', '-f', $makefile, @targets, @make_options, '-r', '-p', '-n') ;
    @res = execute_it_stdout(@cmd) ;

    # We get bin and obj files extensions
    $obj_ext = 'eln' ;
    $bin_ext = 'eld' ;
    my @obj_ext_defs = grep(/^\s*O\s*:?=/i, @res) ;
    if (@obj_ext_defs) {
        my $obj_ext_def = $obj_ext_defs[0] ;
        $obj_ext_def =~ s/^\s*O\s*:?=\s*(.*)\s*$/$1/i ;
        if ($obj_ext_def ne '') {
            $obj_ext = $obj_ext_def ;
        }
    }
    my @bin_ext_defs = grep(/^\s*E\s*:?=/i, @res) ;
    if (@bin_ext_defs) {
        my $bin_ext_def = $bin_ext_defs[0] ;
        $bin_ext_def =~ s/^\s*E\s*:?=\s*(.*)\s*$/$1/i ;
        if ($bin_ext_def ne '') {
            $bin_ext = $bin_ext_def ;
        }
    }

        # We test if the disassemble/re-assemble mode is enabled.
        # if 'mo options' contains "DASM=eln" ou "DASM=eld"
    if (grep(/DASM=${obj_ext}/, @make_options)) {
        $dasm_mode = $obj_ext ;
    } elsif (grep(/DASM=${bin_ext}/, @make_options)) {
        $dasm_mode = $bin_ext ;
    }

    # We get bin, obj and dasm directories
    $obj_dir = 'obj' ;
    $bin_dir = 'bin' ;
    $dasm_dir = 'dasm' ;
    my @obj_dir_defs = grep(/^\s*obj_dir\s*:?=/i, @res) ;
    if (@obj_dir_defs) {
        my $obj_dir_def = $obj_dir_defs[0] ;
        $obj_dir_def =~ s/^\s*obj_dir\s*:?=\s*(.*)\s*$/$1/i ;
        if ($obj_dir_def ne '') {
            $obj_dir = $obj_dir_def ;
        }
    }
    my @bin_dir_defs = grep(/^\s*bin_dir\s*:?=/i, @res) ;
    if (@bin_dir_defs) {
        my $bin_dir_def = $bin_dir_defs[0] ;
        $bin_dir_def =~ s/^\s*bin_dir\s*:?=\s*(.*)\s*$/$1/i ;
        if ($bin_dir_def ne '') {
            $bin_dir = $bin_dir_def ;
        }
    }
    my @dasm_dir_defs = grep(/^\s*dasm_dir\s*:?=/i, @res) ;
    if (@dasm_dir_defs) {
        my $dasm_dir_def = $dasm_dir_defs[0] ;
        $dasm_dir_def =~ s/^\s*dasm_dir\s*:?=\s*(.*)\s*$/$1/i ;
        if ($dasm_dir_def ne '') {
            $dasm_dir = $dasm_dir_def ;
        }
    }
    # We get the name of the compiler
    $CC = 'unknown cc' ;
    my @CC_defs = grep(/^\s*CC\s*:?=/i, @res) ;
    if (@CC_defs) {
        my $CC_def = $CC_defs[0] ;
        $CC_def =~ s/^\s*CC\s*:?=\s*(.*)\s*$/$1/i ;
        if ($CC_def ne '') {
            $CC = $CC_def ;
        }
    }

    my $i_target = $#targets ;
    while ($i_target >= 0) {
        my $target = $targets[$i_target] ;

    #    my @cmd = ('gmake', '-f', $makefile, $target, @make_options, '-r', '-p', '-n') ;
    #    @res = execute_it_stdout(@cmd) ;

        # We verify that the targets exist in the makefile
        my @target_defs = grep(/^$target:/, @res) ;
        if (@target_defs) {
            my $exe_fname = $target_defs[0] ;
            $exe_fname =~ s/^$target:\s*([^\s]*)\s*.*$/$1/ ;
            $exe_fnames{$target} = $exe_fname ;
            my $dasm_exe_fname = $exe_fname ;
            $dasm_exe_fname =~ s/^$bin_dir/$dasm_dir/ ;
            $dasm_exe_fnames{$target} = $dasm_exe_fname ;
            $eln_targets = 1 if (is_sc_sim($simulator) and ($exe_fname =~ /\.${obj_ext}$/)) ;
        }
        else {
            print STDERR "\n\nWARNING: target $target is unknown in makefile $makefile.\n\n" ;
            splice(@targets, $i_target, 1) ;
            push(@unknown_targets, $target . ' (unknown)') ;
        }
        $i_target-- ;
    }
    unless (@targets) {
        print STDERR "\n\nWARNING: there is no target to test in the parameter file nor in the parameters.\n\n" ;
    }

    # We get the mandatory options
    @mandatory_opts = () ;
    my @mandatory_defs    = grep(/^\s*mandatory_cflags\s*:?=/i, @res) ;
    my @mandatory_CC_defs = grep(/^\s*mandatory_${CC}\s*:?=/i, @res) ;
    if (@mandatory_defs) {
        my $mandatory_def = $mandatory_defs[0] ;
        $mandatory_def =~ s/^\s*mandatory_cflags\s*:?=\s*(.*)\s*$/$1/i ;
        @mandatory_opts = ($mandatory_def =~ /([^ \t\"\']+|\"[^\"]*\"|\'[^\']*\')/gsx) ;
        #DEBUG    print STDOUT "Mandatory options == ", join(' ', @mandatory_opts), "\n\n" if (@mandatory_opts) ;
    }
    if (@mandatory_CC_defs) {
        my $mandatory_CC_def = $mandatory_CC_defs[0] ;
        $mandatory_CC_def =~ s/^\s*mandatory_${CC}\s*:?=\s*(.*)\s*$/$1/i ;
        @mandatory_CC_opts = ($mandatory_CC_def =~ /([^ \t\"\']+|\"[^\"]*\"|\'[^\']*\')/gsx) ;
        #DEBUG    print STDOUT "Mandatory $CC options == ", join(' ', @mandatory_CC_opts), "\n\n" if (@mandatory_CC_opts) ;
    }
    $mand_CFLAGS = join(' ', @mandatory_opts, @mandatory_CC_opts) ;
}
else {
    $obj_ext = '' ;
    $bin_ext = '' ;
    $obj_dir = 'obj' ;
    $bin_dir = 'bin' ;
    $dasm_dir = 'dasm' ;
    $CC = $ENV{'CC'} if (exists($ENV{'CC'})) ;
    @mandatory_opts = () ;
    @mandatory_CC_opts = () ;
}

# --------------------------- WE PRINT SOME INFORMATION ON STDOUT ---------------
$CFLAGS = join(' ', @options) ;

unless ($empty) {
    print STDOUT "\n" ;
    print STDOUT "test mode == $test_mode\n" ;
    print STDOUT "version   == $version   \n" ;
    print STDOUT "level     == $level     \n" ;
    print STDOUT "targets   == ", join(', ', @targets, @unknown_targets), "\n" ;
    print STDOUT "makefile  == $makefile  \n" ;
    print STDOUT "make opt. == ", join(', ', @make_options) , "\n" ;
    print STDOUT "simulator == $simulator \n" ;
    print STDOUT "sim opt.  == ", join(', ', @sim_options) , "\n" ;
    print STDOUT "options     == ", join(', ', @options, @mandatory_opts, @mandatory_CC_opts) , "\n" ;
    print STDOUT "param_files == ", join(', ', @param_files) , "\n\n" ;
}


# --------------------------- WE GET INFORMATION ABOUT THE INPUT FILES ---------------

%inputs_nb_frames       = () ;
%inputs_samples_per_frm = () ;
%inputs_sample_acq_freq = () ;

GET_FILES_INFOS: {
    # Filename ;              number of frames ; number of samples per frame ; frequency of acquisition of the samples (Hz)
    my $nb_items = 4 ;

    if ( -f "$files_infos" ) {

        # We read all the lines of the file 'inputs/files.infos'
        my @inputs_infos = read_goodlines("$files_infos") ;

        foreach my $line (@inputs_infos) {

            my (@items) = ($line =~ /[^;]+/gs) ;

            # if the number of items separated by ';' is not equal to $nb_items
            if ($#items + 1 < $nb_items) {
                print STDERR "\nERROR: line of '$files_infos' not recognized:\n\n" ;
                print STDERR "$line\n\n" ;
            }
            else {
                foreach my $item (@items) {
                    $item =~ s/^\s+//;
                    $item =~ s/\s+$//;
                }
                # Filename ;              number of frames ; number of samples per frame ; frequency of acquisition of the samples (Hz)
                my $filename        = shift @items ;
                my $nb_frames       = shift @items ;
                my $samples_per_frm = shift @items ;
                my $sample_acq_freq = shift @items ;

                $inputs_nb_frames{$filename}       = $nb_frames ;
                $inputs_samples_per_frm{$filename} = $samples_per_frm ;
                $inputs_sample_acq_freq{$filename} = $sample_acq_freq ;
            }
        } # end foreach my $line (@inputs_infos)
    } # end if ( -f "inputs/files.infos" )
    else {
        # No information about the input files
        print STDERR "\nWARNING: file '$files_infos' not found.\n\n" ;
    }
} # end GET_FILES_INFOS


# --------------------------- HERE ARE THE FUNCTIONS FORMATTING THE OUTPUT ---------------

# function which format a number on 2 characters
sub fmt_2car {
    return substr('0' . $_[0], -2) ;
}

sub formatted_date {
    my ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime(time);
    # $year -= 100 ; $year = fmt_2car($year) ;
    $year += 1900 ;
    $mon  += 1 ;
    # $date = fmt_2car($mon) . "-" . fmt_2car($mday) . "-" . fmt_2car($year) ;
    my $date = fmt_2car($mday) . '/' . fmt_2car($mon) . '/' .  $year
                . ' ' . fmt_2car($hour) . ':' . fmt_2car($min) . ':' . fmt_2car($sec)  ;
    return $date ;
}
#2004-11-13T23:53:59Z
sub xml_formatted_date {
	my ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime(time);
	# $year -= 100 ; $year = fmt_2car($year) ;
	$year += 1900 ;
	$mon  += 1 ;
	# $date = fmt_2car($mon) . "-" . fmt_2car($mday) . "-" . fmt_2car($year) ;
	my $date = $year . '-' . fmt_2car($mon) . '-' . fmt_2car($mday) .
				'T' . fmt_2car($hour) . ':' . fmt_2car($min) . ':' . fmt_2car($sec) . 'Z' ;
	return $date ;
}

# In case of user break, we continue in the $empty mode but with this variable set
$global_break = 0 ;

# Counter for atomic reports, different from $num_fail
# because atomic fails are reported in the functional stage if they occur there
# and then not in the performance stage
$fail_counter = 0 ;

# computed when incrementing $num_fail when reporting in 2nd stage a FAIL for the 1st stage
$already_reported = 0 ;

# test name without blanks nor special chars, for atomic fail reports
$test_clean_name = ${str15_title} ;
$test_clean_name =~ s/^\s+// ;
$test_clean_name =~ s/\s+$// ;
$test_clean_name = opt_to_str($test_clean_name) ;

# The flag to test if we can generate the report in this mode iteration :
# We can if we are in a functional+performance mode at the performance stage
# or if there is only one test mode
# or if we test in compile only level
#
$ok_to_report = 0 ;

# Start and end of test target execution/simulation
$exec_start_date = undef ;
$exec_end_date = undef ;

# Sums
$sum_size = $sum_cycles = $num_fail = 0 ;
$dasm_sum_size = 0 ;

# Maximum length of the columns about targets
our $max_targets_l  = length('Target')  ;

# Maximum length of the column about input files
$max_in_files_l = length('Input file') unless ($perf_mode) ;

# ---------------------------------------------------------
sub write_xml_test_config {
    my $HANDLER = shift ;

    pxml_begin_tag      ($HANDLER, 'TEST') unless defined(${scn_idx}) ;
    pxml_begin_tag      ($HANDLER, 'TEST', ['scn_idx', ${scn_idx}]) if defined(${scn_idx}) ;
    pxml_atomic_element ($HANDLER, 'Test_path', ${test_path}) ;
    pxml_atomic_element ($HANDLER, 'Start_date', ${xml_date}) ;
    pxml_atomic_element ($HANDLER, 'Test_name', ${str15_title}) ;
    pxml_atomic_element ($HANDLER, 'Host_name', ${HOST}) ;
    pxml_atomic_element ($HANDLER, 'Test_mode', ${test_mode}) ;
    pxml_atomic_element ($HANDLER, 'Level', ${level}) ;
    pxml_atomic_element ($HANDLER, 'CC_options', ${CFLAGS}) ;
    pxml_atomic_element ($HANDLER, 'CFLAGS', join(' ', ${CFLAGS}, ${mand_CFLAGS})) ;
    pxml_atomic_element ($HANDLER, 'Makefile', ${makefile}) ;
    pxml_atomic_element ($HANDLER, 'Make_options', join(' ', @make_options)) ;
    pxml_atomic_element ($HANDLER, 'Simulator', ${simulator}) ;
    pxml_atomic_element ($HANDLER, 'Sim_options', join(' ', @sim_options)) ;
    # Targests list not usefull
    #    pxml_begin_tag      ($HANDLER, 'Targets') ;
    #    foreach my $target (@targets[0..$#targets], @unknown_targets) {
    #        pxml_atomic_element ($HANDLER, 'target', ${target}) ;
    #    }
    #    pxml_end_tag        ($HANDLER, 'Targets') ;
    return ;
}
# ---------------------------------------------------------
sub line_report {
    my ($report_fhdl, $target, $descr, $in_file, $status, $size, $nb_cyc, $argvtab, $exec_time, @others) = @_ ;
    my ($argv_str, $n_frames, $mips, $cycles_p_frame, $e_freq) = (undef, undef, undef, undef, undef) ;

    # Supplementary columns are 16 chars width
    my $col_width = 16 ;

    # @others contains other information. If not empty, first one is a string with  the cycles per frame and then the MIPS
    #
    @others = split(/,/, join(',', map({defined($_) ? $_ : ' '} @others))) ;

    $cycles_p_frame = $others[0] if (@others) ;
    if ($#others > 0) {
        my (@items) = ($others[1] =~ /^\s*([0-9]+\.?[0-9]*)\s*MIPS\s*$/gsi) ;
        $mips = $items[0] if (@items) ;
    }

    # If this is a real execution result and not a header formatting
    if ($status =~ /^(PASS|FAIL)/ ) {

        # if this is the break event
        if ($status =~ /^FAIL\(break\)/ ) {
            $global_break = 1 ;
        }
        else {
            ($status, $size, $nb_cyc, @others) = ('', '', '', []) if ($empty) ;
            $status = 'break' if ($global_break) ;

            # We suppress the diretory part for inputs if it exists
            $in_file =~ s/^inputs\/// ;
            $in_file =~ s/^\.\.\/inputs\/// ;
            $in_file =~ s/^\.\/// ;

            $n_frames       = $inputs_nb_frames{$in_file}       if exists($inputs_nb_frames{$in_file}) ;
            $sample_p_frame = $inputs_samples_per_frm{$in_file} if exists($inputs_samples_per_frm{$in_file}) ;
            $e_freq         = $inputs_sample_acq_freq{$in_file} if exists($inputs_sample_acq_freq{$in_file}) ;

            $argv_str = join(' ', @{$argvtab}) if (@{$argvtab}) ;

            # Files to write the report
            my @HANDLERS_TO_WRITE = () ;
            push(@HANDLERS_TO_WRITE, $XML_REPORT) if ($ok_to_report) ;

            # The handle of the file we will open for atomic fail report, if necessary
            my $XML_FAIL_REPORT = undef ;

            if ($atomic_fail_reports and ($status =~ /^FAIL/ )) {
                if ($already_reported) {
                    # computed when incrementing $num_fail when reporting in 2nd stage a FAIL for the 1st stage
                    $already_reported = 0 ;
                }
                else {
                    $fail_counter++ ;
                    ($XML_FAIL_REPORT, $fail_report_name) = tempfile("report_${version}.${fail_counter}.${test_clean_name}.${target}.XXXX", DIR=>"$runtest_dir/atomic_fail_reports", SUFFIX=>".xml", OPEN=>1, UNLINK=>0)
                        or die "Can't open new atomic fail report: '$runtest_dir/atomic_fail_reports/report_${version}.${fail_counter}.${test_clean_name}.${target}.XXXX.xml'." ;

                    write_xml_test_config($XML_FAIL_REPORT) ;

                    push(@HANDLERS_TO_WRITE, $XML_FAIL_REPORT) ;
                }
            }

            foreach my $A_HANDLER (@HANDLERS_TO_WRITE) {
                # XML raw data
                #
                pxml_begin_tag      ($A_HANDLER, 'Exec') ;
                pxml_atomic_element ($A_HANDLER, 'target', ${target})                 if (defined(${target})) ;
                pxml_atomic_element ($A_HANDLER, 'description', ${descr})             if (defined(${descr})) ;
                pxml_atomic_element ($A_HANDLER, 'status', ${status})                 if (defined(${status})) ;
                pxml_atomic_element ($A_HANDLER, 'size', ${size})                     if (defined(${size})) ;
                pxml_atomic_element ($A_HANDLER, 'input', ${in_file})                 if (defined(${in_file})) ;
                pxml_atomic_element ($A_HANDLER, 'n_frames', ${n_frames})             if (defined(${n_frames})) ;
                pxml_atomic_element ($A_HANDLER, 'sample_p_frame', ${sample_p_frame}) if (defined(${sample_p_frame})) ;
                pxml_atomic_element ($A_HANDLER, 'e_freq', ${e_freq})                 if (defined(${e_freq})) ;
                pxml_atomic_element ($A_HANDLER, 'argv', ${argv_str})                 if (defined(${argv_str})) ;
                pxml_atomic_element ($A_HANDLER, 'cycles', ${nb_cyc})                 if (defined(${nb_cyc})) ;
                pxml_atomic_element ($A_HANDLER, 'exec_time', ${exec_time})           if (defined(${exec_time})) ;
                pxml_atomic_element ($A_HANDLER, 'cycles_p_frame', ${cycles_p_frame}) if (defined(${cycles_p_frame})) ;
                pxml_atomic_element ($A_HANDLER, 'MIPS', ${mips})                     if (defined(${mips})) ;
                pxml_atomic_element ($A_HANDLER, 'start_date', ${exec_start_date})   if (defined(${exec_start_date})) ;
                pxml_atomic_element ($A_HANDLER, 'end_date', ${exec_end_date})       if (defined(${exec_end_date})) ;
                pxml_end_tag        ($A_HANDLER, 'Exec') ;
            }

            if (defined($XML_FAIL_REPORT)) {
                pxml_atomic_element       ($XML_FAIL_REPORT, 'End_date', xml_formatted_date()) ;
                pxml_end_tag              ($XML_FAIL_REPORT, 'TEST') ;
                close $XML_FAIL_REPORT ;

                open  $XML_FAIL_REPORT_FLAG, ">$fail_report_name.flagged_new" or die "Can't open the atomic_fail_reports flag file: $fail_report_name.flagged_new" ;
                close $XML_FAIL_REPORT_FLAG ;
            }
        }
    }

    unless ($empty) {
        my $others_str = '' ;
        $others_str = '; ' . join('; ', map({sprintf("%16s", $_)} @others)) if (@others) ;

        if (looks_like_number($nb_cyc)) {
        	$nb_cyc = sprintf("%.2f", $nb_cyc);
        }

        if ($perf_mode) {
            printf { $report_fhdl } "%       -${max_targets_l}s;%                20s;%      9s;%           15s%s\n", $descr, $status, $size, $nb_cyc, $others_str ;
            printf STDOUT           "%       -${max_targets_l}s;%                20s;%      9s;%           15s%s\n", $descr, $status, $size, $nb_cyc, $others_str ;
        }
        else {
            printf { $report_fhdl } "%       -${max_targets_l}s, %${max_in_files_l}s;%                20s;%      9s;%           15s%s\n", $descr, $in_file, $status, $size, $nb_cyc, $others_str ;
            printf STDOUT           "%       -${max_targets_l}s, %${max_in_files_l}s;%                20s;%      9s;%           15s%s\n", $descr, $in_file, $status, $size, $nb_cyc, $others_str ;
        }
    } # end unless ($empty)
}

# ---------------------------------------------------------
sub head_report {
    my $perf_unit = 'Num of cycles';
	if (! compute_cyc($simulator)) {
    	$perf_unit = 'Seconds';
    }

	unless ($empty) {
        if ($perf_mode) {
            line_report ($REPORT, undef,
                                             'Target',           '',            'Status','Size (b)',      $perf_unit, undef, undef, $perf_unit.'/fr, ...'
                        ) ;
        print  $REPORT "-" x $max_targets_l, "-------------------------------------------------------------------------","\n" ;
        print  STDOUT  "-" x $max_targets_l, "-------------------------------------------------------------------------","\n" ;
        }
        else {
            line_report ($REPORT, undef,
                                             'Target', 'Input file',            'Status','Size (b)',      $perf_unit, undef, undef, $perf_unit.'/fr, ...'
                        ) ;
        print  $REPORT "-" x $max_targets_l, "-----------------------------------------------------------------------------------------------","\n" ;
        print  STDOUT  "-" x $max_targets_l, "-----------------------------------------------------------------------------------------------","\n" ;
        }
    } # end unless ($empty)
}

sub end_report {
    # pxml_until_tag_level      ($XML_REPORT, 1)  ; # like next one
    pxml_until_in_tag         ($XML_REPORT, 'test')  ;
    pxml_atomic_element       ($XML_REPORT, 'End_date', xml_formatted_date()) ;
    pxml_until_tag_level      ($XML_REPORT, -1)  ;
    unless ($empty) {
        if ($perf_mode) {
            print  $REPORT "-" x $max_targets_l, "-------------------------------------------------------------------------","\n" ;
            print  STDOUT  "-" x $max_targets_l, "-------------------------------------------------------------------------","\n" ;
            line_report ($REPORT, undef,
                                           'Total',                  '', 'num F_A_I_L = '.$num_fail,$sum_size,       $sum_cycles, undef, undef, @others
                        ) ;
            line_report ($REPORT, undef,
                                     'Total(DASM)',                  '', ''                        ,$dasm_sum_size,       '', '', undef, undef
                        ) if ($dasm_mode) ;
        }
        else {
			print  $REPORT "-" x $max_targets_l, "-----------------------------------------------------------------------------------------------","\n" ;
			print  STDOUT  "-" x $max_targets_l, "-----------------------------------------------------------------------------------------------","\n" ;
            line_report ($REPORT, undef,
                                           'Total',                  '', 'num F_A_I_L = '.$num_fail,$sum_size,       $sum_cycles, undef, undef, @others
                        ) ;
            line_report ($REPORT, undef,
                                     'Total(DASM)',                  '', ''                        ,$dasm_sum_size,       '', '', undef, undef
                        ) if ($dasm_mode) ;
        }
        print  $REPORT "\n\n" ;
        print  STDOUT "\n\n" ;

        foreach my $param_file_name (@param_files) {

            unless (open(FOO, "< $param_file_name")) {
                printf $REPORT "* Parameter file: %20s not found *************\n", $param_file_name ;
                printf STDOUT  "* Parameter file: %20s not found *************\n", $param_file_name ;
            }
            else {
                printf $REPORT "* Parameter file: %20s ***********************\n", $param_file_name ;
                printf STDOUT  "* Parameter file: %20s ***********************\n", $param_file_name ;
                while ( <FOO> ) {
                    chomp ;
                    # We strip newline (LF, NL) ; return (CR) ; form feed (FF) ; alarm (bell) (BEL) ; escape (think troff)  (ESC)
                    s/[\n\r\f\a\e]//g ;
                    print $REPORT $_, "\n" ;
                    print STDOUT  $_, "\n" ;
                }
                close FOO ;
                printf $REPORT "* End of parameter file: %20s ****************\n\n", $param_file_name ;
                printf STDOUT  "* End of parameter file: %20s ****************\n\n", $param_file_name ;
            }
        }
        print  $REPORT "\n\n" ;
        print  STDOUT  "\n\n" ;
    } # end unless ($empty)
}

# --------------------------- WE BEGIN THE $REPORT FILE ----------------------------------

$date = formatted_date() ;
$xml_date = xml_formatted_date() ;

if ($empty) {
    $xml_report_name = "reports/report_${version}.draft.xml" ;
    open $XML_REPORT, ">>$xml_report_name" or die "Can't open the trace file $xml_report_name." ;
    autoflush $XML_REPORT 1 ;
    binmode $XML_REPORT ;
}
else {
    $report_name = "reports/report_${version}" ;
    open $REPORT, ">>$report_name" or die "Can't open the trace file $report_name." ;
    autoflush $REPORT 1 ;
    binmode $REPORT ;

    $xml_report_name = "reports/report_${version}.xml" ;
    open $XML_REPORT, ">>$xml_report_name" or die "Can't open the trace file $xml_report_name." ;
    autoflush $XML_REPORT 1 ;
    binmode $XML_REPORT ;
}

# XML reporting
my $curpos = tell($XML_REPORT) ;
if ($curpos == 0) {
    pxml_header         ($XML_REPORT) ;
    pxml_begin_tag      ($XML_REPORT, 'REPORT', ['version', ${version}]) ;
}
else {
    close $XML_REPORT ;
    unless (open $XML_REPORT, "+<$xml_report_name") {
        print STDERR "Can't open $xml_report_name for update: $!\n" ;
        print STDERR "Creating $xml_report_name\n" ;
        open $XML_REPORT, ">$xml_report_name" or die "Can't create $xml_report_name: $!" ;
    }
    autoflush $XML_REPORT 1 ;

    $curpos = tell($XML_REPORT) ;
    # searching the line before the ending tag </REPORT>
    while ( ($line = <$XML_REPORT>) && ($line !~ /^ *<\/REPORT>/) ) { $curpos = tell($XML_REPORT) }
    seek($XML_REPORT, $curpos, 0) ;
    # Context is: we are already in the 'REPORT' object
    pxml_push_tags('REPORT') ;
}
# We write the test configuration
write_xml_test_config($XML_REPORT) ;

# Standard reporting
unless ($empty) {
    if ($purify_test) {
        $purify_report_name = "$ENV{'NEW_QA_ROOT'}/runtest/allapp_reports/purify_report" ;
        open $PURIFY_REPORT, ">>$purify_report_name" or die "Can't open the trace file $purify_report_name." ;
        autoflush $PURIFY_REPORT 1 ;
        binmode $PURIFY_REPORT ;

        $purify_trace_name = "$ENV{'NEW_QA_ROOT'}/runtest/allapp_reports/purify_trace" ;
        open $PURIFY_TRACE, ">>$purify_trace_name" or die "Can't open the trace file $purify_trace_name." ;
        autoflush $PURIFY_TRACE 1 ;
        binmode $PURIFY_TRACE ;

        @REPORTS_FHDL = ( $REPORT, $PURIFY_REPORT, $PURIFY_TRACE ) ;
    }
    else {
        @REPORTS_FHDL = ( $REPORT ) ;
    }

    if ($test_mode eq 'functional+performance') {
        $report_name_func_pass = $report_name .'_func_pass' ;

        open $REPORT_FP, ">$report_name_func_pass" or die "Can't open the trace file $report_name_func_pass." ;
        autoflush $REPORT_FP 1 ;
        binmode $REPORT_FP ;
        push (@REPORTS_FHDL, $REPORT_FP) ;
    }

    foreach my $REPORT_FHDL (@REPORTS_FHDL) {
        print  $REPORT_FHDL "**************************************************************\n" ;
        printf $REPORT_FHDL "*   Start date: %44s *\n",                                    $date ;
        printf $REPORT_FHDL "*    Test name: %44s *\n",                                    $str15_title ;
        printf $REPORT_FHDL "* Test version: %44s *\n",                                    $version ;
        printf $REPORT_FHDL "*    Test path: %44s *\n",                                    $test_path ;
        printf $REPORT_FHDL "*    Host name: %44s *\n",                                    $HOST ;
        print  $REPORT_FHDL "*                                                            *\n" ;
        printf $REPORT_FHDL "*    Test mode: %44s *\n",                                    $test_mode ;
        printf $REPORT_FHDL "*        Level: %44s *\n",                                    $level ;
        printf $REPORT_FHDL "*   CC options: %44s *\n",                                    $CFLAGS . ' ' . $mand_CFLAGS ;
        if (($#p_targets >= 0) or ($#targets <= 10)) {
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
} # end unless ($empty)

if ($level eq 'skip') {
    print  $REPORT "Skip test.\n" ;
    if ($empty) {
        pxml_until_tag_level      ($XML_REPORT, -1)  ;
        close $XML_REPORT ;
    }
    else {
        close $REPORT ;
    }
    exit 0 ;
}

if ($unknown_simulator) {
    if ($empty) {
        pxml_atomic_element ($XML_REPORT, 'ERROR', 'Unknown simulator') ;
        pxml_until_tag_level      ($XML_REPORT, -1)  ;
        close $XML_REPORT ;
    }
    else {
        close $REPORT ;
    }
    exit 0 ;
}

# --------------------------- WE READ A LIST OF INPUT FILES ACCORDING TO THE LEVEL ---
# level=compile means that one only checks for the compilation,
# level=light   means - for functional tests that the correctness of results is checked
#                       using a reduced set of inputs (one or few input files for example),
#                     - for performance tests that only correctness is checked,
#                       performance test is not run,
# level=full    means - for functional tests that the correctness of results is checked
#                       using every input available,
#                     - for performance tests that both correctness and performance tests
#                       are run.
GET_FILENAMES: {

    # Content of the file FILES_IN_OUT_REF:
    # target ; input file ; description ; launch params ; output file1, reference file1 ; output file2, reference file2 ; ...
    #
    $nb_min_items = 5 ;

    %timeouts_simul = %in_files = %descrs = %params_lists = %out_files = %ref_files = () ;
    %pass_status = %pass_info = %err_msg = () ;

    foreach my $t (@targets) {
		$timeouts_simul{$t}     = [] ;
        $in_files{$t}           = [] ;
        $out_files{$t}          = [] ;
        $ref_files{$t}          = [] ;
        $descrs{$t}             = [] ;
        $params_lists{$t}       = [] ;
        $pass_status{$t}        = [] ;
        $pass_info{$t}          = [] ;
        $err_msg{$t}            = [] ;
    }
    FIOR_LINES:
    foreach my $line (@fior_lines) {

       # test of - empty line or comment
       SWITCH_LINE: {
           if ((length($line) == 0) || ($line =~ '^#')) {
               nul ; # print STDERR "Empty line or comment.\n" ;
               last SWITCH_LINE ;
           }

           my (@items) = ($line =~ /[^;]+/gs) ;
           if ($#items < $nb_min_items - 1) {
               print STDERR "\nERROR, the next line not recognized:\n" ;
               print STDERR "$line\n\n" ;
           }
           else {
               foreach my $item (@items) {
                   $item =~ s/^\s+//;
                   $item =~ s/\s+$//;
               }
               my $target =                     $items[0] ;

			   # Simulation timeout
			   if ($target =~ /<\s*(\d+)\s*$/) {
			   	   my $timeout = $LAST_PAREN_MATCH;
			   	   $target =~ s/<\s*\d+\s*$// ;
			   	   $target =~ s/\s+$//;
			   	   push(@{$timeouts_simul{$target}}, $timeout) ;
			   }
			   else {
			   	   push(@{$timeouts_simul{$target}}, 0) ;
			   }

               # In perf mode, targets are run only one time
               next FIOR_LINES if ($perf_mode and not $func_mode and ($#{$descrs{$target}} >= 0)) ;

               # We search descriptions for the targets we must test
               #
               if (grep(/^$target$/i, @targets)) {

                   # Input files are in the "../inputs" directory ($in_d_re regular expression)
                   $items[1] =~ s/^$in_d_re\/// ;

                   push(@{$in_files{$target}},      $items[1]) ;
                   push(@{$descrs{$target}},        $items[2]) ;
                   push(@{$params_lists{$target}},  $items[3]) ;

                   # We compute length of input file names and targets descriptions
                   my $in_f = $items[1] ;
                   my $l_in_f = length($in_f) ;
                   $max_in_files_l = $l_in_f if ($max_in_files_l < $l_in_f) ;
                   #
                   my $l_descr = length($items[2]) ;
                   $max_targets_l = $l_descr if ($max_targets_l < $l_descr) ;

                   my @out_flist = () ;
                   my @ref_flist = () ;
                   foreach my $out_ref_str (@items[4..$#items]) {
                       my @out_ref = ($out_ref_str =~ /[^,]+/gs) ;
                       if ($#out_ref != 1) {
                           print STDERR "\nERROR, the out-ref string is not recognized: ${out_ref_str}\n" ;
                       }
                       else {
                           $out_ref[0] =~ s/^\s+//;
                           $out_ref[1] =~ s/^\s+//;
                           $out_ref[0] =~ s/\s+$//;
                           $out_ref[1] =~ s/\s+$//;
                           # Output and ref files are in the "outputs" and "../ref" directories ($out_d_re $ref_d_re regular expression)
                           $out_ref[0] =~ s/^$out_d_re\/// ;
                           $out_ref[1] =~ s/^$ref_d_re\/// ;
                           push(@out_flist, $out_ref[0]) ;
                           push(@ref_flist, $out_ref[1]) ;
                       }
                   }
                   #DEBUG print STDOUT "\@out_flist == '", join(', ', @out_flist), "'\n" ;
                   #DEBUG print STDOUT "\@ref_flist == '", join(', ', @ref_flist), "'\n\n" ;
                   push(@{$out_files{$target}}, [@out_flist]) ;
                   push(@{$ref_files{$target}}, [@ref_flist]) ;
               } # end if (grep(/^$target$/i, @targets))
           } # end of test $#items < $nb_items - 1
       } # end of test of SWITCH_LINE
    } # end of foreach my $line (@fior_lines)
} # end GET_FILENAMES

# if the disassembly is enabled. a comment (DASM=eln/eld) is added in the report.
$max_targets_l += length("(DASM=$obj_ext)") if ($dasm_mode) ;

# We print the head of columns in the report
#
head_report unless ($empty) ;

# --------------------------------------------------------
# We build the "timeout" executable

unless ($empty) {
    $timeout_compil_fname = 'timeouts_compil.txt' ;

    unlink 'timeout' ;
    unlink 'timeout.exe' ;
    $has_timeouts_compil = undef ;
    $has_timeouts_cmd    = undef ;

    # Hash table based on the target names
    %timeouts_compil = () ;


    if ( -e $timeout_compil_fname ) {
        my @ARGS = ('gcc', '-o', 'timeout', "$ENV{'QA_TOOLS'}/Other_src/timeout.c") ;
        print STDOUT join(' ', quotes_surround(@ARGS)), "\n\n" ;
        unless (system(@ARGS) == 0) {
            $exit_value = $? >> 8 ;
            $signal_num = $? & 127 ;
            print STDERR "\nERROR, ", join(' ', quotes_surround(@ARGS)), " failed: $?\n" ;
            print STDERR "exit_value: $exit_value\n" ;
            print STDERR "signal_num: $signal_num\n" ;
            if (($signal_num == 2) || ($signal_num == 125)) {
                if (is_foreground()) {
                    print STDOUT "Do you want to abort all the $str15_title tests ? y|o/n [y] " ;
                    my $answer = <STDIN> ;
                    chomp $answer ;
                    if ($answer eq '' || $answer =~ /o|y/i) {
                        print $REPORT "User break\n\n" ;
                        $global_break = 1 ;
                        $empty = 1 ; # DEBUG, next lines will be ignored
                        # end_report() ;
                        # close $REPORT ;
                        # close $XML_REPORT ;
                        # exit 2 ;
                    }
                }
            }
        }
        else {
            $has_timeouts_cmd = 1 ;

            my @lines = read_goodlines($timeout_compil_fname) ;
            foreach my $line (@lines) {
                my (@items) = ($line =~ /(^[^;\"\s]+)\s*;\s*(\d+)\s*$/gs) ;
                if ($#items == 1) {
                    if (grep(/^$items[0]$/, @targets)) {
                        $timeouts_compil{$items[0]} = $items[1] ;
                        # DEBUG print STDOUT "Timeout : $items[0] ; $items[1]", "\n" ;
                    }
                }
                else {
                    print STDERR "Next line not recognized in ${timeout_compil_fname}:\n" ;
                    print STDERR $line, "\n\n" ;
                }
            }
        }
    }
} # end unless ($empty)

# --------------------------------------------------------
# We loop the test, first in functional mode without Xicode option
# then in performance mode with Xicode options.

# Reference are already built :
# gcc -DDEBUG -D_MSC_VER=900 -o C.exe -g src/prototype.c
#


@test_modes = () ;
push(@test_modes, 'functional')  if ($func_mode) ;
push(@test_modes, 'performance') if ($perf_mode) ;
pop(@test_modes) if (($empty or ($level eq 'compile')) and ($#test_modes == 1)) ;

# ----------------- TEST LOOP WITH THE TWO TEST MODES ------------------------
MODE:
foreach my $iter_test_mode (@test_modes) {

    if ($iter_test_mode eq 'functional') {
        $iter_func_mode = 1 ;
        $iter_perf_mode = not($iter_func_mode) ;
        @iter_options = @options ;
#unit_tests        @iter_options = (@options, '-DDEBUG') ;
    }
    else {
        $iter_perf_mode = 1 ;
        $iter_func_mode = not($iter_perf_mode) ;
        @iter_options = @options ;
    }
    my $CFLAGS = join(' ', @iter_options) ;

    # We test if we can generate the report in this mode iteration :
    # We can if we are in a functional+performance mode at the performance stage
    # or if there is only one test mode
    # or if we test in compile only level
    #
    $ok_to_report = (($test_mode ne 'functional+performance') or $iter_perf_mode or ($level eq 'compile') or $empty) ;

    TARGET:
    foreach my $target_i (0 .. $#targets) {
        my $target = $targets[$target_i] ;
    # --------------------------- WE BUILD THE EXECUTABLE FILE ------------------------------

        my $exe_fname  = $exe_fnames{$target} ;
        my $exe_name = $exe_fname ;
        $exe_name =~ s/[^\/]*\///g ;
        my $dasm_exe_fname  = $dasm_exe_fnames{$target} ;
        my $dasm_exe_name = $exe_fname ;
        $dasm_exe_name =~ s/[^\/]*\///g ;

        $descr = $target ;

        $dasm_target = $target ;
        $dasm_target =~ s/$/(DASM=$dasm_mode)/ ;
        $dasm_descr = $dasm_target ;

        # For errors occurring in the compilation in the first stage
        if ($ok_to_report) {
            if (exists(${@pass_status{$target}}[0]) and (ref(${@pass_status{$target}}[0]) eq "ARRAY")
                                               and defined(${${@pass_status{$target}}[0]}[0])) {

                my $SIZE = my $CYC = my $norm_res = '' ;

                if (${${@pass_status{$target}}[0]}[0] =~ 'FAIL') {
                    $num_fail++ ;
                    $SIZE = '(fail)' ;
                    $norm_res = '' ;
                    $CYC = '(not executed)' ;

                    line_report($REPORT, $target,
                                $descr,
                                '',                                                     # the $in_file,
                                ${${@pass_status{$target}}[0]}[0] . ${${@pass_info{$target}}[0]}[0],
                                $SIZE,
                                $CYC,
                                $norm_res,
                                undef, undef,
                                ${${@err_msg{$target}}[0]}[0]
                                ) ;
                    if ($dasm_mode) {
                          line_report($REPORT, $target,
                                      $dasm_descr,
                                      '',                                                     # the $in_file,
                                      ${${@pass_status{$target}}[1]}[0] . ${${@pass_info{$target}}[1]}[0],
                                      $SIZE,
                                      $CYC,
                                      $norm_res,
                                      undef, undef,
                                      ${${@err_msg{$target}}[1]}[0]
                                      ) ;
                    }
                    next TARGET ;
                }
            }
        }

        unless ($empty) {
            # Cleaning
            if ($no_pre_clean) {
                print STDOUT "\nNo pre cleaning.\n" ;
            }
            else {

                print STDOUT "rm -f $exe_fname\n\n" ;
                unlink "$exe_fname" ;

                # Case of targets that are .eln that must be cleared for the $SIZE computation
                if ($eln_targets) {
                    print STDOUT "rm -f ${obj_dir}/*.${obj_ext}\n\n" ;
                    unlink <$obj_dir/*.${obj_ext}> ;
                }
                my @ARGS = ('gmake', '-f', $makefile, @make_options, 'light_clean', '-r', "CFLAGS=$CFLAGS") ;

                print STDOUT join(' ', quotes_surround(@ARGS)), "\n\n" ;
                unless (system(@ARGS) == 0) {
                    $exit_value = $? >> 8 ;
                    $signal_num = $? & 127 ;
                    print STDERR "\nERROR, ", join(' ', quotes_surround(@ARGS)), " failed: $?\n" ;
                    print STDERR "exit_value: $exit_value\n" ;
                    print STDERR "signal_num: $signal_num\n" ;
                    if (($signal_num == 2) || ($signal_num == 125)) {
                        if (is_foreground()) {
                            print STDOUT "Do you want to abort all the $str15_title tests ? y|o/n [y] " ;
                            my $answer = <STDIN> ;
                            chomp $answer ;
                            if ($answer eq '' || $answer =~ /o|y/i) {
                                line_report($REPORT, $target, $descr, '', 'FAIL(break)', '(fail)', '(not executed)', undef, undef) ;
                                line_report($REPORT, $target, $dasm_descr, '', 'FAIL(break)', '(fail)', '(not executed)', undef, undef) if ($dasm_mode) ;
                                $global_break = 1 ;
                                $empty = 1 ; # DEBUG, next lines will be ignored
                                # end_report() ;
                                # close $REPORT ;
                                # close $XML_REPORT ;
                                # exit 2 ;
                            }
                        }
                        else {
                                ${${@pass_status{$target}}[0]}[0] = 'FAIL' ;
                                ${${@pass_info{$target}}[0]}[0]   = '(break)';
                                ${${@err_msg{$target}}[0]}[0]     = '(not executed)' ;

                                ${${@pass_status{$target}}[1]}[0] = 'FAIL' ;
                                ${${@pass_info{$target}}[1]}[0]   = '(break)';
                                ${${@err_msg{$target}}[1]}[0]     = '(not executed)' ;

                                line_report($REPORT_FP, $target, $descr, '', 'FAIL(break)', '(fail)', '(not executed)', undef, undef) ;
                                line_report($REPORT_FP, $target, $dasm_descr, '', 'FAIL(break)', '(fail)', '(not executed)', undef, undef) if ($dasm_mode) ;
                                $global_break = 1 ;
                                $empty = 1 ; # DEBUG, next lines will be ignored
                                # next TARGET ;
                        }
                    }
                }
            } # end if ($no_clean)

            # Compilation
            if ($iter_perf_mode) {
                if ($CFLAGS eq "") {
                    @ARGS = ('-f', "$makefile", @make_options, "$target", '-r', "CFLAGS=-D_QA_PERF_") ;
                }
                else {
                    @ARGS = ('-f', "$makefile", @make_options, "$target", '-r', "CFLAGS=-D_QA_PERF_ $CFLAGS") ;
                }
            } # end if ($iter_perf_mode)
            if ($iter_func_mode) {
                if ($CFLAGS eq '') {
                    @ARGS = ('-f', $makefile, @make_options, $target, '-r') ;
                }
                else {
                    @ARGS = ('-f', $makefile, @make_options, $target, '-r', "CFLAGS=$CFLAGS") ;
                }
            } # end if ($iter_func_mode)

            my $make_argv = join(' ', quotes_surround(@ARGS)) ;
            unshift(@ARGS, 'gmake') ;

            if (exists($timeouts_compil{$target})) {
                unshift(@ARGS, './timeout', $timeouts_compil{$target}) ;
            }
            if ($ok_to_report) {
                pxml_begin_tag      ($XML_REPORT, 'Compilation') ;
                pxml_atomic_element ($XML_REPORT, 'target', ${target}) ;
                pxml_atomic_element ($XML_REPORT, 'CFLAGS', ${CFLAGS}) ;
                pxml_atomic_element ($XML_REPORT, 'make_argv', ${make_argv}) ;
                pxml_atomic_element ($XML_REPORT, 'start_date', xml_formatted_date()) ;
            }
            print STDOUT join(' ', quotes_surround(@ARGS)), "\n\n" ;
            if ( $purify_test ) {
                print $PURIFY_REPORT join(' ', quotes_surround(@ARGS)), "\n" ;
                print $PURIFY_TRACE  join(' ', quotes_surround(@ARGS)), "\n" ;
            }
            unless (system(@ARGS) == 0) {
                $exit_value = $? >> 8 ;
                $signal_num = $? & 127 ;

                if ($ok_to_report) {
                    pxml_atomic_element ($XML_REPORT, 'end_date', xml_formatted_date()) ;
                    pxml_end_tag        ($XML_REPORT, 'Compilation') ;
                }

                print STDERR "\nERROR, ", join(' ', quotes_surround(@ARGS)), " failed: $?\n" ;
                print STDERR "exit_value: $exit_value\n" ;
                print STDERR "signal_num: $signal_num\n" ;
                if (($signal_num == 2) or ($signal_num == 125)) {
                    if (is_foreground()) {
                        print STDOUT "Do you want to abort all the $str15_title tests ? y|o/n [y] " ;
                        my $answer = <STDIN> ;
                        chomp $answer ;
                        if ($answer eq '' || $answer =~ /o|y/i) {
                            line_report($REPORT, $target, $descr, '', 'FAIL(break)', '(fail)', '(not executed)', undef, undef) ;
                            line_report($REPORT, $target, $dasm_descr, '', 'FAIL(break)', '(fail)', '(not executed)', undef, undef) if ($dasm_mode) ;
                            $global_break = 1 ;
                            $empty = 1 ; # DEBUG, next lines will be ignored
                            # end_report() ;
                            # close $REPORT ;
                            # close $XML_REPORT ;
                            # exit 2 ;
                        }
                    }
                    else {
                            ${${@pass_status{$target}}[0]}[0] = 'FAIL' ;
                            ${${@pass_info{$target}}[0]}[0]   = '(break)';
                            ${${@err_msg{$target}}[0]}[0]     = '(not executed)' ;

                            ${${@pass_status{$target}}[1]}[0] = 'FAIL' ;
                            ${${@pass_info{$target}}[1]}[0]   = '(break)';
                            ${${@err_msg{$target}}[1]}[0]     = '(not executed)' ;

                            line_report($REPORT_FP, $target, $descr, '', 'FAIL(break)', '(fail)', '(not executed)', undef, undef) ;
                            line_report($REPORT_FP, $target, $dasm_descr, '', 'FAIL(break)', '(fail)', '(not executed)', undef, undef) if ($dasm_mode) ;
                            $empty = 1 ; # DEBUG, next lines will be ignored
                            # next TARGET ;
                    }
                }
                elsif ((exists($timeouts_compil{$target})) and (($exit_value == 30) or ($exit_value == 124)) and ($signal_num == 0)) {
                    if ($ok_to_report) {
                        $num_fail++ ;
                        line_report($REPORT, $target, $descr, '', 'FAIL(make timeout)', '(fail)', '(not executed)', undef, undef) ;
                    }
                    else {
                        ${${@pass_status{$target}}[0]}[0] = 'FAIL' ;
                        ${${@pass_info{$target}}[0]}[0]   = '(make timeout)';
                        ${${@err_msg{$target}}[0]}[0]     = '' ;

                        line_report($REPORT_FP, $target, $descr, '', 'FAIL(make timeout)', '(fail)', '(not executed)', undef, undef) ;
                    }
                    next TARGET ;
                }
                else {
                    # The makefile has generated an error. test of the executable.
                    #
                    if ( ! -f "$exe_fname") {
                        if ($ok_to_report) {
                            $num_fail++ ;
                            line_report($REPORT, $target, $descr, '', 'FAIL(make error)', '(fail)', '(not executed)', undef, undef) ;
                        }
                        else {
                            ${${@pass_status{$target}}[0]}[0] = 'FAIL' ;
                            ${${@pass_info{$target}}[0]}[0]   = '(make error)';
                            ${${@err_msg{$target}}[0]}[0]     = '' ;

                            line_report($REPORT_FP, $target, $descr, '', 'FAIL(make error)', '(fail)', '(not executed)', undef, undef) ;
                        }
                    }
                    else {
                        if ($ok_to_report) {
                            $num_fail++ ;
                            line_report($REPORT, $target, $descr, '', 'PASS(compil only)', '(fail)', '(not executed)', undef, undef) ;
                        }
                        else {
                            ${${@pass_status{$target}}[0]}[0] = 'PASS' ;
                            ${${@pass_info{$target}}[0]}[0]   = '(compil only)';
                            ${${@err_msg{$target}}[0]}[0]     = '' ;

                            line_report($REPORT_FP, $target, $descr, '', 'PASS(compil only)', '(fail)', '(not executed)', undef, undef) ;
                        }
                    }
                    if ($dasm_mode) {
                        if (! -f "$dasm_exe_fname") {
                            if ($ok_to_report) {
                                $num_fail++ ;
                                line_report($REPORT, $target, $dasm_descr, '', 'FAIL(make error)', '(fail)', '(not executed)', undef, undef) ;
                            }
                            else {
                                ${${@pass_status{$target}}[1]}[0] = 'FAIL' ;
                                ${${@pass_info{$target}}[1]}[0]   = '(make error)';
                                ${${@err_msg{$target}}[1]}[0]     = '' ;

                                line_report($REPORT_FP, $target, $dasm_descr, '', 'FAIL(make error)', '(fail)', '(not executed)', undef, undef) ;
                            }
                        }
                        else {
                            if ($ok_to_report) {
                                $num_fail++ ;
                                line_report($REPORT, $target, $dasm_descr, '', 'PASS(compil only)', '(fail)', '(not executed)', undef, undef) ;
                            }
                            else {
                                ${${@pass_status{$target}}[1]}[0] = 'PASS' ;
                                ${${@pass_info{$target}}[1]}[0]   = '(compil only)';
                                ${${@err_msg{$target}}[1]}[0]     = '' ;

                                line_report($REPORT_FP, $target, $dasm_descr, '', 'PASS(compil only)', '(fail)', '(not executed)', undef, undef) ;
                            }
                        }
                    }
                    next TARGET if ( (! -f "$exe_fname") or (($dasm_mode) and (! -f "$dasm_exe_fname")) ) ;
                }
            } # end unless (system(@ARGS)
            else {
                if ($ok_to_report) {
                    pxml_atomic_element ($XML_REPORT, 'end_date', xml_formatted_date()) ;
                    pxml_end_tag        ($XML_REPORT, 'Compilation') ;
                }
            }


            if ($empty) {
                $SIZE = '' ;
                $DASM_SIZE = '' ;
            }
            else {
                # We test if there is an elf reader
                #
                my @elf_read = () ;
                if ($CC =~ /^gcc$/i) {
                    @elf_read = ('size', '-t') if (which('size')) ;
                }
                elsif (($CC =~ /^scc$/i) || ($CC =~ /^dsp56800$/i) || ($CC =~ /^dsp56800e$/i)) {
                    @elf_read = ('sc100-size') if (which('sc100-size'));
                }
                else {
                    @elf_read = ('size', '-t') if (which('size')) ;
                }

                if (@elf_read && ($CC !~ /^java$/i)) {
                    $SIZE = '(fail)' ;

                    # We find the list of objects filenames and then ELF filenames
                    my @exist_elf_fnames = glob("$obj_dir/*.$obj_ext") ;
                    if ($#exist_elf_fnames < 0) {
                        print STDERR "\nERROR, no .$obj_ext file in $obj_dir.\n\n" ;
                    }
                    else {
                        my $local_dir = cwd() ;
                        chomp $local_dir;
                        foreach my $f (@exist_elf_fnames) {
                            $f =~ s/^$local_dir\/*//;
                        }
                        print STDOUT join(' ', @elf_read, @exist_elf_fnames), "\n" ;
                        my @elf_sizes = execute_it(@elf_read, @exist_elf_fnames) ;
                        my @SIZES = ($elf_sizes[$#elf_sizes] =~ /[0-9]+/gs) ;
                        $SIZE = $SIZES[0] ;

                        # We test if are in a functional+performance mode at the performance stage
                        $sum_size += $SIZE if ($ok_to_report) ;
                    } # end if ($#exist_elf_fnames < 0)

                    # if the dasm mode is enabled, also extract the dasm object size
                    #
                    if ($dasm_mode) {
                        $DASM_SIZE = '(fail)' ;

                        # We find the list of objects filenames and then ELF filenames
                        my @exist_elf_fnames = glob("$dasm_dir/*.$obj_ext") ;
                        if ($#exist_elf_fnames < 0) {
                            print STDERR "\nERROR, no .$obj_ext file in $dasm_dir.\n\n" ;
                        }
                        else {
                            print STDOUT join(' ', 'sc100-size', @exist_elf_fnames), "\n" ;
                            my @elf_sizes = execute_it('sc100-size', @exist_elf_fnames) ;
                            my @SIZES = ($elf_sizes[$#elf_sizes] =~ /[0-9]+/gs) ;
                            $DASM_SIZE = $SIZES[0] ;

                            # We test if are in a functional+performance mode at the performance stage
                            $dasm_sum_size += $DASM_SIZE if ($ok_to_report) ;
                        } # end if ($#exist_elf_fnames < 0)
                    }
                }
                else {
                    $SIZE = "($CC)" ;
                }
            } # end unless($empty)
        } # end unless($empty)


        if (( ! -f "$exe_fname") and ! $empty) {
            if ($ok_to_report) {
                $num_fail++ ;
                line_report($REPORT, $target, $descr, '', 'FAIL(no exe)', $SIZE, '(not executed)', undef, undef) ;
            }
            else {
                ${${@pass_status{$target}}[0]}[0] = 'FAIL' ;
                ${${@pass_info{$target}}[0]}[0]   = '(no exe)';
                ${${@err_msg{$target}}[0]}[0]     = '' ;

                line_report($REPORT_FP, $target, $descr, '', 'FAIL(no exe)', $SIZE, '(not executed)', undef, undef) ;
            }
        }
        elsif (($level eq 'compile') or ($exe_name =~ /\.${obj_ext}$/)) {
            # We test if are in a functional+performance mode at the performance stage
            if ($ok_to_report) {
                line_report($REPORT, $target, $descr, '', 'PASS(compil only)', $SIZE, '(not executed)', undef, undef) ;
            }
            else {
                ${${@pass_status{$target}}[0]}[0] = 'PASS' ;
                ${${@pass_info{$target}}[0]}[0]   = '(compil only)';
                ${${@err_msg{$target}}[0]}[0]     = '' ;

                line_report($REPORT_FP, $target, $descr, '', 'PASS(compil only)', $SIZE, '(not executed)', undef, undef) ;
            }
        } # end if (( ! -f "$exe_fname") and ! $empty)

        if ($dasm_mode) {
            if ((! -f "$dasm_exe_fname") and ! $empty)  {
                if ($ok_to_report) {
                    $num_fail++ ;
                    line_report($REPORT, $target, $dasm_descr, '', 'FAIL(no exe)', $DASM_SIZE, '(not executed)', undef, undef) ;
                }
                else {
                    ${${@pass_status{$target}}[1]}[0] = 'FAIL' ;
                    ${${@pass_info{$target}}[1]}[0]   = '(no exe)';
                    ${${@err_msg{$target}}[1]}[0]     = '' ;

                    line_report($REPORT_FP, $target, $dasm_descr, '', 'FAIL(no exe)', $DASM_SIZE, '(not executed)', undef, undef) ;
                }
            }
            elsif (($level eq 'compile') or ($dasm_exe_name =~ /\.${obj_ext}$/)) {
                # We test if are in a functional+performance mode at the performance stage
                if ($ok_to_report) {
                    line_report($REPORT, $target, $dasm_descr, '', 'PASS(compil only)', $DASM_SIZE, '(not executed)', undef, undef) ;
                }
                else {
                    ${${@pass_status{$target}}[1]}[0] = 'PASS' ;
                    ${${@pass_info{$target}}[1]}[0]   = '(compil only)';
                    ${${@err_msg{$target}}[1]}[0]     = '' ;

                    line_report($REPORT_FP, $target, $dasm_descr, '', 'PASS(compil only)', $DASM_SIZE, '(not executed)', undef, undef) ;
                }
            }
        }
        next TARGET if ( (! -f "$exe_fname" and not $empty) or ($level eq 'compile') or ($exe_name =~ /\.${obj_ext}$/) ) ;
        next TARGET if ( ($dasm_mode)
                        and ((! -f "$dasm_exe_fname" and not $empty)
                             or($level eq 'compile')
                             or($dasm_exe_fname =~ /\.${obj_ext}$/)) ) ;

        # --------------------------- WE LAUNCH THE EXECUTION OF THE TESTS ----------------------
        TEST_INPUTS:
        foreach my $inp (0 .. $#{$descrs{$target}}) {

            # Execution
            my $descr       = ${$descrs{$target}}[$inp] ;
            my $dasm_descr  = $descr ;
            $dasm_descr  =~ s/$/(DASM=$dasm_mode)/ ;

            my $sim_timeout = ${$timeouts_simul{$target}}[$inp] ;
            my @descr_list  = ( ${$descrs{$target}}[$inp] );
            my $params_str  = ${$params_lists{$target}}[$inp] ;

            my $in_file     = undef ;
            my @out_files   = undef ;
            my @ref_files   = undef ;
            my $in_basename = undef ;
            my $norm_res    = undef ;

            my @params_list = () ;
            unless ($iter_perf_mode) {
                $params_str =~ s/^\s+//;
                $params_str =~ s/\s+$//;
                $params_str =~ s/^\"([^\"]*)\"$/\1/;
                $params_str =~ s/^\'([^\']*)\'$/\1/;
                @params_list = ($params_str =~ /([^ \t\"\']+|\"[^\"]*\"|\'[^\']*\')/gsx) ;
            }

            my $CYC = '(fail)' ;
            # List of lines from stdout
            my @res = () ;
            # List of (frame number, bytes written) doublets
            my @frames_bytes = () ;

            # Simulator and parameters
            my @sim_cmd = () ;
            @sim_cmd = ($simulator, [@sim_options], [@iter_options,@mandatory_opts,@mandatory_CC_opts], $exe_fname, [@params_list]) if ($iter_func_mode) ;
            @sim_cmd = ($simulator, [@sim_options], [@iter_options,@mandatory_opts,@mandatory_CC_opts], $exe_fname, [])             if ($iter_perf_mode) ;

            if ( $dasm_mode ) {
                 @sim_cmd_dasm = ($simulator, [@sim_options], [@iter_options,@mandatory_opts,@mandatory_CC_opts], $dasm_exe_fname, [@params_list]) if ($iter_func_mode) ;
                 @sim_cmd_dasm = ($simulator, [@sim_options], [@iter_options,@mandatory_opts,@mandatory_CC_opts], $dasm_exe_fname, [])             if ($iter_perf_mode) ;

                 @sim_cmd_list = ([@sim_cmd] ,[@sim_cmd_dasm]) ;

                 push (@descr_list, $dasm_descr) ;
            }
            else {
                 @sim_cmd_list = ([@sim_cmd]) ;
            }

            SIMULATION :
            foreach $current_sim_idx ( 0 .. $#descr_list ) {

                $exec_start_date = undef ;
                $exec_end_date = undef ;

                if (not($current_sim_idx)) {
                    $CURRENT_SIZE = $SIZE;
                }
                else {
                    $CURRENT_SIZE = $DASM_SIZE;
                }

                @current_sim_cmd = @{@sim_cmd_list[$current_sim_idx]} ;
                $descr = @descr_list[$current_sim_idx];

                if ($iter_func_mode) {
                    $in_file     = "$input_dir/${$in_files{$target}}[$inp]" ;
                    @out_files   = @{${$out_files{$target}}[$inp]} ;
                    unless ($empty) {
                        foreach my $out_file (@out_files) {
                            if ($out_file =~ /^stdout$/i) {
                            print STDOUT "rm -f '", $captured_stdout_file, "'\n" ;
                            unlink $captured_stdout_file ;
                            }
							elsif ($out_file =~ /^stderr$/i) {
								print STDOUT "rm -f '", $captured_stderr_file, "'\n" ;
								unlink $captured_stderr_file ;
							}
                            else {
                                print STDOUT "rm -f '$output_dir/${out_file}'\n" ;
                                unlink "$output_dir/$out_file" ;
                            }
                        }
                        print STDOUT "\n" if (@out_files) ;
                    }
                    @ref_files   = @{${$ref_files{$target}}[$inp]} ;
                    $in_basename = ${$in_files{$target}}[$inp] ;
                    $in_basename =~ s/[^\/]*\///g ;
                }
                if ($iter_perf_mode) {
                    $in_file     = '' ;
                    @out_files   = () ;
                    @ref_files   = () ;
                    $in_basename = '_QA_PERF_' . $target ;
                }

                if ($empty) {
                    line_report($REPORT, $target,
                                $descr,
                                $in_basename,
                                'PASS',
                                $CURRENT_SIZE,
                                '',
                                [@params_list], undef,
                                '') ;
                    next SIMULATION ;
                }
                else {
					my @printable_cmd = run_sim_cmd(@current_sim_cmd) ;
					if ($sim_timeout > 0) {
						unshift(@printable_cmd, 'timeout', $sim_timeout) ;
					}
					print STDOUT "\n", join(' ', quotes_surround(@printable_cmd)), "\n\n" ;

                    # We launch the compiled target
                    #
                    my $user_break = 0 ;
                    my $sim_error  = 0 ;

                    local $brkhdl = sub {
                        $user_break = 1 ;
                    } ;
                    local $errhdl = sub {
                        $sim_error  = shift if ($simulator !~ /none/i) ;
                    } ;
                    $exec_start_date = xml_formatted_date() ;
                    @res = run_sim_errbrkhdl(\&$errhdl, \&$brkhdl, $sim_timeout, @current_sim_cmd) ;
                    $CYC = $res[0] ;
                    @stdout_lines = @{$res[1]} ;
                    $exec_end_date = xml_formatted_date() ;


                    # DEBUG print STDOUT "\$user_break == $user_break \n" ; # DEBUG
                    # DEBUG print STDOUT "\$sim_error  == $sim_error \n" ;  # DEBUG
                    # DEBUG print STDOUT "\$res[0]     == $res[0] \n" ;     # DEBUG

                    # Frame informations are for codec tests
                    #
                    if ($iter_func_mode) {
                        # We extract the frames traces from the stdout
                        #
                        @frame_byte_list = () ;
                        my @frame_bytes_trc = grep(/^frame\s*=[0-9]+,\s*[0-9]+\s*bytes written/, @stdout_lines) ;
                        @stdout_sim         = grep(!/^frame\s*=[0-9]+,\s*[0-9]+\s*bytes written/, @stdout_lines) ;
                        foreach my $frame_byte (@frame_bytes_trc) {
                            @frame_byte = ( $frame_byte =~ /[0-9]+/g) ;
                            if ($#frame_byte == 1) {
                                push (@frame_byte_list, [$frame_byte[0], $frame_byte[1]]) ;
                                #DEBUG print STDOUT "Frame == $frame_byte[0], $frame_byte[1] bytes written.\n" ;
                            }
                            else {
                                print STDERR "Trace information (frame number and num bytes written) is bad.\n" ;
                            }
                        }
                    }

                    # We test if the simulator returns a speed value
					# We test if the number of cycles is a number or an error message
					unless ($CYC =~ /^[0-9]+(\.[0-9]+)?$/x) {
						# if the number of cycles is an error message
						# we keep only error message in $norm_res
						$norm_res = $CYC ;
						$norm_res =~ s/[0-9]+(\.[0-9]+)?//gx ;
					}
					# We compute the normalized value from cycle number
					elsif ((($test_mode ne 'functional+performance') and $iter_func_mode) or $iter_perf_mode) {
						$sum_cycles += $CYC ;
						$norm_res = '' ;
						if ( -f "$run_norm" ) {
							my @cmd = ($run_norm, $files_infos, $in_basename, $CYC) ;
							print STDOUT "\n", join(' ', @cmd), "\n" ;
							my $status = 0 ;
							my $brk = 0 ;
							my @nres = execute_it_stdout_errbrkhdl(sub {$status = shift}, sub {$brk = 1}, @cmd) ;

							if ($brk) {
								$user_break = 1 ;
							}
							elsif ($status) {
								print STDERR "ERROR: $run_norm returns status $status.\n" ;
							}
							elsif (@nres) {
								$norm_res = $nres[0] ;
							}
						}
					}
                    else {
                        $CYC = $norm_res = $sum_cycles = "($CC)" ;
                    }

                    if ($user_break) {
                        line_report($REPORT, $target, $descr, '(nothing)', 'FAIL(User break)', $CURRENT_SIZE, $CYC, [@params_list], undef, $norm_res) ;

                        if (is_foreground()) {
                            print STDOUT "Do you want to abort all the $str15_title tests ? y|o/n [y] " ;
                            my $answer = <STDIN> ;
                            chomp $answer ;
                            if ($answer eq '' || $answer =~ /o|y/i) {
                                $empty = 1 ; # DEBUG, next lines will be ignored
                                # end_report() ;
                                # close $REPORT ;
                                # close $XML_REPORT ;
                                # exit 2 ;
                            }
                        }
                        else {
                            next SIMULATION ;
                        }
                    }
                    elsif ($sim_error) {
						if (($sim_timeout > 0) and (($exit_value == 30) or ($exit_value == 124)) and ($signal_num == 0)) {
							if ($ok_to_report) {
								$num_fail++ ;
								line_report($REPORT, $target, $descr, '', 'FAIL(exec timeout)', $CURRENT_SIZE, '(not executed)', [@params_list], undef, undef) ;
							}
							else {
								${${@pass_status{$target}}[0]}[0] = 'FAIL' ;
								${${@pass_info{$target}}[0]}[0]   = '(exec timeout)';
								${${@err_msg{$target}}[0]}[0]     = '' ;

								line_report($REPORT_FP, $target, $descr, '', 'FAIL(exec timeout)', $CURRENT_SIZE, '(not executed)', [@params_list], undef, undef) ;
							}
							next TARGET ;
						}
						else {
							if ($ok_to_report) {
								$num_fail++ ;
								line_report($REPORT, $target, $descr,
											$in_file,
											"FAIL(sim status $sim_error)",
											$CURRENT_SIZE,
											$CYC,
											[@params_list], undef,
											$norm_res
											) ;
							}
							else {
								${${@pass_status{$target}}[$current_sim_idx]}[$inp+1] = 'FAIL' ;
								${${@pass_info{$target}}[$current_sim_idx]}[$inp+1]   = "(sim status $sim_error)" ;
								${${@err_msg{$target}}[$current_sim_idx]}[$inp+1]     = '' ;

								line_report($REPORT_FP, $target, $descr, $in_basename, "FAIL(sim status $sim_error)", $CURRENT_SIZE, $CYC, [@params_list], undef, $norm_res) ;
							}
                    	}
                        next SIMULATION ;
                    } # end if $user_break or $sim_error
                } # unless ($empty)

                if ($iter_perf_mode and not $empty) {
                    # Stdout output test is for codec tests
                    # Output comparison
                    #
                    #We search the word pass/fail
                    my @pass_fail = grep(/\b(pass|passed|fail|failed)\b/i, @stdout_lines) ;
                    unless (@pass_fail) {
                        $num_fail++ ;
                        line_report($REPORT, $target, $descr, $in_basename, 'FAIL(no pass/fail)', $CURRENT_SIZE, $CYC, [@params_list], undef, $norm_res) ;
                    }
                    else {
                        my @fails = grep(/\b(fail|failed)\b/i, @pass_fail) ;
                        if (@fails) {

                            my @fails_infos_l = () ;
                            foreach my $fail_line (@fails) {
                                my ($fail_info) = ($fail_line =~ /\bfail[^(]*\(([^)]+)\).*/i) ;
                                push(@fails_infos_l, $fail_info) ;
                            }
                            my $fails_info = join(' ', @fails_infos_l) ;
                            $num_fail++ ;
                            line_report($REPORT, $target, $descr, $in_basename, "FAIL($fails_info)", $CURRENT_SIZE, $CYC, [@params_list], undef, $norm_res) ;
                        }
                        else {

                            if (exists(${@pass_status{$target}}[$current_sim_idx]) and (ref(${@pass_status{$target}}[$current_sim_idx]) eq "ARRAY")
                                                               and defined(${${@pass_status{$target}}[$current_sim_idx]}[$inp+1])) {

                                $num_fail++ if (${${@pass_status{$target}}[$current_sim_idx]}[$inp+1] =~ /FAIL/i) ;

                                # already reported in atomic reports
                                $already_reported = 1 ;

                                # DEBUG print STDOUT "\${\$pass_status{$target}}[$inp+1] == ${$pass_status{$target}}[$inp+1] \n" ;
                                line_report($REPORT, $target,
                                            $descr,
                                            $in_basename,
                                            ${${@pass_status{$target}}[$current_sim_idx]}[$inp+1] . ${${@pass_info{$target}}[$current_sim_idx]}[$inp+1],
                                            $CURRENT_SIZE,
                                            $CYC,
                                            [@params_list], undef,
                                            $norm_res, ${${@err_msg{$target}}[$current_sim_idx]}[$inp+1]
                                            ) ;
                                #   next TARGET ; # Laurent. Warning.
                                next SIMULATION ;
                            }
                            else {
                                line_report($REPORT, $target,
                                            $descr,
                                            $in_basename,
                                            'PASS',
                                            $CURRENT_SIZE,
                                            $CYC,
                                            [@params_list], undef,
                                            $norm_res) ;
                            }
                        }
                    } # end if (@pass_fail)
                } # end if ($iter_perf_mode)

                if ($iter_func_mode and not $empty) {
                    # Outputs comparison
                    #
                    TEST_OUTPUTS:
                    foreach my $i_out (0..$#out_files) {
                        my $out_file = "$output_dir/$out_files[$i_out]" ;
                        my $ref_file = "$ref_dir/$ref_files[$i_out]" ;
                        my @out_lines = ();

                        if ($out_files[$i_out] =~ /^stdout$/i) {
                           open STDOUT_SIM_NOCR, "> stdout_sim_nocr" or die "Can't open the file 'stdout_sim_nocr'." ;
                           binmode STDOUT_SIM_NOCR ;
                           autoflush STDOUT_SIM_NOCR 1 ;
                           foreach (@stdout_lines) {
                               print STDOUT_SIM_NOCR $_, "\n" ;
                           }
                           close(STDOUT_SIM_NOCR)	    	|| die "can't close $file: $!";
                           $out_file = 'stdout_sim_nocr' ;
                           @out_lines = @stdout_lines;
                        }
						elsif ($out_files[$i_out] =~ /^stderr$/i) {
						   @stderr_lines = read_alllines($captured_stderr_file) ;
						   open STDERR_SIM_NOCR, "> stderr_sim_nocr" or die "Can't open the file 'stderr_sim_nocr'." ;
						   binmode STDERR_SIM_NOCR ;
						   autoflush STDERR_SIM_NOCR 1 ;
						   foreach (@stderr_lines) {
							   print STDERR_SIM_NOCR $_, "\n" ;
						   }
						   close(STDERR_SIM_NOCR)	    	|| die "can't close $file: $!";
						   $out_file = 'stderr_sim_nocr' ;
						   @out_lines = @stderr_lines;
						}

                        my @differ = () ;

                        # Is there a reference file ?
                        #
                        unless (-f "$ref_file") {
                            if ($ok_to_report) {
                                $num_fail++ ;
                                line_report($REPORT, $target, $descr, $in_basename, 'FAIL(no ref)', $CURRENT_SIZE, $CYC, [@params_list], undef, $norm_res) ;
                            }
                            else {
                                ${${@pass_status{$target}}[$current_sim_idx]}[$inp+1] = 'FAIL' ;
                                ${${@pass_info{$target}}[$current_sim_idx]}[$inp+1]   = '(no ref)';
                                ${${@err_msg{$target}}[$current_sim_idx]}[$inp+1]     = '' ;

                                line_report($REPORT_FP, $target, $descr, $in_basename, 'FAIL(no ref)', $CURRENT_SIZE, $CYC, [@params_list], undef, $norm_res) ;
                            }
							my $CFLAGS_noblank = opt_to_str($CFLAGS) ;
							my $flat_target = ${target} ;
							$flat_target =~ s,/,.,g ;
							mkdir 'outputs' unless (-d 'outputs') ;
							mkdir "outputs/new_${flat_target}_${version}${CFLAGS_noblank}" unless (-d "outputs/new_${flat_target}_${version}${CFLAGS_noblank}") ;

							print STDERR "\n", "mv $out_file outputs/new_${flat_target}_${version}${CFLAGS_noblank}/$ref_files[$i_out]\n" ;
							rename "$out_file", "outputs/new_${flat_target}_${version}${CFLAGS_noblank}/$ref_files[$i_out]"
								or warn("Fail renaming '$out_file' to 'outputs/new_${flat_target}_${version}${CFLAGS_noblank}/$ref_files[$i_out]'.") ;
                            next SIMULATION ;
                         } # end if ! (-f "$ref_file")

                        # Is there an output file ?
                        #
                        unless (-f "$out_file") {
                            if ($ok_to_report) {
                                $num_fail++ ;
                                line_report($REPORT, $target, $descr, $in_basename, 'FAIL(run: no output)', $CURRENT_SIZE, $CYC, [@params_list], undef, $norm_res) ;
                            }
                            else {
                                ${${@pass_status{$target}}[$current_sim_idx]}[$inp+1] = 'FAIL' ;
                                ${${@pass_info{$target}}[$current_sim_idx]}[$inp+1]   = '(run: no output)';
                                ${${@err_msg{$target}}[$current_sim_idx]}[$inp+1]     = '' ;

                                line_report($REPORT_FP, $target, $descr, $in_basename, 'FAIL(run: no output)', $CURRENT_SIZE, $CYC, [@params_list], undef, $norm_res) ;
                            }
                            print  STDERR "\nERROR, File not found: $out_file\n\n" ;
                            next SIMULATION ;
                        }

                        my @differ = () ;
                        if (($out_file eq 'stdout_sim_nocr') or ($out_file eq 'stderr_sim_nocr')) {
                            print STDOUT "diff $out_file $ref_file\n\n" ;
                            my @reflines = read_alllines($ref_file) ;

                            if ($#out_lines != $#reflines) {
                                @differ = (1) ;
                            }
                            else {
                                OUT_REF_CMP_LOOP:
                            foreach my $i (0 .. $#reflines) {

                            	if ($out_lines[$i] ne $reflines[$i]) {
                                    @differ = (1) ;
                                    print STDERR "< '$out_lines[$i]'\n" ;
                                    print STDERR "> '$reflines[$i]'\n" ;
                                    print STDERR "---------------\n" ;
                                    print STDERR "<" ;
                                    foreach my $j (0 .. length($out_lines[$i])) {
                                    	printf STDERR ' \0%o', ord(substr($out_lines[$i], $j, 1)) ;
                                    }
                                    print STDERR "\n" ;
                                    print STDERR ">" ;
                                    foreach my $j (0 .. length($reflines[$i])) {
                                        printf STDERR ' \0%o', ord(substr($reflines[$i], $j, 1)) ;
                                    }
                                    print STDERR "\n" ;
                                    print STDERR "------------------------------\n" ;
                                    last OUT_REF_CMP_LOOP ;
                                    }
                                }
                            }
                        }
                        else {
                            print STDOUT "cmp $out_file $ref_file\n\n" ;
                            @differ = compare($out_file, $ref_file) ;
                        }

                        if (@differ) {
                            my $error_byte = $differ[0] ;
                            # DEBUG print "\nERROR_byte == $error_byte \n" ; # DEBUG

                            my ($frame_num, $byte_num) = (1, 0) ;
                            if (@frame_byte_list) {
                                ($frame_num, $byte_num) = @{$frame_byte_list[0]} ;
                                shift @frame_byte_list ;
                            }

                            SEARCH_FRAME:
                            while (@frame_byte_list) {
                                # DEBUG print STDOUT "Frame == $frame_num, $byte_num bytes test.\n" ; # DEBUG
                                my ($next_frame_num, $next_byte_num) = @{$frame_byte_list[0]} ;

                                if (( $error_byte <= $next_byte_num ) or ($frame_num > $next_frame_num)) {

                                    # We skip the traces for the first output file for the next output file
                                    SEARCH_LAST_FRAME:
                                    while (@frame_byte_list) {
                                        if (${$frame_byte_list[0]}[0] == 1) {
                                            last SEARCH_LAST_FRAME ;
                                        }
                                        shift @frame_byte_list ;
                                    }
                                   last SEARCH_FRAME ;
                                }
                                ($frame_num, $byte_num) = ($next_frame_num, $next_byte_num) ;
                                shift @frame_byte_list ;
                            }
                            if ($ok_to_report) {
                                $num_fail++ ;
                                line_report($REPORT, $target, $descr, $in_basename, 'FAIL(Diff)', $CURRENT_SIZE, $CYC, [@params_list], undef, $norm_res, "Error file $out_file byte $error_byte frame $frame_num") ;
                #unit_tests            line_report($REPORT, $target, $descr, $in_basename, 'FAIL(Diff)', $CURRENT_SIZE, $CYC, [@params_list], undef, $norm_res) ;
                            }
                            else {
                                ${${@pass_status{$target}}[$current_sim_idx]}[$inp+1] = 'FAIL' ;
                                ${${@pass_info{$target}}[$current_sim_idx]}[$inp+1]   = '(Diff)';
                                ${$err_msg{$target}}[$inp+1]     = "Error file $out_file byte $error_byte frame $frame_num" ;
                #unit_tests                ${${@err_msg{$target}}[$current_sim_idx]}[$inp+1]     = '' ;

                                line_report($REPORT_FP, $target, $descr, $in_basename, 'FAIL(Diff)', $CURRENT_SIZE, $CYC, [@params_list], undef, $norm_res, "Error file $out_file byte $error_byte frame $frame_num") ;
                #unit_tests                line_report($REPORT_FP, $target, $descr, $in_basename, 'FAIL(Diff)', $CURRENT_SIZE, $CYC, [@params_list], undef, $norm_res) ;
                            }

                            my $CFLAGS_noblank = opt_to_str($CFLAGS) ;
                            mkdir 'outputs' unless (-d 'outputs') ;

                            if ($out_file =~ /stdout_sim/) {
                                print STDERR "\n", "mv $out_file outputs/${out_file}_err_${target}_${version}${CFLAGS_noblank}\n" ;
                                rename "$out_file", "outputs/${out_file}_err_${target}_${version}${CFLAGS_noblank}" ;
                            }
                            else {
                                print STDERR "\n", "mv $out_file ${out_file}_err_${target}_${version}${CFLAGS_noblank}\n" ;
                                rename "$out_file", "${out_file}_err_${target}_${version}${CFLAGS_noblank}" ;
                            }
                            next SIMULATION ;
                        } # end if (@differ)

                        else {
                            # DEBUG print STDOUT "We skip traces for the '$out_file' output file.\n" ; # DEBUG
                            # We skip the traces for the first output file for the next output file
                            if (@frame_byte_list) {
                                shift @frame_byte_list ;
                            }
                            SKIP_FRAMES_THIS_INPUT:
                            while (@frame_byte_list) {
                                if (${$frame_byte_list[0]}[0] == 1) {
                                    last SKIP_FRAMES_THIS_INPUT ;
                                }
                                shift @frame_byte_list ;
                            }
                            unless ($no_clean) {
                                print STDOUT "rm -f '$out_file'\n" ;
                                unlink "$out_file" ;
                            }
                        } # end if $no_diff
                    } # end TEST_OUTPUTS: foreach $i_out (0..$#out_files)

                    if ($ok_to_report) {
                        line_report($REPORT, $target, $descr, $in_basename, 'PASS', $CURRENT_SIZE, $CYC, [@params_list], undef, $norm_res) ;
                    }
                    else {
                        ${${@pass_status{$target}}[$current_sim_idx]}[$inp+1] = 'PASS' ;
                        ${${@pass_info{$target}}[$current_sim_idx]}[$inp+1]   = '' ;
                        ${${@err_msg{$target}}[$current_sim_idx]}[$inp+1]     = '' ;

                        line_report($REPORT_FP, $target, $descr, $in_basename, 'PASS', $CURRENT_SIZE, $CYC, [@params_list], undef, $norm_res) ;
                    }
                } # end if ($iter_func_mode and not $empty)
            } # end SIMULATION: foreach $current_sim_idx ( 0 .. $#descr_list )
        } # end TEST_INPUTS: foreach $inp (0 .. $#{$in_files{$target}})
    } # end foreach $target (@targets)

    # ------------- END TEST LOOP WITH THE TWO TEST MODES ------------------------
} # end foreach my $iter_test_mode (@test_modes)

# --------------------------- END -------------------------------------------------------

end_report() ;
unless ($empty) {
    print  $REPORT "**************************************************************\n\n" ;
    close  $REPORT ;

    if ($test_mode eq 'functional+performance') {
        close $REPORT_FP ;
        unlink "$report_name_func_pass" ;
    }

    # Cleaning
    unless ($no_clean or grep(/^--keep$/i, @options)) {

        my @ARGS = ('gmake', '-f', $makefile, @make_options, 'clean', '-r', "CFLAGS=$CFLAGS") ;

        print STDOUT join(' ', quotes_surround(@ARGS)), "\n\n" ;
        unless (system(@ARGS) == 0) {
            $exit_value = $? >> 8 ;
            $signal_num = $? & 127 ;
            print STDERR "\nERROR, ", join(' ', quotes_surround(@ARGS)), " failed: $?\n" ;
            print STDERR "exit_value: $exit_value\n" ;
            print STDERR "signal_num: $signal_num\n" ;
            if (($signal_num == 2) || ($signal_num == 125)) {
                exit 2 ;
            }
        }
    }
    else {
        print STDOUT "\nNo cleaning.\n" ;
    }
    unlink 'timeout' ;
} # end unless ($empty)

close  $XML_REPORT ;

exit 0 ;

