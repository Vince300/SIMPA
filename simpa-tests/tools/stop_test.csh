#!/usr/bin/tcsh

set check = FAIL
cd $NEW_QA_ROOT/runtest

if ($#argv == 1) then
  set ver = $1
else
  set ver = `ls -alprt running.v* | tail -1 | awk '{print $9}'|sed -e "s/^running\.//g"`
endif

if ( -e running.$ver ) then
    touch stop.$ver
endif
