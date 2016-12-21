#!/usr/bin/tcsh -vx

setenv QA_TOOLS        "$HOME/simpa-tests/tools"
setenv QA_ROOT     "$HOME/simpa-tests/root"
setenv NEW_QA_ROOT     "$HOME/simpa-tests/root"
setenv PATH "${QA_TOOLS}:${PATH}"

# To define environment variables, this script must not run under a separate shell
unset interactive_shell
set perlexpr = 'unless(open(TTY, "/dev/tty")){print "0\n"}else{print (tcgetpgrp(TTY) == getpgrp()), "\n"}'
set interactive_shell=`perl -M'POSIX qw/getpgrp tcgetpgrp/' -e "${perlexpr}"`
if ( "$interactive_shell" == "" ) set interactive_shell=0

if ( $interactive_shell && ($SHLVL == 2) && ("$0" == "${QA_TOOLS}/startup.csh") ) then
    perl -e "print STDERR 'Warning, you must launch: source $0'"
    perl -e 'print STDERR "\n"'
endif


setenv CC  java
setenv SYS linux
if ( -f "${QA_TOOLS}/startup.csh" ) source "${QA_TOOLS}/startup.csh"

if ($?MANPATH == 0 ) then
	setenv MANPATH ""
endif


