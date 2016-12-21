#!/usr/bin/tcsh -f

if ( $#argv != 2) then
   exit 1
endif


cd $1
tar cvf - $2
exit $status

