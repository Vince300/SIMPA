#!/usr/bin/tcsh -f

# To define environment variables, this script must not run under a separate shell
unset interactive_shell
set perlexpr = 'unless(open(TTY, "/dev/tty")){print "0\n"}else{print (tcgetpgrp(TTY) == getpgrp()), "\n"}'
set interactive_shell=`perl -M'POSIX qw/getpgrp tcgetpgrp/' -e "${perlexpr}"`
if ( "$interactive_shell" == "" ) set interactive_shell=0

if ( $interactive_shell && ($SHLVL == 2) && ("$0" == "${QA_TOOLS}/startup.csh") ) then
    perl -e "print STDERR 'Warning, you must launch: source $0'"
    perl -e 'print STDERR "\n"'
endif

# -------------------------------------------------------------------------------
unset ERROR

if (! $?QA_TOOLS) then
    echo "ERROR, the QA_TOOLS variable must be defined."
    set ERROR
endif

# Some SYS available values: solaris, cygwin
#
if (! $?SYS) then
    echo "ERROR, the SYS variable must be defined."
    set ERROR
endif

# Some CC available values: scc, ppc, armcc
#
if (! $?CC) then
    echo "ERROR, the CC variable must be defined."
    set ERROR
endif

if ( $?ERROR) exit 1
# -------------------------------------------------------------------------------
# Common configuration for all systems
if ( -e "${QA_TOOLS}/defaults/startup.csh" )	             source "${QA_TOOLS}/defaults/startup.csh"

# -------------------------------------------------------------------------------
if ( -e "${QA_TOOLS}/defaults/${SYS}/startup.csh" )	     source "${QA_TOOLS}/defaults/${SYS}/startup.csh"
if ( -e "${QA_TOOLS}/compilers/${CC}/${SYS}/startup.csh" )   source "${QA_TOOLS}/compilers/${CC}/${SYS}/startup.csh"
if ( -e "${QA_TOOLS}/compilers/${CC}/startup.csh" )	     source "${QA_TOOLS}/compilers/${CC}/startup.csh"

exit 0

