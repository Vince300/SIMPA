#!/usr/bin/tcsh -f
echo "Conversion of QA report into Excel input file"

set param="$1"

# If the parameter is only the run_id and not the version
if ("$param" == "$param:as/_//") then
    set version=v`ls -1 "${NEW_QA_ROOT}/runtest/allapp_reports"/allapp_report_v${param}_* | sed -e 's/^.*allapp_report_v\([0-9][0-9]*_[^\.]*\).*$/\1/g' | tail -1`
else
    set version="$param"
endif

echo "Version read is ${version}"

echo "cd ${NEW_QA_ROOT}/runtest"
cd "${NEW_QA_ROOT}/runtest"

echo "cp allapp_reports/allapp_report_${version} allapp_reports/allapp_report_${version}.bck"
cp allapp_reports/allapp_report_${version} allapp_reports/allapp_report_${version}.bck

echo "new_allapp_reports_pack.pl -v ${version} scenarios/scc/vl_report_order_v1.scn"
new_allapp_reports_pack.pl -v ${version} scenarios/scc/vl_report_order_v1.scn

# some verifications
set min_lines_one_test=27
set nb_tests=`sort -u scenarios/scc/vl_report_order_v1.scn | wc -l`
@ min_size = $nb_tests * $min_lines_one_test
set perf_report_size=`cat allapp_reports/allapp_report_${version} | wc -l`
if ( $perf_report_size < $min_size ) then
    echo ''
    echo 'WARNING, report too small. Did tests run on this computer? They have to.'
    echo ''
endif

sleep 1

echo "grep PASS allapp_reports/allapp_report_${version} > /tmp/perfxl_${version}.txt"
egrep -i '(pass|fail)' allapp_reports/allapp_report_${version} > /tmp/perfxl_${version}.txt

echo "mv allapp_reports/allapp_report_${version}.bck allapp_reports/allapp_report_${version}"
mv allapp_reports/allapp_report_${version}.bck allapp_reports/allapp_report_${version}

echo "End of extraction for excel. Results stored in /tmp/perfxl_${version}.txt"

