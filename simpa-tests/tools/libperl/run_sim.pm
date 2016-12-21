#!/usr/bin/env perl

# version:              1.7
# date of creation:     05/07/2002
# date of modification: 07/03/2005
# author:               Guerte Yves
# usage:                use lib "$ENV{'QA_TOOLS'}/libperl" ; use run_sim

# This library allows to run different simulator on compiled code

use POSIX ;
use FileHandle ;
use IO::Handle ;
use Carp;
use English ;

if (exists($ENV{'NEW_QA_ROOT'}) and exists($ENV{'QA_TOOLS'})) {

    use lib "$ENV{'QA_TOOLS'}/libperl" ;
    use tools ;
}
else {
        print STDERR "Variables NEW_QA_ROOT and QA_TOOLS must be set !\n" ;
    exit 1
}

autoflush STDOUT 1 ;
autoflush STDERR 1 ;

our $captured_stdout_file = 'stdout_sim' ;
our $captured_stderr_file = 'stderr_sim' ;


# ---------------------------------------------------------------------------------------
# PARAMETERS

$PC = (sys_kind() eq 'PC') ;

# Available simulators :
#
if ($PC) {
    @sim_available = ('runsc1000', 'runsc100', 'sc100-sim', 'none', 'runccs', 'sim-ame', 'ISS', 'axd', 'mwrunsim56800e', 'mwrunsim56800', 'armsd', 'java') ;
    # Starcore simulators
    %starcore_sim  = ('runsc1000' => 1, 'runsc100' => 1, 'sc100-sim' => 1, 'runccs' => 1) ;
    # Simulators that return a number of cycles
    %compute_cyc   = ('runsc1000' => 1, 'runsc100' => 1, 'sc100-sim' => 1, 'runccs' => 1, 'sim-ame' => 1, 'ISS' => 1, 'axd' => 1, 'mwrunsim56800e' => 1, 'mwrunsim56800' => 1) ;
}
else {
    @sim_available = ('runsc1000', 'runsc100', 'sc100-sim', 'none', 'sim-ame', 'ISS', 'axd', 'runtcl', 'runbf', 'java') ;
    # Starcore simulators
    %starcore_sim  = ('runsc1000' => 1, 'runsc100' => 1, 'sc100-sim' => 1, 'runtcl' => 1, 'runbf' => 1) ;
    # Simulators that return a number of cycles
    %compute_cyc   = ('runsc1000' => 1, 'runsc100' => 1, 'sc100-sim' => 1, 'sim-ame' => 1, 'ISS' => 1, 'axd' => 1) ;
}
$default_simulator = 'sc100-sim' unless (defined($default_simulator));

# ---------------------------------------------------------------------------------------
# function that returns TRUE if the simulator is for the StarCore
#
sub is_sc_sim {
    my $sim = shift ;
    return exists($starcore_sim{$sim}) ;
}

# ---------------------------------------------------------------------------------------
# function that returns TRUE if run_sim is able to return an execution cycle number
#
sub compute_cyc {
    my $sim = shift ;
    return exists($compute_cyc{$sim}) ;
}

# ---------------------------------------------------------------------------------------
# function that returns the simulation command that must be launched
#
# use:    @cmd = run_sim_cmd($simulator, [@sim_options], [@comp_options], $exe_fname, [@params_list]) ;

sub run_sim_cmd {

    my $sim = $_[0] ;
    my @sim_options = @{$_[1]} ;
    my @comp_options = @{$_[2]} ;
    my $sim_exe = $_[3] ;
    my @sim_exe_params = @{@_[4..$#_]} ;

    foreach my $i (0 .. $#sim_options) {
        my @params_list = ($sim_options[$i] =~ /([^ \t\"\']+|\"[^\"]*\"|\'[^\']*\')/gsx) ;
        splice(@sim_options, $i, 1, @params_list) ;
    }

	# (double) quotes surrounding parameters are necessary only for shell to aggregate one parameter
    foreach my $param (@sim_exe_params) {
		$param = no_quote_surr($param) ;
    }

    #DEBUG print STDOUT "\$sim ==            $sim \n" ;
    #DEBUG print STDOUT "\@sim_options ==    ", join(', ', @sim_options), "\n" ;
    #DEBUG print STDOUT "\@comp_options ==   ", join(', ', @comp_options), "\n" ;
    #DEBUG print STDOUT "\$sim_exe ==        $sim_exe \n" ;
    #DEBUG print STDOUT "\@sim_exe_params == ", join(', ', @sim_exe_params), "\n" ;

    # result
    my @cmd = () ;

    SWITCH_SIM: {
        # -------------------------------------------------
        if ($sim eq 'runsc1000') {
            if (grep(/^-be$/, @comp_options)) {
                @cmd = ('runsc1000', '-e', '-t', @sim_options, $sim_exe, @sim_exe_params) ;
            }
            else {
                @cmd = ('runsc1000', '-t', @sim_options, $sim_exe, @sim_exe_params) ;
            }
            last SWITCH_SIM ;
        } # end if ($sim eq 'runsc1000')

        # -------------------------------------------------
        if ($sim eq 'runsc100') {
            if (grep(/^-be$/, @comp_options)) {
                @cmd = ('runsc100', '-f', '-e', '-t', @sim_options, $sim_exe, @sim_exe_params) ;
            }
            else {
                @cmd = ('runsc100', '-f', '-t', @sim_options, $sim_exe, @sim_exe_params) ;
            }
            last SWITCH_SIM ;
        } # end if ($sim eq 'runsc100')

        # -------------------------------------------------
        if ($sim eq 'sc100-sim') {
            @cmd = ('sc100-sim', '-quiet', '-o', $captured_stdout_file, '--', @sim_options,
                                 '-statse', '-exec', "$sim_exe", @sim_exe_params) ;

            last SWITCH_SIM ;
        } # end if ($sim eq 'sc100-sim')

        # -------------------------------------------------
        if ($sim eq 'runtcl') {
            @cmd = ('runtcl', @sim_options, $sim_exe, @sim_exe_params);

            last SWITCH_SIM ;
        } # endif ($sim eq 'runtcl')

        # -------------------------------------------------
        if ($sim eq 'runbf') {
            @cmd = ('runbf', @sim_options, $sim_exe, @sim_exe_params);

            last SWITCH_SIM;
        } # endif ($sim eq 'runbf')

        # -------------------------------------------------
        if ($sim eq 'runccs') {

            foreach my $p (@sim_exe_params) {
                if (grep(/\//, $p)) {
                    if (grep(/^\.\.\//, $p)) {

                        my $previous = `cygpath -w ".."` ;
                        chomp $previous ;

                        $p = `cygpath -w "$p"` ;
                        chomp $p ;

                        $previous = quotemeta($previous) ;
                        $p =~ s/^${previous}\\*/..\\/ ;
                    }
                    else {
                        $p = `cygpath -w "$p"` ;
                        chomp $p ;
                    }
                }

            }
            @cmd = ('runccs', '-o', $captured_stdout_file, '-e', $captured_stderr_file, @sim_options, '--', $sim_exe, @sim_exe_params) ;

            last SWITCH_SIM ;
        } # end if ($sim eq 'sc100-sim')

        # -------------------------------------------------
        if ($sim eq 'none') {
            @cmd = ($sim_exe, @sim_options, @sim_exe_params) ;
            last SWITCH_SIM ;
        } # end if ($sim eq 'none')

        # -------------------------------------------------
        if ($sim eq 'java') {
            # we remove bin/ because in run_sim_errbrkhdl() we do a chdir('bin')
            if ($sim_exe =~ /bin\/(.*)$/) {
            	$sim_exe = $LAST_PAREN_MATCH ;
            }
            if ($sim_exe =~ /(.*)\.class$/) {
            	$sim_exe = $LAST_PAREN_MATCH ;
            }

        	@cmd = ('java', $sim_exe, @sim_options, @sim_exe_params) ;
            last SWITCH_SIM ;
        } # end if ($sim eq 'java')

        # -------------------------------------------------
        if ($sim eq 'sim-ame') {

            print STDERR "\nERROR, AME variable not defined.\n\n" unless (exists($ENV{'AME'})) ;

            my @sim_ame_exe_params = () ;
            foreach my $p (@sim_exe_params) {
                push (@sim_ame_exe_params, '--args', $p) ;
            }

            unless (@sim_options) {
                @cmd = ('sim-ame', "$ENV{'AME'}/config/zen", "$sim_exe", @sim_ame_exe_params) ;
            }
            else {
                @cmd = ('sim-ame', @sim_options, "$sim_exe", @sim_ame_exe_params) ;
            }
            last SWITCH_SIM ;
        } # end if ($sim eq 'sim-ame')
        # -------------------------------------------------
        if ($sim eq 'ISS') {

            print STDERR "\nERROR, ISS_BIN_PATH variable not defined.\n\n" unless (exists($ENV{'ISS_BIN_PATH'})) ;

            my @args = ('iss_mk_startup.csh',
                        '../inputs/empty.txt',
                        $captured_stdout_file,
                        $captured_stderr_file,
                        $sim_exe,
                        @sim_ame_exe_params
                        ) ;

            print STDOUT join(' ', @args), "\n" ;

            my @tmpres = execute_it_stdout(@args) ;

            unless (@sim_options) {
                @cmd = ('ISS', '-nt', '-nw', '-f', 'srec_startup.tcl') ;
            }
            else {
                @cmd = ('ISS', @sim_options, '-nt', '-nw', '-f', 'srec_startup.tcl') ;
            }
            last SWITCH_SIM ;
        } # end if ($sim eq 'ISS')
        # -------------------------------------------------
        if ($sim eq 'axd') {
            warn("The ARMCONF variable must be defined.") unless (exists($ENV{'ARMCONF'})) ;

            my @p_sim_options = () ;
            foreach my $opt (@sim_options) {
                push(@p_sim_options, '-s', $opt) ;
            }
            @cmd = ('run_axd_sim.pl' , '-o', $captured_stdout_file, '-l', 'tmp_axd.log', @p_sim_options, '--', $sim_exe, @sim_exe_params) ;

            last SWITCH_SIM ;
        } # end if ($sim eq 'axd')
        # -------------------------------------------------
        if ($sim eq 'mwrunsim56800e') {
            @cmd = ('mwrunsim56800e', '-verbose', $sim_exe, @sim_options, @sim_exe_params);
            last SWITCH_SIM ;
        } # end if ($sim eq 'mwrunsim56800e')
        # -------------------------------------------------
        if ($sim eq 'mwrunsim56800') {
        	@cmd = ('mwrunsim56800', '-verbose', $sim_exe, @sim_options, @sim_exe_params);
        	last SWITCH_SIM ;
        } # end if ($sim eq 'mwrunsim56800')
        # -------------------------------------------------
        if ($sim eq 'armsd') {
            my $TOP_LEVEL = $ENV{'NEW_QA_ROOT'}.'/mwth/mw_test/Cross_Products/Compiler/mw_test_harness' ;
            $TOP_LEVEL = $ENV{'TOP_LEVEL'} if (exists($ENV{'TOP_LEVEL'})) ;
            @cmd = ("$TOP_LEVEL/product_utils/arm/mw_execute_armsd.pl", @sim_options, $sim_exe, @sim_exe_params);
            last SWITCH_SIM ;
        } # end if ($sim eq 'armsd')

        # -------------------------------------------------
        print STDERR "Simulator '$sim' not recognized." ;

    } # end SWITCH_SIM

    return @cmd ;

}
# ---------------------------------------------------------------------------------------
# function that executes a simulator command
# and returns the number of cycles used for a StarCore simulation
# and the trace output lines
#
# It needs an error and break handler(status as parameter) functions
#
# use:    @res = run_sim_errbrkhdl(\&errhdl, \&brkhdl, $sim_timeout, $simulator, [@sim_options], [@comp_options], $exe_fname, [@params_list]) ;
#         $CYC     = $res[0] ;
#         @std_out = @{$res[1]}

sub run_sim_errbrkhdl {

    # inputs
    my $errhdl = shift ;
    unless ($errhdl && ref($errhdl) eq 'CODE') {
        confess "usage: run_sim_errbrkhdl(CODEREF, CODEREF, sim_timeout, ...)" ;
    }
    my $brkhdl = shift ;
    unless ($brkhdl && ref($brkhdl) eq 'CODE') {
        confess "usage: run_sim_errbrkhdl(CODEREF, CODEREF, sim_timeout, ...)" ;
    }
    my $sim_timeout = shift;

    my $sim = $_[0] ;
    my @comp_options = @{$_[2]} ;
    my $sim_exe = $_[3] ;
    my @cmd = run_sim_cmd(@_) ;

    if ($sim_timeout > 0) {
    	unshift(@cmd, 'timeout', $sim_timeout) ;
    }

    # number of cycles got from the exec/simulator
    my $CYC = undef ;

    # stdout of the cmd
    my @res = () ;

    unlink $captured_stdout_file ;
    unlink $captured_stderr_file ;

    SWITCH_SIM: {
        # -------------------------------------------------
        if ($sim eq 'runsc1000') {

            @res = execute_it_errbrkhdl(\&$errhdl, \&$brkhdl, @cmd) ;

            foreach my $i (reverse(0 .. $#res)) {
                if ($res[$i] =~ /total\s*execution\s*time\s*==\s(\d+)\s*instruction\s*cycles\s*$/) {
                    $CYC = $LAST_PAREN_MATCH unless (defined($CYC)) ;
                    if ($PREMATCH eq '') {
                        splice(@res, $i, 1) ;
                    }
                    else {
                        $res[$i] = $PREMATCH ;
                    }
                }
            }

            last SWITCH_SIM ;
        } # end if ($sim eq 'runsc1000')
        # -------------------------------------------------
        if ($sim eq 'runsc100') {

            @res = execute_it_stdout_errbrkhdl(\&$errhdl, \&$brkhdl, @cmd) ;

            foreach my $i (reverse(0 .. $#res)) {
                if ($res[$i] =~ /total\s*execution\s*time\s*==\s(\d+)\s*instruction\s*cycles\s*$/) {
                    $CYC = $LAST_PAREN_MATCH unless (defined($CYC)) ;
                    if ($PREMATCH eq '') {
                        splice(@res, $i, 1) ;
                    }
                    else {
                        $res[$i] = $PREMATCH ;
                    }
                }
            }

            last SWITCH_SIM ;
        } # end if ($sim eq 'runsc100')
        # -------------------------------------------------
        if ($sim eq 'sc100-sim') {
            @res = execute_it_stdout_errbrkhdl(\&$errhdl, \&$brkhdl, @cmd) ;
            @res = grep(/cycles/, @res) ;

            $CYC = $res[$#res] ;
            $CYC =~ s/^\D*(\d+)\D*$/\1/g ;
            if ("$CYC" eq "") {
                $CYC = '(fail)' ;
            }

            if ( -f $captured_stdout_file ) {
                @res = read_alllines($captured_stdout_file) ;
            }
            else {
                print STDERR "No '$captured_stdout_file' file.\n" ;
                @res = () ;
            }

            last SWITCH_SIM ;
        } # end if ($sim eq 'sc100-sim')

        # -------------------------------------------------
        if ($sim eq 'runccs') {
            my $has_fastio = grep(/^-D\s*MDCR_MSC8101ADS_FS$/, @comp_options) ;
            my $fast_stdout = 'screen.txt' if ($has_fastio) ;

            unlink $captured_stderr_file ;
            unlink "$fast_stdout" if ($has_fastio) ;

            @res = execute_it_stdout_errbrkhdl(\&$errhdl, \&$brkhdl, @cmd) ;
            my @res_cyc = grep(/count events\./, @res) ;

            $CYC = $res_cyc[$#res_cyc] ;
            $CYC =~ s/^\D*(\d+)\D*$/\1/g ;
            if ("$CYC" eq "") {
                $CYC = '(fail)' ;
            }

            if ( -f $captured_stdout_file ) {
                @res = read_alllines($captured_stdout_file) ;
            }
            elsif (not $has_fastio)  {
                print STDERR "No '$captured_stdout_file' file.\n" ;
                @res = () ;
            }
            if ($has_fastio) {
                if ( -f $fast_stdout) {
                    push(@res, read_alllines($fast_stdout)) ;
                }
                else {
                    print STDERR "No '$fast_stdout' file.\n" ;
                }
            }
            last SWITCH_SIM ;
        } # end if ($sim eq 'runccs')

        # -------------------------------------------------
        if ($sim eq 'java') {

        	my (undef,undef,$cuser_start_times,undef) = times;
            $CYC = '(not SC)' ;

			$old_classpath = $ENV{CLASSPATH}
				and print STDOUT 'setenv OLD_CLASSPATH $CLASSPATH', "\n" ;
			$ENV{CLASSPATH} = $ENV{PWD} . '/bin:' . $ENV{CLASSPATH}
				and print STDOUT 'setenv CLASSPATH $PWD/bin:$CLASSPATH', "\n" ;

            @res = execute_it_stdout_errbrkhdl(\&$errhdl, \&$brkhdl, @cmd) ;

			$ENV{CLASSPATH} = $old_classpath
				and print STDOUT 'setenv CLASSPATH $OLD_CLASSPATH', "\n" ;

            my (undef,undef,$cuser_end_times,undef) = times ;
            $CYC = $cuser_end_times - $cuser_start_times ;

            # we remove the SIMPA version
            if ($res[0] =~ /^SIMPA\s+\-\s+\d+\/\d+\/\d+$/) {
            	shift @res ;
            }
            SEARCH_DURATION:
            foreach my $i (reverse(0 .. $#res)) {
                if ($res[$i] =~ /^Found an automata which seems to have no counter example in \d+\.*\d*s/) {
                	splice(@res, $i, 1) ;
                	last SEARCH_DURATION ;
                }
            }

            # we remove the date at prefix in STDERR captured lines
            if ( -f $captured_stderr_file ) {
                @err = read_alllines($captured_stderr_file) ;
            }
            open (STDERR_FILE, ">stderr_sim") or die "problem opening stderr_sim\n";
            foreach (@err) {
				s/^\[[0-9:]*\]//s ;
				print STDERR_FILE $_ ;
            }
            close (STDERR_FILE);

            last SWITCH_SIM ;
        } # end if ($sim eq 'java')

        # -------------------------------------------------
        if ($sim eq 'none') {

        	my (undef,undef,$cuser_start_times,undef) = times;

            $CYC = '(not SC)' ;
            #DEBUG print STDOUT "\@cmd == ", join(' ', @cmd), "\n" ;
            @res = execute_it_stdout_errbrkhdl(\&$errhdl, \&$brkhdl, @cmd) ;

            my (undef,undef,$cuser_end_times,undef) = times;
            $CYC = $cuser_end_times - $cuser_start_times;

            last SWITCH_SIM ;
        } # end if ($sim eq 'none')
        # -------------------------------------------------
        if ($sim eq 'sim-ame') {

            @res = execute_it_stdout_errbrkhdl(\&$errhdl, \&$brkhdl, @cmd) ;

            my @res_cyc = grep(/Clock Ticks/, @res) ;
            if (@res_cyc) {
                $CYC = $res_cyc[$#res_cyc] ;
                $CYC =~ s/^[^;]*;[^;]*;\D*(\d+[\.]?\d*)\D*$/\1/g ;
                if ("$CYC" eq "") {
                    $CYC = '(fail)' ;
                }
                else {
                    my $cyc_line = $res_cyc[$#res_cyc] ;
                    @res = grep(!/^$cyc_line$/, @res) ;
            pop(@res) ;
            # my $exit_line = grep(/^program exit/, @res[$#res - 2 .. $#res]) ;
            # @res = grep(!/^$exit_line$/, @res) ;
                }
            } # end if (@res_cyc)

            last SWITCH_SIM ;
        } # end if ($sim eq 'sim-ame')

        # -------------------------------------------------
        if ($sim eq 'ISS') {

            @res = execute_it_stdout_errbrkhdl(\&$errhdl, \&$brkhdl, @cmd) ;

            $CYC = $res[$#res] ;
            $CYC =~ s/^\D*(\d+)\D*$/\1/g ;
            if ("$CYC" eq "") {
                $CYC = '(fail)' ;
            }

            if ( -f $captured_stdout_file ) {
                @res = read_alllines($captured_stdout_file) ;
            }
            else {
                print STDERR "No '$captured_stdout_file' file.\n" ;
                @res = () ;
            }
            last SWITCH_SIM ;
        } # end if ($sim eq 'runsc100')
        # -------------------------------------------------
        if ($sim eq 'axd') {

            my $axd_log = 'tmp_axd.log' ;
            unlink $axd_log ;

            @res = execute_it_stdout_errbrkhdl(\&$errhdl, \&$brkhdl, @cmd) ;

            unless (open(FILE, "<$axd_log")) {
                print STDERR "No log file ${axd_log}\n";
                @res = () ;
            }
            else {
                my $start_cycle = undef ;
                while ($line = <FILE>) {
                    if ($line =~ /\.Total/)
                    {
                        chomp $line ;
                        my ($CYC_hex) = ($line =~ /^[\s]*[^\s]+[\s]+([^\s]+)[\s]*$/gs) ;
                        $CYC = hex($CYC_hex) ;

                        if (defined($start_cycle)) {
                            $CYC -= $start_cycle;
                        }
                        else {
                            $start_cycle = $CYC;
                        }
                    }
                }
                close(FILE) ;
                print STDOUT "rm -f '${axd_log}'\n" ;
                unlink ${axd_log} ;
            }

            if ( -f $captured_stdout_file ) {
                @res = read_alllines($captured_stdout_file) ;
            }
            else {
                print STDERR "No '$captured_stdout_file' file.\n" ;
                @res = () ;
            }
            last SWITCH_SIM ;
        } # end if ($sim eq 'axd')
        # -------------------------------------------------
        if ($sim eq 'mwrunsim56800e') {

            #DEBUG print STDOUT "\@cmd == ", join(' ', @cmd), "\n" ;
            @res = execute_it_stdout_errbrkhdl(\&$errhdl, \&$brkhdl, @cmd) ;
            foreach my $i (reverse(0 .. $#res)) {
                if ($res[$i] =~ /mwrunsim56800e:.*$/) {
                    my $line = $res[$i] ;
                    if ($PREMATCH eq '') {
                        splice(@res, $i, 1) ;
                    }
                    else {
                        $res[$i] = $PREMATCH ;
                    }
                    if ($line =~ /mwrunsim56800e: Program stopped at:[^\(]*\((\d+)\s*cycles\)\s*$/) {
                        $CYC = $LAST_PAREN_MATCH unless (defined($CYC)) ;
                    }
                }
            }
            last SWITCH_SIM ;
        } # end if ($sim eq 'mwrunsim56800e')
        # -------------------------------------------------
        if ($sim eq 'mwrunsim56800') {

            #DEBUG print STDOUT "\@cmd == ", join(' ', @cmd), "\n" ;
            @res = execute_it_stdout_errbrkhdl(\&$errhdl, \&$brkhdl, @cmd) ;
            foreach my $i (reverse(0 .. $#res)) {
                if ($res[$i] =~ /mwrunsim56800:.*$/) {
                    my $line = $res[$i] ;
                    if ($PREMATCH eq '') {
                        splice(@res, $i, 1) ;
                    }
                    else {
                        $res[$i] = $PREMATCH ;
                    }
                    if ($line =~ /mwrunsim56800: Program stopped at:[^\(]*\((\d+)\s*cycles\)\s*$/) {
                        $CYC = $LAST_PAREN_MATCH unless (defined($CYC)) ;
                    }
                }
            }
            last SWITCH_SIM ;
        } # end if ($sim eq 'mwrunsim56800')
        # -------------------------------------------------

        if($sim eq 'runtcl') {
            @res = execute_it_stdout_errbrkhdl(\&$errhdl, \&$brkhdl, @cmd) ;
            last SWITCH_SIM;
        }

        # -------------------------------------------------

        if($sim eq 'runbf') {
            @res = execute_it_stdout_errbrkhdl(\&$errhdl, \&$brkhdl, @cmd) ;
            last SWITCH_SIM;
        }
        # -------------------------------------------------
        if ($sim eq 'armsd') {
            $CYC = '(not with armsd)' ;
            #DEBUG print STDOUT "\@cmd == ", join(' ', @cmd), "\n" ;
            @res = execute_it_stdout_errbrkhdl(\&$errhdl, \&$brkhdl, @cmd) ;
            last SWITCH_SIM ;
        } # end if ($sim eq 'armsd')

        # -------------------------------------------------

        print STDERR "Simulator '$sim' not recognized.\n" ;

    } # end SWITCH_SIM
    # -----------------------------------------------------

    # number of cycles got from the stdout
    my $QA_CYC = undef ;

    foreach my $i (reverse(0 .. $#res)) {
        if ($res[$i] =~ /\[?qa_cycles=(\d+)\]?\s*$/) {
            $QA_CYC = $LAST_PAREN_MATCH unless (defined($QA_CYC)) ;
            if ($PREMATCH eq '') {
                splice(@res, $i, 1) ;
            }
            else {
                $res[$i] = $PREMATCH ;
            }
        }
    }
    $CYC = $QA_CYC  if      (defined($QA_CYC)) ;
    $CYC = '(fail)' unless (defined($CYC)) ;

    # If the stdout was not stored in the sc100_sim file by the simulator
    # or if we removed the qa_cycles from the stdout,
    # we have to store the stdout in stdout_sim.
    if (defined($QA_CYC) or not(grep(/^${sim}$/, ('sc100-sim', 'ISS', 'axd')))) {
        open (OUTPUT, "> $captured_stdout_file") 	|| die "can't open $captured_stdout_file: $!";
        autoflush OUTPUT 1 ;
        foreach (@res) {
            print OUTPUT $_, "\n" ;
        }
        close(OUTPUT)	    	|| die "can't close $captured_stdout_file: $!";
    }
    return ($CYC, [@res]) ;
} # end of sub run_sim_errbrkhdl

# ---------------------------------------------------------------------------------------

1 ;

