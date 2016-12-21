#!/usr/bin/tcsh -f

if ( $#argv != 1) then
   exit 1
endif

set scriptname=`basename $0`
grep -v 'not_this_line' $0 | tr -d '\015' > /tmp/$$_$scriptname ; chmod u+rx /tmp/$$_$scriptname ; exec /tmp/$$_$scriptname $*


cd $1
tar xf -
set tar_status=$status

rm -f /tmp/$scriptname ; exit $tar_status
