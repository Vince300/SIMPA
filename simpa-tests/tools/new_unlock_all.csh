#!/usr/bin/tcsh -f

pushd $NEW_QA_ROOT/runtest >& /dev/null

glob "{{applications,standards,unit_tests,bug_reports},customers/*}/*/v[0-9]*/run_all.lock" >& /dev/null

if (! $status) then
  foreach lock (  applications/*/v*/run_all.pl.lock \
                  standards/*/v*/run_all.pl.lock \
                  unit_tests/*/v*/run_all.pl.lock \
                  bug_reports/*/v*/run_all.pl.lock \
                  customers/*/*/v*/run_all.pl.lock \
                  )
    set master="$lock:h/$lock:t:r"

    echo -n "Do you want to delete the lock of $master ? (y|o/n) "
    set ans = $<
    if ("$ans" =~ [oOyY] || "$ans" == "") then
      unlock.pl $master
    endif
  end
endif

popd >& /dev/null
exit 0

