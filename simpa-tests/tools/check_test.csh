#!/usr/bin/tcsh -f

set check = FAIL
cd $NEW_QA_ROOT/runtest

if ($#argv == 1) then
  set ver = $1
else
  set ver = `ls -alprt running.v* | tail -1 | awk '{print $9}'|sed -e "s/^running\.//g"`
endif

rm allapp_reports/allapp_report_$ver
new_allapp_reports_pack.pl -v $ver scenarios/report_order.scn
cp allapp_reports/allapp_report_$ver z:/tmp/$HOST.allapp_report_$ver

clear
echo "========================== begin of grep $check"
grep $check allapp_reports/allapp_report_$ver
echo "========================== end of grep"


echo "\nYou can edit the report by"
echo "  nedit /cygdrive/z/tmp/$HOST.allapp_report_$ver &\n\n"
