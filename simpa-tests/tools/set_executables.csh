#!/usr/bin/tcsh -f
# version:              1.0
# date of creation:     12/02/2004
# date of modification: 12/02/2004
# author:               Guerte Yves
# usage:                set_executables.csh
#                       set the exec flag to all scripts in the QA

find "$QA_TOOLS"    -type d -name 'CVS' -prune -o -type f \( -name '*.{pl,sh,csh,exe,com,cmd}' -print -o -exec egrep -l '^(#\!/usr/bin|#\!/bin|#\!/usr/local/bin)' {} \; \) -exec chmod ug+rx {} \;
find "$NEW_QA_ROOT" -type d -name 'CVS' -prune -o -type f \( -name '*.{pl,sh,csh,exe,com,cmd}' -o -exec has_exec_header.sh {} \; \) -exec chmod ug+rx {} \; -print

