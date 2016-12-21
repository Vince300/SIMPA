#!/usr/bin/tcsh
set IN_FILE = $1
set TP_FILE = /tmp/TP_$1

echo "Conversion of QA report into Excel test plan for XL"
echo "Report file read is $IN_FILE"

echo "grep Begin $IN_FILE | grep home > $TP_FILE"
grep Begin $IN_FILE | grep home > $TP_FILE

echo "Add excel separators in $TP_FILE"
subst_v0.sh $TP_FILE

echo "End of extraction for excel. Results stored in $TP_FILE"



