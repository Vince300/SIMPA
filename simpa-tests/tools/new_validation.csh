#!/usr/bin/tcsh -f

umask 022

# version:              1.8
# date of creation:     18/09/2001
# date of modification: 31/03/2005
# author:               Guerte Yves
# usage:                Read manual part or launch: new_validation.csh -help

# The runtest directory is $NEW_QA_ROOT/runtest directory
#
if ( ! $?NEW_QA_ROOT || ! $?QA_TOOLS ) then
    echo "Variables NEW_QA_ROOT and QA_TOOLS must be set !\n" ;
    exit 1
else
    set TST_QA_ROOT = "$NEW_QA_ROOT"
    set QA_ROOT_STR = '$NEW_QA_ROOT'
endif

set SYS_KIND=`perl -I"${QA_TOOLS}/libperl" -Mtools -e 'print sys_kind();'`
set HOSTNAME=`hostname`
set HOSTNAME="$HOSTNAME:al"
set SCRIPT_NAME=`basename $0`
set DATE=`date '+%Y-%m-%d'`
unset TEST_COMPILER_INSTALLED

set quotexpr='perl -e '"'"'print quotemeta($ENV{"toperl"})'"'"

# -----------------------------------------------------------------------------
#        PARAMETERS

# for Cygwin
setenv GREP_OPTIONS '--binary-files=without-match --directories=skip'

# -----------------------------------------------------------------------------
# DEFAULT PARAMETERS

if (! -d "$NEW_QA_ROOT/defaults") then
    echo 'WARNING: the "$NEW_QA_ROOT/defaults" directory does not exist, creating it.'
    mkdir -p "$NEW_QA_ROOT/defaults"
endif

set QA_USER = qatools

set DEFAULT_FTP_PORT = 260

# -----------------------------------------------------------------------------
if (! -f "$NEW_QA_ROOT/defaults/new_validation.txt") then
    echo 'WARNING: the "$NEW_QA_ROOT/defaults/new_validation.txt" file does not exist, creating it.'
    echo 'Filling "$NEW_QA_ROOT/defaults/new_validation.txt" with default values for mandatory parameters you must change.'
    echo ''
    cat > "$NEW_QA_ROOT/defaults/new_validation.txt" << _END_
## Remove the # first character to enable the option as a default one
-trace
-nogetqa
-getlib
-nocleantmpcc
-nofill
-sleep 0
# -shareddrive Z
# -qastation taillefer
# -scenario valid_generic_5_pc.scn
_END_
endif
# -----------------------------------------------------------------------------

    #########################################################
    #
    # PARSING OF THE DEFAULTS
    #
    #########################################################
unset HELP

unset DEFAULT_GETQA
unset DEFAULT_RTLIB
unset DEFAULT_QASTATION
unset DEFAULT_OTHERCOMP
unset DEFAULT_QADRIVE
unset DEFAULT_SHAREDDRIVE
unset DEFAULT_SHAREDDIR
unset DEFAULT_LOCAL_SHAREDDRIVE
unset DEFAULT_LOCAL_SHAREDDIR
unset DEFAULT_SCEN
unset DEFAULT_TRACE
unset DEFAULT_CPU_ID
set   DEFAULT_PRFX=""
set   DEFAULT_REMOTE=""
set   DEFAULT_ARGS=()
set   DEFAULT_DEFS=()
unset DEFAULT_SLEEP_DELAY
unset DEFAULT_HINETD
unset DEFAULT_FILL
unset DEFAULT_CLEANTMPCC
unset DEFAULT_REPORT_ORDER

if (-f "$NEW_QA_ROOT/defaults/new_validation.txt") then
    set default_argv = (`grep -v '^#.*$' "$NEW_QA_ROOT/defaults/new_validation.txt"`)
    while ( $#default_argv != 0 )
	  switch ( $default_argv[1]:al )
		case -cpu_id:
			shift default_argv
			set DEFAULT_CPU_ID="$default_argv[1]"
			shift default_argv
			breaksw
		case -hinetd:
			set DEFAULT_HINETD=1
			shift default_argv
			breaksw
		case -nohinetd:
			set DEFAULT_HINETD=0
			shift default_argv
			breaksw
		case -sleep:
			shift default_argv
			set DEFAULT_SLEEP_DELAY="$default_argv[1]"
			shift default_argv
			breaksw
		case -d:
		case -def:
			shift default_argv
			setenv toperl "$default_argv[1]"
			set DEFAULT_DEFS="$DEFAULT_DEFS -D `$quotexpr`"
			shift default_argv
			breaksw
		case -prefix:
			shift default_argv
			set DEFAULT_PRFX="$default_argv[1]"
			shift default_argv
			breaksw
		case -scenario:
			shift default_argv
			set DEFAULT_SCEN="$default_argv[1]"
			shift default_argv
			breaksw
		case -getqa:
			if ( $?DEFAULT_GETQA ) then
			    if ( $DEFAULT_GETQA == 0 ) then
				echo "ERROR in defaults: -getqa and -nogetqa cannot be simultaneous."
				set HELP
			    endif
			else
			    set DEFAULT_GETQA=1
			endif
			shift default_argv
			breaksw
		case -nogetqa:
			if ( $?DEFAULT_GETQA ) then
			    if ( $DEFAULT_GETQA == 1 ) then
				echo "ERROR in defaults: -getqa and -nogetqa cannot be simultaneous."
				set HELP
			    endif
			else
			    set DEFAULT_GETQA=0
			endif
			shift default_argv
			breaksw
		case -getlib:
			if ( $?DEFAULT_RTLIB ) then
			    if ( $DEFAULT_RTLIB != get ) then
				echo "ERROR in defaults: -getlib and -keeplib cannot be simultaneous."
				set HELP
			    endif
			else
			    set DEFAULT_RTLIB=get
			endif
			shift default_argv
			breaksw
		case -keeplib:
			if ( $?DEFAULT_RTLIB ) then
			    if ( $DEFAULT_RTLIB != keep ) then
				echo "ERROR in defaults: -getlib and -keeplib cannot be simultaneous."
				set HELP
			    endif
			else
			    set DEFAULT_RTLIB=keep
			endif
			shift default_argv
			breaksw
		case -shareddrive:
			shift default_argv
			if ( $?DEFAULT_SHAREDDIR ) then
			    echo "ERROR in defaults: compiler and lib cannot be taken from drive ${default_argv[1]:as/://}: and ${DEFAULT_SHAREDDIR} simultaneously."
			    set HELP
			else if ( $?DEFAULT_SHAREDDRIVE ) then
			    if ( "$DEFAULT_SHAREDDRIVE" != "${default_argv[1]:as/://}" ) then
				echo "ERROR in defaults: two different definitions of the shared drive."
				set HELP
			    endif
			else
			    set DEFAULT_SHAREDDRIVE="${default_argv[1]:as/://}"
			endif
			shift default_argv
			breaksw
		case -shareddir:
			shift default_argv
			if ( $?DEFAULT_SHAREDDRIVE ) then
			    echo "ERROR in defaults: compiler and lib cannot be taken from drive ${DEFAULT_SHAREDDRIVE}: and $default_argv[1] simultaneously."
			    set HELP
			else if ( $?DEFAULT_SHAREDDIR ) then
			    if ( "$DEFAULT_SHAREDDIR" != "$default_argv[1]" ) then
				echo "ERROR in defaults: two different definitions of the shared directory."
				set HELP
			    endif
			else
			    set DEFAULT_SHAREDDIR="$default_argv[1]"
			endif
			shift default_argv
			breaksw
		case -local_shareddrive:
			shift default_argv
			if ( $?DEFAULT_LOCAL_SHAREDDIR ) then
			    echo "ERROR in defaults: compiler and lib cannot be taken from drive ${default_argv[1]:as/://}: and ${DEFAULT_LOCAL_SHAREDDIR} simultaneously."
			    set HELP
			else if ( $?DEFAULT_LOCAL_SHAREDDRIVE ) then
			    if ( "$DEFAULT_LOCAL_SHAREDDRIVE" != "${default_argv[1]:as/://}" ) then
				echo "ERROR in defaults: two different definitions of the local shared drive."
				set HELP
			    endif
			else
			    set DEFAULT_LOCAL_SHAREDDRIVE="${default_argv[1]:as/://}"
			endif
			shift default_argv
			breaksw
		case -local_shareddir:
			shift default_argv
			if ( $?DEFAULT_LOCAL_SHAREDDRIVE ) then
			    echo "ERROR in defaults: compiler and lib cannot be taken from drive ${DEFAULT_LOCAL_SHAREDDRIVE}: and $default_argv[1] simultaneously."
			    set HELP
			else if ( $?DEFAULT_LOCAL_SHAREDDIR ) then
			    if ( "$DEFAULT_LOCAL_SHAREDDIR" != "$default_argv[1]" ) then
				echo "ERROR in defaults: two different definitions of the local shared directory."
				set HELP
			    endif
			else
			    set DEFAULT_LOCAL_SHAREDDIR="$default_argv[1]"
			endif
			shift default_argv
			breaksw
		case -qadrive:
			shift default_argv
			if ( $?DEFAULT_QASTATION ) then
			    echo "ERROR in defaults: QA cannot be taken from drive and workstation simultaneously."
			    set HELP
			else if ( $?DEFAULT_QADRIVE ) then
			    if ( "$DEFAULT_QADRIVE" != "${default_argv[1]:as/://}" ) then
				echo "ERROR in defaults: two different definitions of the QA drive."
				set HELP
			    endif
			else
			    set DEFAULT_QADRIVE="${default_argv[1]:as/://}"
			endif
			shift default_argv
			breaksw
		case -qastation
			shift default_argv
			if ( $?DEFAULT_QADRIVE ) then
			    echo "ERROR in defaults: QA cannot be taken from drive and workstation simultaneously."
			    set HELP
			else if ( $?DEFAULT_QASTATION ) then
			    if ( "$DEFAULT_QASTATION" != "$default_argv[1]" ) then
				echo "ERROR in defaults: two different definitions of workstation from which to get the QA."
				set HELP
			    endif
			else
			    set DEFAULT_QASTATION="$default_argv[1]"
			endif
			shift default_argv
			breaksw
		case -othercomp
			shift default_argv
			if ( $?DEFAULT_OTHERCOMP ) then
			    if ( "$DEFAULT_OTHERCOMP" != "$default_argv[1]" ) then
				echo "ERROR in defaults: two different definitions of the alternate compiler to use."
				set HELP
			    endif
			else
			    set DEFAULT_OTHERCOMP="$default_argv[1]"
			endif
			shift default_argv
			breaksw
		case -remote:
			shift default_argv
			set DEFAULT_REMOTE="$default_argv[1]"
			shift default_argv
			breaksw
		case -trace:
			set DEFAULT_TRACE=1
			shift default_argv
			breaksw
		case -notrace:
			set DEFAULT_TRACE=0
			shift default_argv
			breaksw
		case -fill:
			set DEFAULT_FILL=1
			shift default_argv
			breaksw
		case -nofill:
			set DEFAULT_FILL=0
			shift default_argv
			breaksw
		case -cleantmpcc:
			set DEFAULT_CLEANTMPCC=1
			shift default_argv
			breaksw
		case -nocleantmpcc:
			set DEFAULT_CLEANTMPCC=0
			shift default_argv
			breaksw
		case -report_order:
			shift default_argv
			set DEFAULT_REPORT_ORDER="$default_argv[1]"
			shift default_argv
			breaksw
		default:
			set DEFAULT_ARGS = ($DEFAULT_ARGS $default_argv[1])
			shift default_argv
			breaksw
	  endsw
    end

    if ( $#DEFAULT_ARGS ) then
       echo ''
       echo 'ERROR, Unrecognized default parameters: ' $DEFAULT_ARGS
       echo ''
       set HELP
       echo ''
    endif
endif
# end if the file of defaults exist

# -----------------------------------------------------------------------------

    #########################################################
    #
    # PARSING OF THE COMMAND LINE
    #
    #########################################################

unset GETQA
unset RTLIB
unset QASTATION
unset OTHERCOMP
unset QADRIVE
unset SHAREDDRIVE
unset SHAREDDIR
unset LOCAL_SHAREDDRIVE
unset LOCAL_SHAREDDIR
unset FTP_HOST
unset FTP_PORT
unset SCEN
unset TRACE
unset CPU_ID
unset RUN_ID
set   PRFX=""
set   REMOTE=""
set   ARGS=()
set   DEFS=()
unset SLEEP_DELAY
unset HINETD
unset FILL
unset CLEANTMPCC
unset REPORT_ORDER
unset NOTINTERACTIVE
unset AFTER

while ( $#argv != 0 )
      switch ( $1:al )
	    case -help:
	    case -h:
		    set HELP
		    shift
		    breaksw
	    case -cpu_id:
		    shift
		    set CPU_ID="$argv[1]"
		    shift
		    breaksw
	    case -after:
		    shift
		    set AFTER="$argv[1]"
		    shift
		    breaksw
	    case -r:
	    case -run_id:
		    shift
		    set RUN_ID="$argv[1]"
		    shift
		    breaksw
	    case -hinetd:
		    set HINETD=1
		    shift
		    breaksw
	    case -nohinetd:
		    set HINETD=0
		    shift
		    breaksw
	    case -sleep:
		    shift
		    set SLEEP_DELAY="$argv[1]"
		    shift
		    breaksw
	    case -d:
	    case -def:
		    shift
		    setenv toperl "$argv[1]"
		    set DEFS="$DEFS -D `$quotexpr`"
		    shift
		    breaksw
	    case -prefix:
		    shift
		    set PRFX="$argv[1]"
		    shift
		    breaksw
	    case -scenario:
		    shift
		    set SCEN="$argv[1]"
		    shift
		    breaksw
	    case -getqa:
		    if ( $?GETQA ) then
			if ( $GETQA == 0 ) then
			    echo "ERROR in parameters: -getqa and -nogetqa cannot be simultaneous."
			    set HELP
			endif
		    else
			set GETQA=1
		    endif
		    shift
		    breaksw
	    case -nogetqa:
		    if ( $?GETQA ) then
			if ( $GETQA == 1 ) then
			    echo "ERROR in parameters: -getqa and -nogetqa cannot be simultaneous."
			    set HELP
			endif
		    else
			set GETQA=0
		    endif
		    shift
		    breaksw
	    case -getlib:
		    if ( $?RTLIB ) then
			if ( $RTLIB != get ) then
			    echo "ERROR in parameters: -getlib and -keeplib cannot be simultaneous."
			    set HELP
			endif
		    else
			set RTLIB=get
		    endif
		    shift
		    breaksw
	    case -keeplib:
		    if ( $?RTLIB ) then
			if ( $RTLIB != keep ) then
			    echo "ERROR in parameters: -getlib and -keeplib cannot be simultaneous."
			    set HELP
			endif
		    else
			set RTLIB=keep
		    endif
		    shift
		    breaksw
	    case -shareddrive:
		    shift
		    if ( $?SHAREDDIR ) then
			echo "ERROR in parameters: compiler and lib cannot be taken from drive ${argv[1]:as/://}: and ${SHAREDDIR} simultaneously."
			set HELP
		    else if ( $?SHAREDDRIVE ) then
			if ( "$SHAREDDRIVE" != "${argv[1]:as/://}" ) then
			    echo "ERROR in parameters: two different definitions of the shared drive."
			    set HELP
			endif
		    else
			set SHAREDDRIVE="${argv[1]:as/://}"
		    endif
		    shift
		    breaksw
	    case -shareddir:
		    shift
		    if ( $?SHAREDDRIVE ) then
			echo "ERROR in parameters: compiler and lib cannot be taken from drive ${SHAREDDRIVE}: and $argv[1] simultaneously."
			set HELP
		    else if ( $?SHAREDDIR ) then
			if ( "$SHAREDDIR" != "$argv[1]" ) then
			    echo "ERROR in parameters: two different definitions of the shared directory."
			    set HELP
			endif
		    else
			set SHAREDDIR="$argv[1]"
		    endif
		    shift
		    breaksw
	    case -local_shareddrive:
		    shift
		    if ( $?LOCAL_SHAREDDIR ) then
			echo "ERROR in parameters: compiler and lib cannot be taken from drive ${argv[1]:as/://}: and ${LOCAL_SHAREDDIR} simultaneously."
			set HELP
		    else if ( $?LOCAL_SHAREDDRIVE ) then
			if ( "$LOCAL_SHAREDDRIVE" != "${argv[1]:as/://}" ) then
			    echo "ERROR in parameters: two different definitions of the local shared drive."
			    set HELP
			endif
		    else
			set LOCAL_SHAREDDRIVE="${argv[1]:as/://}"
		    endif
		    shift
		    breaksw
	    case -local_shareddir:
		    shift
		    if ( $?LOCAL_SHAREDDRIVE ) then
			echo "ERROR in parameters: compiler and lib cannot be taken from drive ${LOCAL_SHAREDDRIVE}: and $argv[1] simultaneously."
			set HELP
		    else if ( $?LOCAL_SHAREDDIR ) then
			if ( "$LOCAL_SHAREDDIR" != "$argv[1]" ) then
			    echo "ERROR in parameters: two different definitions of the local shared directory."
			    set HELP
			endif
		    else
			set LOCAL_SHAREDDIR="$argv[1]"
		    endif
		    shift
		    breaksw
            case -ftp_host
                    shift
                    if ( $?FTP_HOST ) then
                        if ( "$FTP_HOST" != "$argv[1]" ) then
                            echo "ERROR in parameters: two different definitions of the FTP host to use."
                            set HELP
                        endif
                    else
                        set FTP_HOST="$argv[1]"
                    endif
                    shift
                    breaksw
            case -ftp_port
                    shift
                    if ( $?FTP_PORT ) then
                        if ( "$FTP_PORT" != "$argv[1]" ) then
                            echo "ERROR in parameters: two different definitions of the FTP port to use."
                            set HELP
                        endif
                    else
                        set FTP_PORT="$argv[1]"
                    endif
                    shift
                    breaksw
	    case -qadrive:
		    shift
		    if ( $?QASTATION ) then
			echo "ERROR in parameters: QA cannot be taken from drive and workstation simultaneously."
			set HELP
		    else if ( $?QADRIVE ) then
			if ( "$QADRIVE" != "${argv[1]:as/://}" ) then
			    echo "ERROR in parameters: two different definitions of the QA drive."
			    set HELP
			endif
		    else
			set QADRIVE="${argv[1]:as/://}"
		    endif
		    shift
		    breaksw
	    case -qastation
		    shift
		    if ( $?QADRIVE ) then
			echo "ERROR in parameters: QA cannot be taken from drive and workstation simultaneously."
			set HELP
		    else if ( $?QASTATION ) then
			if ( "$QASTATION" != "$argv[1]" ) then
			    echo "ERROR in parameters: two different definitions of workstation from which to get the QA."
			    set HELP
			endif
		    else
			set QASTATION="$argv[1]"
		    endif
		    shift
		    breaksw
	    case -othercomp
		    shift
		    if ( $?OTHERCOMP ) then
			if ( "$OTHERCOMP" != "$argv[1]" ) then
			    echo "ERROR in parameters: two different definitions of the alternate compiler to use."
			    set HELP
			endif
		    else
			set OTHERCOMP="$argv[1]"
		    endif
		    shift
		    breaksw
	    case -remote:
		    shift
		    set REMOTE="$argv[1]"
		    shift
		    breaksw
	    case -trace:
		    set TRACE=1
		    shift
		    breaksw
	    case -notrace:
		    set TRACE=0
		    shift
		    breaksw
	    case -fill:
		    set FILL=1
		    shift
		    breaksw
	    case -nofill:
		    set FILL=0
		    shift
		    breaksw
	    case -cleantmpcc:
		    set CLEANTMPCC=1
		    shift
		    breaksw
	    case -nocleantmpcc:
		    set CLEANTMPCC=0
		    shift
		    breaksw
	    case -report_order:
		    shift
		    set REPORT_ORDER="$argv[1]"
		    shift default_argv
		    breaksw
	    case -notinteractive:
		    set NOTINTERACTIVE=1
		    shift
		    breaksw
	    default:
		    set ARGS = ($ARGS $argv[1])
		    shift
		    breaksw
      endsw
end
# -----------------------------------------------------------------------------

    #########################################################
    #
    # DEFAULT VALUES
    #
    #########################################################

# If following values don't have default values, they are set in the file of defaults:
#    -trace
#    -nogetqa
#    -getlib
#    -nocleantmpcc
#    -nofill
#    -sleep 0

unset DEFAULTS
if (! $?GETQA ) then
    if ( $?DEFAULT_GETQA ) then
	set GETQA=$DEFAULT_GETQA
	set DEFAULTS
	echo "Default value used for GETQA: $GETQA"
    else
	echo ' -nogetqa' >> "$NEW_QA_ROOT/defaults/new_validation.txt"
	set GETQA=0
	set DEFAULTS
	echo "Default value used for GETQA: $GETQA"
    endif
endif
if (! $?RTLIB ) then
    if ( $?DEFAULT_RTLIB ) then
	set RTLIB=$DEFAULT_RTLIB
	set DEFAULTS
	echo "Default value used for RTLIB: $RTLIB"
    else
	echo ' -getlib' >> "$NEW_QA_ROOT/defaults/new_validation.txt"
	set RTLIB=get
	set DEFAULTS
	echo "Default value used for RTLIB: $RTLIB"
    endif
endif
if ((! $?QADRIVE) && (! $?QASTATION)) then
    if ( $?DEFAULT_QADRIVE ) then
	set QADRIVE="$DEFAULT_QADRIVE"
	set DEFAULTS
	echo "Default value used for QADRIVE: $QADRIVE"
    endif
    if ( $?DEFAULT_QASTATION ) then
	set QASTATION="$DEFAULT_QASTATION"
	set DEFAULTS
	echo "Default value used for QASTATION: $QASTATION"
    endif
endif
if (! $?OTHERCOMP ) then
    if ( $?DEFAULT_OTHERCOMP ) then
	set OTHERCOMP=$DEFAULT_OTHERCOMP
	set DEFAULTS
	echo "Default value used for OTHERCOMP: $OTHERCOMP"
    endif
endif
if ((! $?SHAREDDRIVE) && (! $?SHAREDDIR)) then
    if ( $?DEFAULT_SHAREDDRIVE ) then
	set SHAREDDRIVE="$DEFAULT_SHAREDDRIVE"
	set DEFAULTS
	echo "Default value used for SHAREDDRIVE: $SHAREDDRIVE"
    endif
    if ( $?DEFAULT_SHAREDDIR ) then
	set SHAREDDIR="$DEFAULT_SHAREDDIR"
	set DEFAULTS
	echo "Default value used for SHAREDDIR: $SHAREDDIR"
    endif
endif
if (! $?REMOTE ) then
    if ($?DEFAULT_REMOTE) then
	set REMOTE=$DEFAULT_REMOTE
	set DEFAULTS
	echo "Default value used for REMOTE: $REMOTE"
    endif
endif
if ( $?DEFAULT_FTP_HOST ) then
    if (! $?FTP_HOST) then
        set FTP_HOST="$DEFAULT_FTP_HOST"
    endif
endif
if ( $?DEFAULT_FTP_PORT ) then
    if (! $?FTP_PORT) then
        set FTP_PORT="$DEFAULT_FTP_PORT"
    endif
endif

if ( "$REMOTE" != "" ) then
    if ((! $?LOCAL_SHAREDDRIVE) && (! $?LOCAL_SHAREDDIR)) then
	if ( $?DEFAULT_LOCAL_SHAREDDRIVE ) then
	    set LOCAL_SHAREDDRIVE="$DEFAULT_LOCAL_SHAREDDRIVE"
	    set DEFAULTS
	    echo "Default value used for LOCAL_SHAREDDRIVE: $LOCAL_SHAREDDRIVE"

	else if ( $?SHAREDDRIVE ) then
	    set LOCAL_SHAREDDRIVE="$SHAREDDRIVE"
	endif
	if ( $?DEFAULT_LOCAL_SHAREDDIR ) then
	    set LOCAL_SHAREDDIR="$DEFAULT_LOCAL_SHAREDDIR"
	    set DEFAULTS
	    echo "Default value used for LOCAL_SHAREDDIR: $LOCAL_SHAREDDIR"

	else if ( $?SHAREDDIR) then
	    set LOCAL_SHAREDDIR="$SHAREDDIR"
	endif
    endif
endif
if (! $?SCEN ) then
    if ($?DEFAULT_SCEN) then
	set SCEN=$DEFAULT_SCEN
	set DEFAULTS
	echo "Default value used for SCEN: $SCEN"
    endif
endif
if (! $?TRACE ) then
    if ($?DEFAULT_TRACE) then
	set TRACE=$DEFAULT_TRACE
	set DEFAULTS
	echo "Default value used for TRACE: $TRACE"
    else
	echo ' -trace' >> "$NEW_QA_ROOT/defaults/new_validation.txt"
	set TRACE=1
	set DEFAULTS
	echo "Default value used for TRACE: $TRACE"
    endif
endif
if (! $?CPU_ID ) then
    if ($?DEFAULT_CPU_ID) then
	set CPU_ID=$DEFAULT_CPU_ID
	set DEFAULTS
	echo "Default value used for CPU_ID: $CPU_ID"
    endif
endif
if (! $?PRFX ) then
    if ($?DEFAULT_PRFX) then
	set PRFX=$DEFAULT_PRFX
	set DEFAULTS
	echo "Default value used for PRFX: $PRFX"
    endif
endif
if (! $?DEFS ) then
    if ($?DEFAULT_DEFS) then
	set DEFS=$DEFAULT_DEFS
	set DEFAULTS
	echo "Default value used for DEFS: $DEFS"
    endif
endif
if ( "$REMOTE" != "" ) then
    if (! $?HINETD ) then
	if ($?DEFAULT_HINETD) then
	    set HINETD=$DEFAULT_HINETD
	    set DEFAULTS
	    echo "Default value used for HINETD: $HINETD"
	endif
    endif
endif
if (! $?SLEEP_DELAY ) then
    if ($?DEFAULT_SLEEP_DELAY) then
	set SLEEP_DELAY=$DEFAULT_SLEEP_DELAY
	set DEFAULTS
	echo "Default value used for SLEEP_DELAY: $SLEEP_DELAY"
    endif
endif
if (! $?FILL ) then
    if ($?DEFAULT_FILL) then
	set FILL=$DEFAULT_FILL
	set DEFAULTS
	echo "Default value used for FILL: $FILL"
    endif
endif
if (! $?CLEANTMPCC ) then
    if ($?DEFAULT_CLEANTMPCC) then
	set CLEANTMPCC=$DEFAULT_CLEANTMPCC
	set DEFAULTS
	echo "Default value used for CLEANTMPCC: $CLEANTMPCC"
    else
	echo ' -nocleantmpcc' >> "$NEW_QA_ROOT/defaults/new_validation.txt"
	set CLEANTMPCC=0
	set DEFAULTS
	echo "Default value used for CLEANTMPCC: $CLEANTMPCC"
    endif
endif
if (! $?REPORT_ORDER ) then
    if ($?DEFAULT_REPORT_ORDER) then
	set REPORT_ORDER=$DEFAULT_REPORT_ORDER
	set DEFAULTS
	echo "Default value used for REPORT_ORDER: $REPORT_ORDER"
    endif
endif

if ( $#ARGS ) then
   echo ''
   echo "ERROR, Unrecognized parameters: " $ARGS
   set HELP
   echo ''
endif


# -----------------------------------------------------------------------------


    #########################################################
    #
    # MANUAL if error or on request
    #
    #########################################################
if ( $?HELP ) then
    echo ''
    echo "usage: $0:t parameters"
    echo 'The parameters are:'
    echo '               [-help]'
    echo '               [-trace | -notrace]'
    echo '               [-sleep <sec_sleep_delay>]'
    echo '               [-cpu_id <cpu_id_string>]'
    echo '               [-run_id <run_id_number>]'
    echo '               [-after <after_run_id_number>'
    echo '               [-def <macrodef>]*'
    echo '               [-prefix <prfx_string> | -scenario <scenario_fname>]'
    echo '               [-remote <remote_pc> [-hinetd | -nohinetd] ]'
    echo '               [-getqa|-nogetqa]'
    echo '               [-qadrive <drive> | -qastation <workstation_adress>]'
    echo '               [-shareddrive <drive> | -shareddir <directory>]'
    echo '               [-local_shareddrive <drive> | -local_shareddir <directory>]'
    echo '               [-ftp_host <hostname>]'
    echo '               [-ftp_port <ftp port>]'
    echo '               [-othercomp <compiler_path>]'
    echo '               [-getlib | -keeplib]'
    echo '               [-cleantmpcc | -nocleantmpcc]'
    echo '               [-fill | -nofill]'
    echo '               [-report_order <report_scenario_fname>]'
    echo ''
    echo 'The default parameters are defined in your $NEW_QA_ROOT/defaults/new_validation.txt'
    echo 'The mandatory parameter is -shareddrive <drive> or -shareddir <directory>'
    echo ''
    echo 'The sleep delay occur after downloading all necessary data and before running the tests.'
    echo 'The <run_id_number> parameter is used to set the run_id of the tests instead of getting it dynamically.'
    echo 'The <after_run_id_number> parameter is used to wait until the test of specified run_id is finished.'
    echo ''
    echo 'If the -scenario parameter is not provided, the prefix prfx_string is added to ''valid_$HOSTNAME.scn'
    echo 'to build the scenario name.'
    echo "The scenario <scenario_fname> is got in the '$QA_ROOT_STR/runtest/scenarios' folder."
    echo ''
    echo 'On Windows PC with -getqa and -qadrive parameters, the QA is updated from:'
    echo '     /cygdrive/<the_qa_drive>/QA and /cygdrive/<the_qa_drive>/tools'
    echo ''
    echo "With -getqa and -qastation parameters, the QA is updated from ${QA_USER}@<qastation>"
    echo ''
    echo 'On Windows PC with -shareddrive parameter, the compiler is got in:'
    echo '     /cygdrive/<the_shared_drive>/compilers/<compiler_path>/compiler'
    echo ''
    echo 'With -shareddir parameter, the compiler is got in:'
    echo '     <the_shared_directory>/compilers/<compiler_path>/compiler'
    echo ''
    echo 'The -local_shareddrive and -local_shareddir parameters must be used when running tests remotely,'
    echo 'and when the shared location has not the same name on the caller and the called computers.'
    echo ''
    echo ' - Getlib:   we get the runtime library once built and tested by another PC.'
    echo ' - Keeplib:  we use the runtime library provided with the SC compiler.'
    echo ''
    echo 'With -remote <remote_pc>, you must add -hinetd if the inetd daemon is the Hummingbird one.'
    echo 'With -cleantmpcc the locally downloaded compiler is removed after the tests.'
    echo 'With -fill the reports concatenation inserts empty reports where they are missing.'
    echo 'The -report_order option allow to set the report order scenario for the reports concatenation.'
    echo ''
    if ( $?HELP || $#ARGS ) then
	exit 1
    endif
endif

# eval "set DEFS = ( $DEFS )"

if ($?DEFAULTS) then
    echo ""
    echo -n "We assume the parameters are:"
    if ( $?TRACE ) then
	if ($TRACE == 1) then
	    echo -n " -trace"
	else
	    echo -n " -notrace"
	endif
    endif
    if ( $?FILL ) then
	if ($FILL == 1) then
	    echo -n " -fill"
	else
	    echo -n " -nofill"
	endif
    endif
    if ( $?CLEANTMPCC ) then
	if ($CLEANTMPCC == 1) then
	    echo -n " -cleantmpcc"
	else
	    echo -n " -nocleantmpcc"
	endif
    endif
    if ( $?REPORT_ORDER )  then
        echo -n " -report_order ${REPORT_ORDER}"
    endif
    if ( "$PRFX" != "" )   then
        echo -n ' -prefix "'"$PRFX"'"'
    endif
    if ( $?SCEN )          then
        echo -n " -scenario ${SCEN}"
    endif
    if ( $?SLEEP_DELAY )   then
        echo -n " -sleep ${SLEEP_DELAY}"
    endif
    if ( $?AFTER )         then
        echo -n " -after ${AFTER}"
    endif
    if ( $?CPU_ID )        then
        echo -n " -cpu_id ${CPU_ID}"
    endif
    if ( $#DEFS != 0 )     then
        # as definitions are stored in ( -D macro1 -D macro2 ...) form
        echo -n "${DEFS:as/-D /-def /}"
    endif
    if ( "$REMOTE" != "" ) then
        echo -n ' -remote "'"$REMOTE"'"'
    endif
    if ( $?SHAREDDRIVE )   then
        echo -n " -shareddrive ${SHAREDDRIVE}:"
    endif
    if ( $?SHAREDDIR )     then
        echo -n " -shareddir ${SHAREDDIR}"
    endif
    if ( "$REMOTE" != "" ) then
        if ( $?LOCAL_SHAREDDRIVE )  then
            echo -n " -local_shareddrive ${LOCAL_SHAREDDRIVE}:"
        endif
        if ( $?LOCAL_SHAREDDIR )    then
            echo -n " -local_shareddir ${LOCAL_SHAREDDIR}"
        endif
        if ( $?FTP_HOST )           then
            echo -n " -ftp_host ${FTP_HOST}"
        endif
        if ( $?FTP_PORT )           then
            echo -n " -ftp_port ${FTP_PORT}"
        endif
    endif
    if ( $?QADRIVE )       then
        echo -n " -qadrive ${QADRIVE}:"
    endif
    if ( $?QASTATION )     then
        echo -n " -qastation ${QASTATION}"
    endif
    if ( $GETQA == 1 ) then
	echo -n " -GetQA"
    else
	echo -n " -noGetQa"
    endif
    switch ( $RTLIB )
	case get:
		echo -n " -GetLib"
		breaksw
	case keep:
		echo -n " -KeepLib"
		breaksw
    endsw
    if ( $?OTHERCOMP )    then
        echo -n " -othercomp ${OTHERCOMP}"
    endif
    echo "\n"

    set perlexpr = 'open(TTY, "/dev/tty") or die $!; print (tcgetpgrp(TTY) == getpgrp()), "\n";'
    set online=`perl -M'POSIX qw/getpgrp tcgetpgrp/' -e "${perlexpr}"`

    if ("$online" == "1") then
	if (! $?NOTINTERACTIVE ) then
	    echo -n "Is it OK [y|o/n] ? "
	    set ans = $<
	    if ( ("$ans:al" == n) || ("$ans:al" == no)) then
		exit 1
	    endif
	endif
    endif
endif


    # WE VERIFY THE MANDATORY PARAMETERS
if ((! $?SHAREDDRIVE) && (! $?SHAREDDIR) && (! $?FTP_HOST)) then
    echo ''
    echo 'ERROR: mandatory parameter is missing: either -shareddrive <drive> or -shareddir <directory> or -ftp_host <hostname>'
    exit 1
endif

if ( "$REMOTE" != "" ) then
    if ( $?LOCAL_SHAREDDRIVE && (! $?LOCAL_SHAREDDIR)) then
        set LOCAL_SHAREDDIR="/cygdrive/${LOCAL_SHAREDDRIVE}"

        mkdir -p "${LOCAL_SHAREDDIR}/allapp_reports" \
                 "${LOCAL_SHAREDDIR}/archives" \
                 "${LOCAL_SHAREDDIR}/atomic_fail_reports" \
                 "${LOCAL_SHAREDDIR}/running" \
                 "${LOCAL_SHAREDDIR}/tmp" \
                 "${LOCAL_SHAREDDIR}/traces"
    endif

    if (($?SHAREDDIR) && (! $?LOCAL_SHAREDDIR)) then
        mkdir -p "${SHAREDDIR}/allapp_reports" \
                 "${SHAREDDIR}/archives" \
                 "${SHAREDDIR}/atomic_fail_reports" \
                 "${SHAREDDIR}/running" \
                 "${SHAREDDIR}/tmp" \
                 "${SHAREDDIR}/traces"
    endif
endif

    # AFTER THIS BLOC WE ONLY USE ${SHAREDDIR} AND NOT ${SHAREDDRIVE}
if ( $?SHAREDDRIVE && (! $?SHAREDDIR)) then
    set SHAREDDIR="/cygdrive/${SHAREDDRIVE}"
endif

    # IF REMOTE USE FTP, SHAREDDIR AND LOCAL_SHAREDDIR HAVE THE SAME USE
if ($?FTP_HOST) then
    if (($?LOCAL_SHAREDDIR) && (! $?SHAREDDIR)) then
        set SHAREDDIR = "${LOCAL_SHAREDDIR}"
    endif
endif


if ( "$REMOTE" != "" ) then

	# WE VERIFY IF THE OUTPUT DIRECTORIES ARE WRITABLE
    if (! -w "${LOCAL_SHAREDDIR}/allapp_reports") then
	printf '%s\n' "The '${LOCAL_SHAREDDIR}/allapp_reports' directory is not writable."
	exit 1
    endif

    if ( $?TRACE ) then
	if (! -w "${LOCAL_SHAREDDIR}/traces") then
	    printf '%s\n' "The '${LOCAL_SHAREDDIR}/traces' directory is not writable."
	    exit 1
	endif
    endif

    if (! -w "${LOCAL_SHAREDDIR}/atomic_fail_reports") then
        printf '%s\n' "The '${LOCAL_SHAREDDIR}/atomic_fail_reports' directory is not writable."
        exit 1
    endif

	# WE VERIFY IF THE TEST COMPILER EXISTS
    if ($?OTHERCOMP) then
	set ROOTDIR = "${LOCAL_SHAREDDIR}/compilers/${OTHERCOMP}"
    else
	set ROOTDIR = "${LOCAL_SHAREDDIR}/compilers"
    endif
    set COMPDIR = "${ROOTDIR}/compiler"

    if (! -e "${COMPDIR}") then
	printf '%s\n' "The '${COMPDIR}' directory doesn't exist."
	exit 1
    endif
endif

if (! $?FTP_HOST) then
	# WE VERIFY IF THE OUTPUT DIRECTORIES ARE WRITABLE
    if (! -w "${SHAREDDIR}/allapp_reports") then
	printf '%s\n' "The '${SHAREDDIR}/allapp_reports' directory is not writable."
	exit 1
    endif

    if ( $?TRACE ) then
	if (! -w "${SHAREDDIR}/traces") then
	    printf '%s\n' "The '${SHAREDDIR}/traces' directory is not writable."
	    exit 1
	endif
    endif

	# WE VERIFY IF THE TEST COMPILER EXISTS
    if ($?OTHERCOMP) then
	set ROOTDIR = "${SHAREDDIR}/compilers/${OTHERCOMP}"
    else
	set ROOTDIR = "${SHAREDDIR}/compilers"
    endif
    set COMPDIR = "${ROOTDIR}/compiler"

    if (! -e "${COMPDIR}") then
	printf '%s\n' "The '${COMPDIR}' directory doesn't exist."
	exit 1
    endif
endif

    #########################################################

    # WE GET RUN IDs


    # We get the run_id for the tests

if ($?RUN_ID) then
    set test_run_id = "$RUN_ID"
else
    set test_run_id = `get_run_id.pl | sed -e 's/^[^0-9]*\([0-9]*\).*$/\1/' | tail -1`
    if ($status) then
	echo "ERROR: status reported from get_run_id.pl"
	exit 1
    endif
endif
if ( $RTLIB == build ) then
    # We set the run_id for the test of the runtimes
    set valid_lib_run_id = "${test_run_id}_builtlib"
endif

if ($?AFTER) then
    if ("$AFTER" >= "$test_run_id") then
	echo "ERROR: the run_id to wait for (${AFTER}) is greater or equal than the run_id of the test (${test_run_id})."
	echo "ERROR: the -after parameter will not be taken in account."
	unset AFTER
    endif
endif

    #########################################################

    # WE LAUNCH THE VALIDATION ON ANOTHER PC IF REMOTE OPTION

if ( "$REMOTE" != "" ) then
    set REMOTE_OPT= ( -notinteractive )
    if ( "$PRFX" != "" ) then
	set REMOTE_OPT= ( -prefix "$PRFX" )
    endif
    if ( $?TRACE ) then
	if ($TRACE == 1) then
	    set REMOTE_OPT= ( $REMOTE_OPT -trace )
	else
	    set REMOTE_OPT= ( $REMOTE_OPT -notrace )
	endif
    endif
    if ( $?FILL ) then
	if ($FILL == 1) then
	    set REMOTE_OPT= ( $REMOTE_OPT -fill )
	else
	    set REMOTE_OPT= ( $REMOTE_OPT -nofill )
	endif
    endif
    if ( $?CLEANTMPCC ) then
	if ($CLEANTMPCC == 1) then
	    set REMOTE_OPT= ( $REMOTE_OPT -cleantmpcc )
	else
	    set REMOTE_OPT= ( $REMOTE_OPT -nocleantmpcc )
	endif
    endif
    if ( $?REPORT_ORDER ) then
        set REMOTE_OPT= ( $REMOTE_OPT -report_order "${REPORT_ORDER}" )
    endif
    if ( $?SCEN )         then
        set REMOTE_OPT= ( $REMOTE_OPT -scenario "${SCEN}" )
    endif
    if ( $?SLEEP_DELAY )  then
        set REMOTE_OPT= ( $REMOTE_OPT -sleep "${SLEEP_DELAY}" )
    endif
    if ( $?AFTER )        then
        set REMOTE_OPT= ( $REMOTE_OPT -after "${AFTER}" )
    endif
    if ( $?CPU_ID )       then
        set REMOTE_OPT= ( $REMOTE_OPT -cpu_id "${CPU_ID}" )
    endif
    set REMOTE_OPT= ( $REMOTE_OPT -run_id "${test_run_id}" )
    if ( $GETQA == 1 ) then
	set REMOTE_OPT= ( $REMOTE_OPT -GetQA )
    else
	set REMOTE_OPT= ( $REMOTE_OPT -noGetQA )
    endif
    if ( $?SHAREDDRIVE ) then
	set REMOTE_OPT= ( $REMOTE_OPT -shareddrive "${SHAREDDRIVE}:" )
    else if ( $?SHAREDDIR ) then
	set REMOTE_OPT= ( $REMOTE_OPT -shareddir "${SHAREDDIR}" )
    endif
    if ( $?FTP_HOST )     then
        set REMOTE_OPT= ( $REMOTE_OPT -ftp_host "${FTP_HOST}" )
    endif
    if ( $?FTP_PORT )     then
        set REMOTE_OPT= ( $REMOTE_OPT -ftp_port "${FTP_PORT}" )
    endif

    if ( $?QADRIVE )      then
        set REMOTE_OPT= ( $REMOTE_OPT -qadrive "${QADRIVE}:" )
    endif
    if ( $?QASTATION )    then
        set REMOTE_OPT= ( $REMOTE_OPT -qastation "${QASTATION}" )
    endif
    switch ( $RTLIB )
	case get:
		set REMOTE_OPT= ( $REMOTE_OPT -GetLib )
		breaksw
	case keep:
		set REMOTE_OPT= ( $REMOTE_OPT -KeepLib )
		breaksw
    endsw
    if ( $?OTHERCOMP ) then
        set REMOTE_OPT= ( $REMOTE_OPT -othercomp "${OTHERCOMP}" )
    endif

    # echo rexec $REMOTE -l ${QA_USER} cmd.exe /K '"'${SHAREDDRIVE}:\valid_server.bat ${REMOTE_OPT}'"'
    # rexec $REMOTE -l ${QA_USER} cmd.exe /K '"'${SHAREDDRIVE}:\valid_server.bat ${REMOTE_OPT}'"'
    #
#    set CYG_PARAM=-cygwin
#    rexec.pl -l qatools taillefer cmd /C ver
#    if ($status) then
#        set CYG_PARAM=''
#    endif
    #
    if ( $?HINETD ) then
	if ( $HINETD ) then
	    set CYG_PARAM=-cygwin
	else
	    set CYG_PARAM=''
	endif
    else
	set CYG_PARAM=''
    endif

    pushd "${LOCAL_SHAREDDIR}/tmp" >& /dev/null
    set perlscript='use File::Temp qw/tempfile/ ; (undef, $filename) = tempfile("'"${REMOTE}.launch_v${test_run_id}_${DATE}"'_XXXX", DIR=>".", SUFFIX=>".csh", OPEN=>1, UNLINK=>0) ; print "${filename}";'
    set TMP_SCRIPT="`perl -e '${perlscript}'`"
    set TMP_SCRIPT="${TMP_SCRIPT:t}"
    echo "Building start script: ${LOCAL_SHAREDDIR}/tmp/${TMP_SCRIPT}"

    printf '#\!/usr/bin/tcsh -f\n'                  >  "$TMP_SCRIPT"
    printf '%s\n' "set SCRIPT_NAME=$SCRIPT_NAME"    >> "$TMP_SCRIPT"

    set perlscript='use File::Temp qw/tempfile/ ; (undef, $filename) = tempfile("'"${SCRIPT_NAME:r}_${test_run_id}_${DATE}"'_XXXX", DIR=>"/tmp", SUFFIX=>".csh", OPEN=>1, UNLINK=>0) ; print "${filename}";'
    printf '%s\n' "set perlscript='${perlscript}'"                          >> "$TMP_SCRIPT"
    printf '%s\n' 'set TMP_SCRIPT="`perl -e '"'"'${perlscript}'"'"'`"'      >> "$TMP_SCRIPT"
    set RECURSIV = "egrep -v 'not_this_line|perlscript'"' $0 | tr -d '"'\015'"' > $TMP_SCRIPT ; chmod u+rwx $TMP_SCRIPT ; exec $TMP_SCRIPT $*'
    printf '%s\n' "$RECURSIV"                                               >> "$TMP_SCRIPT"

    setenv toperl "$DEFS"
    printf '%s\n' "set DEFS=`$quotexpr`"                   >> "$TMP_SCRIPT"
    printf '%s\n' "set REMOTE_OPT=($REMOTE_OPT)"           >> "$TMP_SCRIPT"
    printf 'eval "${SCRIPT_NAME} ${DEFS} ${REMOTE_OPT}"\n' >> "$TMP_SCRIPT"
    printf 'exit $status ; #not_this_line in TMP_SCRIPT\n' >> "$TMP_SCRIPT"
    printf '%s\n' 'rm -f /tmp/`basename $0` ; exit 0'      >> "$TMP_SCRIPT"

#    printf '%s\n\n' "rexec_b.pl $REMOTE $CYG_PARAM -l ${QA_USER} \nice -n 19 $SCRIPT_NAME ${DEFS} ${REMOTE_OPT}"
#    rexec_b.pl $REMOTE $CYG_PARAM -l ${QA_USER} "\nice -n 19 $SCRIPT_NAME ${DEFS} ${REMOTE_OPT}"

    dos2unix.csh "$TMP_SCRIPT" "$TMP_SCRIPT"
    popd >& /dev/null

    if (! $?FTP_HOST) then
        rexec_b.pl $REMOTE $CYG_PARAM -l ${QA_USER} "${SHAREDDIR}/tmp/${TMP_SCRIPT}"
        exit $status
    else
        echo "Building the tar file of the compiler..."
        set TMP_TAR="`basename '${TMP_SCRIPT}' .csh`.tar"

        lock.pl "/tmp/${TMP_TAR}" > /dev/null
        if (! $status) then
            if (! -r "${SHAREDDIR}/archives/v${test_run_id}/${OTHERCOMP}/compiler.tar.gz") then
                pushd "${ROOTDIR}" > /dev/null
                tar cf "/tmp/${TMP_TAR}" compiler
                if ($status) then
                    echo "Can't build /tmp/${TMP_TAR} from ${ROOTDIR}/compiler."
                    exit 1
                endif
                gzip -9 "/tmp/${TMP_TAR}"
                mkdir -p "${SHAREDDIR}/archives/v${test_run_id}/${OTHERCOMP}"
                cp "/tmp/${TMP_TAR}.gz" "${SHAREDDIR}/archives/v${test_run_id}/${OTHERCOMP}/compiler.tar.gz"
                popd > /dev/null
            endif
            unlock.pl "/tmp/${TMP_TAR}" > /dev/null
            rm -f "/tmp/${TMP_TAR}.gz" >& /dev/null
        endif

        rexec_b.pl $REMOTE $CYG_PARAM -l ${QA_USER} cd /tmp \; ftpget.sh ${FTP_HOST} ${FTP_PORT} ${QA_USER} tmp "${TMP_SCRIPT}" \&\& chmod ug+rx ${TMP_SCRIPT} \; ./${TMP_SCRIPT}
        exit $status
    endif
endif

if ( $?TRACE ) then
    if ( $TRACE == 1 ) then
	# The traced command is launched with -notrace and with STDOUT captured
	set TRACE_OPT= ( -notrace )
	if ( "$PRFX" != "" )     then
            set TRACE_OPT= ( -prefix "$PRFX" )
        endif
	if ( $?FILL ) then
	    if ($FILL == 1) then
		set TRACE_OPT= ( $TRACE_OPT -fill )
	    else
		set TRACE_OPT= ( $TRACE_OPT -nofill )
	    endif
	endif
	if ( $?CLEANTMPCC ) then
	    if ($CLEANTMPCC == 1) then
		set TRACE_OPT= ( $TRACE_OPT -cleantmpcc )
	    else
		set TRACE_OPT= ( $TRACE_OPT -nocleantmpcc )
	    endif
	endif
	if ( $?REPORT_ORDER )    then
            set TRACE_OPT= ( $TRACE_OPT -report_order "${REPORT_ORDER}" )
	endif
        if ( $?SCEN )            then
            set TRACE_OPT= ( $TRACE_OPT -scenario "${SCEN}" )
	endif
	if ( $?SLEEP_DELAY )     then
            set TRACE_OPT= ( $TRACE_OPT -sleep "${SLEEP_DELAY}" )
	endif
	if ( $?AFTER )           then
            set TRACE_OPT= ( $TRACE_OPT -after "${AFTER}" )
	endif
	if ( $?CPU_ID )          then
            set TRACE_OPT= ( $TRACE_OPT -cpu_id "${CPU_ID}" )
	endif
        set TRACE_OPT= ( $TRACE_OPT -run_id "${test_run_id}" )
	if ( $GETQA == 1 ) then
	    set TRACE_OPT= ( $TRACE_OPT -GetQA )
	else
	    set TRACE_OPT= ( $TRACE_OPT -noGetQA )
	endif
	if ( $?SHAREDDRIVE ) then
	    set TRACE_OPT= ( $TRACE_OPT -shareddrive "${SHAREDDRIVE}:" )
	else if ( $?SHAREDDIR ) then
	    set TRACE_OPT= ( $TRACE_OPT -shareddir "${SHAREDDIR}" )
	endif
	if ( $?FTP_HOST )        then
            set TRACE_OPT= ( $TRACE_OPT -ftp_host "${FTP_HOST}" )
	endif
	if ( $?FTP_PORT )        then
            set TRACE_OPT= ( $TRACE_OPT -ftp_port "${FTP_PORT}" )
	endif

	if ( $?QADRIVE )         then
            set TRACE_OPT= ( $TRACE_OPT -qadrive "${QADRIVE}:" )
	endif
	if ( $?QASTATION )       then
            set TRACE_OPT= ( $TRACE_OPT -qastation "${QASTATION}" )
	endif
	switch ( $RTLIB )
	    case build:
		    set TRACE_OPT= ( $TRACE_OPT -BuildLib )
		    breaksw
	    case get:
		    set TRACE_OPT= ( $TRACE_OPT -GetLib )
		    breaksw
	    case keep:
		    set TRACE_OPT= ( $TRACE_OPT -KeepLib )
		    breaksw
	endsw
	if ( $?OTHERCOMP )       then
            set TRACE_OPT= ( $TRACE_OPT -othercomp "${OTHERCOMP}" )
        endif

	set perlscript='use File::Temp qw/tempfile/ ; (undef, $filename) = tempfile("'"${SCRIPT_NAME}_${HOSTNAME}_output_v${test_run_id}_${DATE}_pid$$"'_XXXX", DIR=>"/tmp", SUFFIX=>".txt", OPEN=>1, UNLINK=>0) ; print "${filename}";'
	set TRACE_FILE=`perl -e "${perlscript}"`

	printf 'eval "%s" |& tee "%s"\n'  "${SCRIPT_NAME} ${DEFS} ${TRACE_OPT}"  "${TRACE_FILE}"
	onintr -
	eval "${SCRIPT_NAME} ${DEFS} ${TRACE_OPT}" |& tee "${TRACE_FILE}"
	set valid_status=$status

	gzip -9 "${TRACE_FILE}"
	if (! $?FTP_HOST) then
            cp -f   "${TRACE_FILE}.gz" "${SHAREDDIR}/traces/${HOSTNAME}.output_v${test_run_id}_${DATE}.txt.gz"
            if ($status) then
                    echo "Trace file: ${TRACE_FILE}.gz"
            else
                    echo "Trace file: ${SHAREDDIR}/traces/${HOSTNAME}.output_v${test_run_id}_${DATE}.txt.gz"
                    rm -f "${TRACE_FILE}.gz"
            endif
        else
            ftpput.sh ${FTP_HOST} ${FTP_PORT} ${QA_USER} traces "${TRACE_FILE}.gz" "${HOSTNAME}.output_v${test_run_id}_${DATE}.txt.gz"
            if ($status) then
                    echo "Trace file: ${TRACE_FILE}.gz"
            else
                    echo "Trace file: FTP ${QA_USER}@${FTP_HOST}:traces/${HOSTNAME}.output_v${test_run_id}_${DATE}.txt.gz"
                    rm -f "${TRACE_FILE}.gz"
            endif
        endif
	exit $valid_status
    endif
endif


if ( "$PRFX" != "" ) then
    set PRFX="${PRFX}_"
endif

onintr STOPALL

    #########################################################

    # WE UPDATE THE QA WITH THE SUN ONE

# We verify that we won't do an update from the place where we are
#
set SAME_STORAGE=0
if ( $?QASTATION ) then
    if ( ($GETQA == 1) && ("${HOSTNAME}" == "${QASTATION}" )) then
	set SAME_STORAGE=1
    else
	pushd "$TST_QA_ROOT" > /dev/null
	set TMP_DIR=`perl -e 'use File::Temp qw/ tempdir / ; print tempdir (valid_XXXXXX, DIR => "." );'`
	set REM_STATUS=`rsh -n -l $QA_USER ${QASTATION} 'ls -1 -d ${NEW_QA_ROOT}/'"$TMP_DIR"' >& /dev/null ; echo $status' | tail -1`
	if (! $REM_STATUS) then
	    set SAME_STORAGE=1
	endif
	rmdir "$TMP_DIR"
	popd > /dev/null
    endif
endif

if ( ($GETQA == 1) && $SAME_STORAGE ) then
    echo "ERROR: the -qastation and -getqa parameter tell to update the QA from the same host: ${HOSTNAME}"
endif

if ( ($GETQA == 1) && ! $SAME_STORAGE ) then

    # REMOTE COPY OF THE QA
    chmod -R ug+w "${TST_QA_ROOT}/runtest/."
    chmod -R ug+w "${QA_TOOLS}/."

    if ( $?QASTATION ) then
	echo "Remote copy of the QA from ${QASTATION}"
	pushd "$QA_TOOLS" > /dev/null
	set TMP1=`perl -e 'use File::Temp qw/tempfile/ ; (undef, $filename) = tempfile(excl_XXXX, DIR=>"/tmp", OPEN=>1, UNLINK=>0) ; print $filename;'`
	set TMP2=`perl -e 'use File::Temp qw/tempfile/ ; (undef, $filename) = tempfile(excl_XXXX, DIR=>"/tmp", OPEN=>1, UNLINK=>0) ; print $filename;'`
	chmod a-w "$0"
	echo "$0"                                           >  "$TMP1"
	echo "$SCRIPT_NAME"                                 >> "$TMP1"
	echo "${QA_TOOLS}/$SCRIPT_NAME"                     >> "$TMP1"
	echo "${QA_TOOLS}/Other_src/pc-script/$SCRIPT_NAME" >> "$TMP1"
	echo "Other_src/pc-script/$SCRIPT_NAME"             >> "$TMP1"
	echo "./Other_src/pc-script/$SCRIPT_NAME"           >> "$TMP1"
	tr -d '\015' < "$TMP1"                              >  "$TMP2"
	set counter=0
	DO_RCP_TOOLS:
	  @ counter++
	  rsh -n -l $QA_USER ${QASTATION} '${QA_TOOLS}/tar_QA_TOOLS.csh' | tar xvfBipX - $TMP2 --ignore-failed-read | grep '/$'
	  if ($status && ( $counter < 2)) then
	      goto DO_RCP_TOOLS
	  else
	      echo "QA_TOOLS copied"
	  endif
	rm -f "$TMP1" "$TMP2"
	popd > /dev/null

	pushd "${TST_QA_ROOT}" > /dev/null
	set counter=0
	DO_RCP_QA:
	    @ counter++
	    if ( $?CPU_ID ) then
		if ( $?SCEN ) then
		    rsh -n -l $QA_USER ${QASTATION} \
			'${QA_TOOLS}/tar_NEW_QA_from_scn.pl' -mute -tar - -cpu $CPU_ID $QA_ROOT_STR/runtest/scenarios/${SCEN} \
			| tar xvfBip - --ignore-failed-read | grep '/$'
		    set last_status=$status
		else
		    rsh -n -l $QA_USER ${QASTATION} \
			'${QA_TOOLS}/tar_NEW_QA_from_scn.pl' -mute -tar - -cpu $CPU_ID $QA_ROOT_STR/runtest/scenarios/${PRFX}valid_${HOSTNAME}.scn \
			| tar xvfBip - --ignore-failed-read | grep '/$'
		    set last_status=$status
		endif
	    else if ( $?SCEN ) then
		    rsh -n -l $QA_USER ${QASTATION} \
			'${QA_TOOLS}/tar_NEW_QA_from_scn.pl' -mute -tar - $QA_ROOT_STR/runtest/scenarios/${SCEN} \
			| tar xvfBip - --ignore-failed-read | grep '/$'
		    set last_status=$status
	    else
		rsh -n -l $QA_USER ${QASTATION} \
		    '${QA_TOOLS}/tar_NEW_QA_from_scn.pl' -mute -tar - $QA_ROOT_STR/runtest/scenarios/${PRFX}valid_${HOSTNAME}.scn \
		    | tar xvfBip - --ignore-failed-read | grep '/$'
		set last_status=$status
	    endif
	    if ($last_status && ( $counter < 2)) then
		goto DO_RCP_QA
	    else
		echo "$QA_ROOT_STR copied"
	    endif
	popd > /dev/null
    endif
    if ( $?QADRIVE ) then
	echo "Copy of the QA from ${QADRIVE}:"
	pushd "${QA_TOOLS}" > /dev/null
	tar cf - -C /cygdrive/${QADRIVE}/tools . | tar xvfBip - --ignore-failed-read | grep '/$'
	popd > /dev/null
	pushd "${TST_QA_ROOT}" > /dev/null
	tar cf - -C /cygdrive/${QADRIVE}/QA runtest | tar xvfBip - --ignore-failed-read | grep '/$'
	popd > /dev/null
    endif

    find "${TST_QA_ROOT}/runtest" -name run_all.lock -exec rm {} \;

else
    #########################################################
    # REMOTE COPY OF THE SCENARIOS, for the overnight tests scenarios
    pushd "${TST_QA_ROOT}/runtest/scenarios" > /dev/null
    if ( $?QASTATION && ! $SAME_STORAGE ) then
	echo "Remote copy of ${QASTATION}:'${QA_ROOT_STR}/runtest/scenarios'"
	set counter=0
	DO_RCP_SCEN:
	@ counter++
	rsh -n -l $QA_USER ${QASTATION} "tar cf - -C ${QA_ROOT_STR}/runtest/scenarios ." | tar xfBip - --ignore-failed-read
	if ($status && ( $counter < 2)) then
	    goto DO_RCP_SCEN
	else
	    echo "Scenarios copied"
	endif
    endif
    if ( $?QADRIVE ) then
	tar cf - -C /cygdrive/${QADRIVE}/QA/runtest/scenarios .  | tar xfBip - --ignore-failed-read
    endif
    popd > /dev/null
endif

    #########################################################

    # WE REDEFINE THE COMPILER VARIABLES
mkdir -p "${TST_QA_ROOT}/test_compiler"
chmod ug+w "${TST_QA_ROOT}/test_compiler"

set perlexpr='use File::Temp qw/ tempdir / ; print tempdir ("compiler_'"${test_run_id}"'_XXXXXX", DIR => "'"${TST_QA_ROOT}/test_compiler"'" );'
set TMP_DIR=`perl -e "${perlexpr}"`
if ($status || ("$TMP_DIR" == "")) then
    # Caution because compiler tmpdir creation once failed and entire test_compiler was removed
    set COMPILER_DIR="compiler_${test_run_id}_$$_${HOSTNAME}"
else
    set COMPILER_DIR="${TMP_DIR:t}"
endif
unset COMPILER_EXISTS  TMP_DIR

if ( $SYS == cygwin ) then

    if ( $?SC100_HOME ) then
	setenv OLD_SC100_UHOME    `cygpath --absolute --unix    "$SC100_HOME"`
	setenv OLD_SC100_HOME     `cygpath --absolute --windows "$SC100_HOME"`
    endif

    mkdir -p "${TST_QA_ROOT}/test_compiler/${COMPILER_DIR}"

    echo 'source "${QA_TOOLS}/compilers/${CC}/${SYS}/set_cwfolder.csh" "${NEW_QA_ROOT}/test_compiler/'${COMPILER_DIR}'"' \
	 > "${TST_QA_ROOT}/test_compiler/${COMPILER_DIR}/env.csh"

    echo source "${QA_ROOT_STR}/test_compiler/${COMPILER_DIR}/env.csh"
    source "${TST_QA_ROOT}/test_compiler/${COMPILER_DIR}/env.csh"

    setenv NEW_SC100_HOME     `cygpath --absolute --windows "$SC100_UHOME"`

else
# if ( $SYS != cygwin )

    if ( $?SC100_HOME ) then
        setenv OLD_SC100_UHOME    "$SC100_HOME"
        setenv OLD_SC100_HOME     "$SC100_HOME"
    endif

    mkdir -p "${TST_QA_ROOT}/test_compiler/${COMPILER_DIR}"

    echo 'source "${QA_TOOLS}/compilers/${CC}/${SYS}/set_cwfolder.csh" "${NEW_QA_ROOT}/test_compiler/'${COMPILER_DIR}'"' \
          > "${TST_QA_ROOT}/test_compiler/${COMPILER_DIR}/env.csh"

    echo source "${QA_ROOT_STR}/test_compiler/${COMPILER_DIR}/env.csh"
    source "${TST_QA_ROOT}/test_compiler/${COMPILER_DIR}/env.csh"

    setenv NEW_SC100_HOME     "$SC100_UHOME"
endif
# if ( $SYS != cygwin )

if ( $?OLD_SC100_HOME ) then
    if ("$NEW_SC100_HOME" == "$OLD_SC100_HOME") then
        echo "Bad test directory: NEW_SC100_HOME == SC100_HOME"
        exit 1
    endif
endif

    #########################################################

    # WE COPY THE ALTERNATE COMPILER FILES
if (! $?COMPILER_EXISTS) then

    # We build an exclusion file containing only the env.csh filename
    set TMP=`perl -e 'use File::Temp qw/tempfile/ ; (undef, $filename) = tempfile(excl_XXXX, DIR=>"/tmp", OPEN=>1, UNLINK=>0) ; print $filename;'`
    echo 'env.csh'   >  "$TMP"
    echo './env.csh' >> "$TMP"
    dos2unix.csh "$TMP" "$TMP"

    if ( $?FTP_HOST ) then
        echo "FTP copy from ${QA_USER}@${FTP_HOST}:archives/v${test_run_id}/${OTHERCOMP}/compiler.tar.gz to $SC100_UHOME"
        pushd "$SC100_UHOME" > /dev/null
        ftpget.sh ${FTP_HOST} ${FTP_PORT} ${QA_USER} archives/v${test_run_id}/${OTHERCOMP} compiler.tar.gz
        if ($status) then
            echo "Cannot FTP copy ${QA_USER}@${FTP_HOST}:archives/v${test_run_id}/${OTHERCOMP}/compiler.tar.gz"
        else
            gzip -cd compiler.tar.gz | tar xfBipX - "$TMP"
            rm compiler/env.csh
            mv compiler/* .
            rmdir compiler
            rm -f compiler.tar.gz
            set TEST_COMPILER_INSTALLED
        endif
        popd > /dev/null
    else
        # We need not doing an "else-if" here
        echo -n "Copy to $SC100_UHOME from "
        if (-r "${ROOTDIR}/compiler.tar.gz" ) then
            echo "${ROOTDIR}/compiler.tar.gz"
            set counter=0
            DO_RCP_ROOTDIR_TAR:
            @ counter++
            pushd "$SC100_UHOME" > /dev/null
            tar xfBipX "${ROOTDIR}/compiler.tar.gz" "$TMP"
            if ($status && ( $counter < 2)) then
                goto DO_RCP_ROOTDIR_TAR
            else
                echo "Tarball '${ROOTDIR}/compiler.tar.gz' expanded."
                set TEST_COMPILER_INSTALLED
                chmod -R a+rw "$SC100_UHOME"
            endif
            popd > /dev/null
        else
            echo "${COMPDIR}"
            pushd "${COMPDIR}" > /dev/null
            set counter=0
            DO_RCP_COMPDIR:
            @ counter++
            tar cfX - "$TMP" . | ( cd "$SC100_UHOME" >& /dev/null ; tar xfBip - )
            if ($status && ( $counter < 2)) then
                goto DO_RCP_COMPDIR
            else
                echo "Directory '${COMPDIR}' copied"
                set TEST_COMPILER_INSTALLED
                chmod -R a+rw "$SC100_UHOME"
            endif
            popd > /dev/null
        endif
    endif
    rm -f "$TMP"
endif
rehash
versions.pl

# For the -sleep option
if ( $?SLEEP_DELAY ) then
    if ( $SLEEP_DELAY != 0 ) then
	echo "Sleeping ${SLEEP_DELAY}"
	echo ""
	sleep ${SLEEP_DELAY}
    endif
endif

# For the -after option
if ( $?AFTER ) then
    set perlscript='use File::Temp qw/tempfile/ ; (undef, $filename) = tempfile("'"test_running_${AFTER}"'_XXXX", DIR=>"'"/tmp"'", SUFFIX=>".txt", OPEN=>1, UNLINK=>0) ; print "${filename}";'
    set TMP_FILE=`perl -e "${perlscript}"`

    # Is a test of $AFTER run_id running ?
    #
    (ls -1 "${TST_QA_ROOT}/runtest/"running.v${AFTER}_* > "${TMP_FILE}") >& /dev/null
    set test_running_status = $status

    if ($test_running_status) then
	echo "No RUNNING file for run_id == ${AFTER}."
    else
	echo 'Waiting for the end of' `tr -d '\015' < "${TMP_FILE}"`
	echo -n 'Waiting.'
	while (! $test_running_status)
	    sleep 60
	    (ls -1 "${TST_QA_ROOT}/runtest/"running.v${AFTER}_* > "${TMP_FILE}") >& /dev/null
	    set test_running_status = $status
	    echo -n '.'
	end
	echo ''
	echo 'Continuing as running trace disappeared.'
    endif
    rm -f "${TMP_FILE}"
endif


    #########################################################

    # WE GET THE RUNTIME LIBRARY
if ($?ROOTDIR) then
    if ((! -e "${ROOTDIR}/compiler.tar.gz") && (! $?FTP_HOST )) then
        if ( $RTLIB == get ) then
            pushd "${ROOTDIR}" > /dev/null
            while ( (! -e lib_ok) && (! -e lib_nok) )
                set i=0
                echo "Waiting for the library in drive ${ROOTDIR}"
                while ( ( (! -e lib_ok) && (! -e lib_nok) ) && ( $i < 10 ) )
                    sleep 30
                    @ i++
                end
            end
            if ( -e lib_nok ) then
                echo "Runtime Library NOK."
            else
                echo "Runtime Library OK."
                mkdir -p "$SC100_UHOME/lib"
                cp -fr ${COMPDIR}/lib/* "$SC100_UHOME/lib/."
                chmod -R a+rw "$SC100_UHOME/lib/."
                mkdir -p "$SC100_UHOME/include"
                cp -fr ${COMPDIR}/include/* "$SC100_UHOME/include/."
                chmod -R a+rw "$SC100_UHOME/include/."
            endif
            popd > /dev/null
        endif
    endif
endif
    #########################################################

    # WE BACKUP THE COMPILER

if ($?ROOTDIR) then
    if ((! -e "${ROOTDIR}/compiler.tar.gz") && (! $?FTP_HOST )) then
        if ($?OTHERCOMP) then
            mkdir -p "${SHAREDDIR}/archives/v${test_run_id}/${OTHERCOMP}/compiler"
            rmdir "${SHAREDDIR}/archives/v${test_run_id}/${OTHERCOMP}/compiler" >& /dev/null
            if ( $status ) then
                echo "Other computer is making a backup of the compiler."
            else
                echo "Making a backup of the ${COMPDIR}"' to '"${SHAREDDIR}/archives/v${test_run_id}/${OTHERCOMP}/"
                mkdir -p "${SHAREDDIR}/archives/v${test_run_id}"
                cp -r "${ROOTDIR}"/lib_*ok "${COMPDIR}" "${SHAREDDIR}/archives/v${test_run_id}/${OTHERCOMP}/." |& grep -v 'setting permissions'
            endif
        else
            mkdir -p "${SHAREDDIR}/archives/v${test_run_id}/compiler"
            rmdir "${SHAREDDIR}/archives/v${test_run_id}/compiler" >& /dev/null
            if ( $status ) then
                echo "Other computer is making a backup of the compiler."
            else
                echo "Making a backup of the ${COMPDIR}"' to '"${SHAREDDIR}/archives/v${test_run_id}/"
                cp -r "${ROOTDIR}"/lib_*ok "${COMPDIR}" "${SHAREDDIR}/archives/v${test_run_id}/." |& grep -v 'setting permissions'
            endif
        endif
    endif
endif
    #########################################################

    # WE RUN THE TESTS

set RUN_ALLAPP_PARAMS = ( -r "$test_run_id" )
if ( $?CPU_ID ) then
    set RUN_ALLAPP_PARAMS = ( $RUN_ALLAPP_PARAMS -i "$CPU_ID" )
endif
if ( $?SCEN ) then
    set RUN_ALLAPP_PARAMS = ( $RUN_ALLAPP_PARAMS "scenarios/${SCEN}" )
else
    set RUN_ALLAPP_PARAMS = ( $RUN_ALLAPP_PARAMS "scenarios/${PRFX}valid_${HOSTNAME}.scn" )
endif

onintr -
pushd "${TST_QA_ROOT}/runtest" > /dev/null
setenv TMPSTATUSFILE `perl -e 'use File::Temp qw/tempfile/ ; (undef, $filename) = tempfile(runallapp_status_XXXX, DIR=>"/tmp", SUFFIX=>".txt", OPEN=>1, UNLINK=>0) ; print $filename;'`
echo new_run_allapp.pl -tar $DEFS $RUN_ALLAPP_PARAMS
\nice -n 19 tcsh -f -c "new_run_allapp.pl -tar -atomic_fail_reports $DEFS $RUN_ALLAPP_PARAMS" || echo 1 > "$TMPSTATUSFILE" &
set new_run_allapp_pid = $!

if (! $?FTP_HOST) then
    echo copy_running.pl -r $test_run_id -s "$SHAREDDIR" -p $new_run_allapp_pid
    \nice -n 19 copy_running.pl -r $test_run_id -s "$SHAREDDIR" -p $new_run_allapp_pid < /dev/null > /dev/null &
    echo copy_atomic_fails.pl -r $test_run_id -s "$SHAREDDIR" -p $new_run_allapp_pid
    \nice -n 19 copy_atomic_fails.pl -r $test_run_id -s "$SHAREDDIR" -p $new_run_allapp_pid < /dev/null > /dev/null &
else
    echo copy_atomic_fails.pl -r $test_run_id -ftp_host ${FTP_HOST} -ftp_port ${FTP_PORT} -p $new_run_allapp_pid
    \nice -n 19 copy_atomic_fails.pl -r $test_run_id -ftp_host ${FTP_HOST} -ftp_port ${FTP_PORT} -p $new_run_allapp_pid < /dev/null > /dev/null &
endif

wait
set return_status = `cat "$TMPSTATUSFILE"`
if ("$return_status" == "") then
    set return_status = 0
endif
rm -f "$TMPSTATUSFILE"
popd > /dev/null


# We pack the results
STOPALL:
echo "We pack the results."

set TMP_DIR=`perl -e 'use File::Temp qw/ tempdir / ; print tempdir (validation_XXXXXX, DIR => "/tmp" );'`
if ($status || ("$TMP_DIR" == "")) then
    # Caution because compiler tmpdir creation once failed and entire test_compiler was removed
    set TMP_DIR="/tmp/validation_${test_run_id}_$$_${HOSTNAME}"
endif

set REPORT = `ls -1 -rt "${TST_QA_ROOT}"/runtest/allapp_reports/allapp_report_v${test_run_id}_* | grep -v '\.tar$' | tail -1`
if ( "$REPORT" != "" ) then

    gzip -9 "${REPORT}.tar"
    if ($?FTP_HOST) then
        ftpput.sh ${FTP_HOST} ${FTP_PORT} ${QA_USER} allapp_reports "${REPORT}" "${HOSTNAME}.${REPORT:t}"
        ftpput.sh ${FTP_HOST} ${FTP_PORT} ${QA_USER} allapp_reports "${REPORT}.tar.gz" "${HOSTNAME}.${REPORT:t}.tar.gz"
    else
        cp -f   "${REPORT}"        "${SHAREDDIR}/allapp_reports/${HOSTNAME}.${REPORT:t}"
        cp -f   "${REPORT}.tar.gz" "${SHAREDDIR}/allapp_reports/${HOSTNAME}.${REPORT:t}.tar.gz"
    endif

    # If new_validation was sent from a run_test, run_id was a parameter and there may be others computers reports with same run_id to concatenate
    if ($?RUN_ID) then
        if ( `ls -1 "${SHAREDDIR}"/allapp_reports/*.allapp_report_v${test_run_id}_*.tar.gz | wc -l` > 1 ) then

            if ($?FTP_HOST ) then
                pushd "${TMP_DIR}" > /dev/null
                ftpmget.sh ${FTP_HOST} ${FTP_PORT} ${QA_USER} allapp_reports '*.allapp_report_v'"${test_run_id}"'_*.tar.gz'
                if ($status) then
                    echo "Cannot FTP copy ${QA_USER}@${FTP_HOST}:allapp_reports/*.allapp_report_v${test_run_id}_*.tar.gz"
                endif
                popd > /dev/null
            else
                cp    "${SHAREDDIR}"/allapp_reports/*.allapp_report_v${test_run_id}_*.tar.gz "${TMP_DIR}"
            endif

            gzip -d ${TMP_DIR}/*.allapp_report_v${test_run_id}_*.tar.gz
            set FILL_OPT=''
            if ( $?FILL ) then
                set FILL_OPT='-fill'
            endif
            if (! $?REPORT_ORDER ) then
                set REPORT_ORDER="report_order.scn"
            endif
            echo -n "new_allapp_reports_concat.pl -v v${test_run_id}_concat ${FILL_OPT} -s ${TST_QA_ROOT}/runtest/scenarios/${REPORT_ORDER} "
            echo ${TMP_DIR}/*.allapp_report_v${test_run_id}_*.tar
            new_allapp_reports_concat.pl -v v${test_run_id}_concat ${FILL_OPT} -s "${TST_QA_ROOT}/runtest/scenarios/${REPORT_ORDER}" \
                                         ${TMP_DIR}/*.allapp_report_v${test_run_id}_*.tar

            if ($?FTP_HOST ) then
                echo \
                ftpput.sh ${FTP_HOST} ${FTP_PORT} ${QA_USER} allapp_reports \
                          "${TST_QA_ROOT}/runtest/allapp_reports"/allapp_report_v${test_run_id}_concat \
                          "allapp_report_v${test_run_id}_concat.txt"
                ftpput.sh ${FTP_HOST} ${FTP_PORT} ${QA_USER} allapp_reports \
                          "${TST_QA_ROOT}/runtest/allapp_reports"/allapp_report_v${test_run_id}_concat \
                          "allapp_report_v${test_run_id}_concat.txt"
                if (! $status) rm -f "${TST_QA_ROOT}/runtest/allapp_reports"/allapp_report_v${test_run_id}_concat*
            else
                echo \
                cp -f "${TST_QA_ROOT}/runtest/allapp_reports"/allapp_report_v${test_run_id}_concat "${SHAREDDIR}"/allapp_reports/allapp_report_v${test_run_id}_concat.txt
                cp -f "${TST_QA_ROOT}/runtest/allapp_reports"/allapp_report_v${test_run_id}_concat "${SHAREDDIR}"/allapp_reports/allapp_report_v${test_run_id}_concat.txt
                if (! $status) rm -f "${TST_QA_ROOT}/runtest/allapp_reports"/allapp_report_v${test_run_id}_concat*
            endif
            rm -f ${TMP_DIR}/*.allapp_report_v${test_run_id}_*.tar >& /dev/null
        endif
        rm -rf "${TMP_DIR}"/* >& /dev/null
    endif
else
    echo "ERROR: no report found using 'ls -1 -rt ${TST_QA_ROOT}/runtest/allapp_reports/allapp_report_v${test_run_id}_\*'"
endif

set XMLREPORT = `ls -1 -rt "${TST_QA_ROOT}"/runtest/allapp_reports/allapp_report_v${test_run_id}_*.xml | grep -v '\.tar$' | tail -1`
if ( "$XMLREPORT" != "" ) then

    gzip -9 "${XMLREPORT}"
    if ($?FTP_HOST ) then
        ftpput.sh ${FTP_HOST} ${FTP_PORT} ${QA_USER} allapp_reports "${XMLREPORT}.gz" "${HOSTNAME}.${XMLREPORT:t}.gz"
    else
        cp -f   "${XMLREPORT}.gz"  "${SHAREDDIR}/allapp_reports/${HOSTNAME}.${XMLREPORT:t}.gz"
    endif


    # If new_validation was sent from a run_test, run_id was a parameter and there may be others computers reports with same run_id to concatenate
    if ($?RUN_ID) then
        if ( `ls -1 "${SHAREDDIR}"/allapp_reports/*.allapp_report_v${test_run_id}_*.xml.gz | wc -l` > 1 ) then

            if ($?FTP_HOST ) then
                pushd "${TMP_DIR}" > /dev/null
                ftpmget.sh ${FTP_HOST} ${FTP_PORT} ${QA_USER} allapp_reports '*.allapp_report_v'"${test_run_id}"'_*.xml.gz'
                if ($status) then
                    echo "Cannot FTP copy ${QA_USER}@${FTP_HOST}:allapp_reports/*.allapp_report_v${test_run_id}_*.xml.gz"
                endif
                popd > /dev/null
            else
                cp    "${SHAREDDIR}"/allapp_reports/*.allapp_report_v${test_run_id}_*.xml.gz "${TMP_DIR}"
            endif

            gzip -d ${TMP_DIR}/*.allapp_report_v${test_run_id}_*.xml.gz

            touch "${TMP_DIR}/concat_v${test_run_id}.xml"
            echo -n '$QA_TOOLS/excel/reporting/add_to_xml_history.csh' "${TMP_DIR}/concat_v${test_run_id}.xml "
            echo ${TMP_DIR}/*.allapp_report_v${test_run_id}_*.xml
            "${QA_TOOLS}/excel/reporting/add_to_xml_history.csh" "${TMP_DIR}/concat_v${test_run_id}.xml" ${TMP_DIR}/*.allapp_report_v${test_run_id}_*.xml

            echo gzip -9 "${TMP_DIR}/concat_v${test_run_id}.xml"
            gzip -9 "${TMP_DIR}/concat_v${test_run_id}.xml"

            #
            if ($?FTP_HOST ) then
                echo \
                ftpput.sh ${FTP_HOST} ${FTP_PORT} ${QA_USER} allapp_reports \
                          "${TMP_DIR}/concat_v${test_run_id}.xml.gz" \
                          "allapp_report_v${test_run_id}_concat.xml.gz"
                ftpput.sh ${FTP_HOST} ${FTP_PORT} ${QA_USER} allapp_reports \
                          "${TMP_DIR}/concat_v${test_run_id}.xml.gz" \
                          "allapp_report_v${test_run_id}_concat.xml.gz"
            else
                echo \
                cp -f "${TMP_DIR}/concat_v${test_run_id}.xml.gz" "${SHAREDDIR}/allapp_reports/allapp_report_v${test_run_id}_concat.xml.gz"
                cp -f "${TMP_DIR}/concat_v${test_run_id}.xml.gz" "${SHAREDDIR}/allapp_reports/allapp_report_v${test_run_id}_concat.xml.gz"
            endif
        endif

        rm -rf "${TMP_DIR}" >& /dev/null
        unset TMP_DIR
    endif
endif

if ( $?TEST_COMPILER_INSTALLED ) then
    if ( $CLEANTMPCC == 1) then
        pushd "$SC100_UHOME"
        if (! $status) then
            echo rm -rf "$SC100_UHOME"
            foreach i ( * )
                if ("$i" != "env.csh") then
                    rm -rf "$i"
                endif
            end
        endif
    else
        echo "The $SC100_UHOME compiler is not removed because the -nocleantmpcc option was set."
    endif
endif
exit $return_status

