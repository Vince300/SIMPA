#!/usr/bin/env tcsh

set NOK=0

set REPORT="/tmp/PREREQ_REPORT.TXT"

# ---------------------------------------
# We verify shells are in the right place

if (! -f /bin/sh) then
        echo 'FAIL: the /usr/sh shell does not exist' | tee "$REPORT"
        set NOK=1
else if (! -x /bin/sh) then
        echo 'FAIL: the /bin/sh shell has not executable status' | tee "$REPORT"
        set NOK=1
endif

if (! -f /usr/bin/tcsh) then
        echo 'FAIL: the /usr/bin/tcsh shell does not exist' | tee "$REPORT"
        set NOK=1
else if (! -x /usr/bin/tcsh) then
        echo 'FAIL: the /usr/bin/tcsh shell has not executable status' | tee "$REPORT"
        set NOK=1
endif

# ---------------------------------------
# We verify if required simpa.hit.simpa.drivergen.tools exist

foreach tool (gmake egrep perl)
  which "${tool}" >& /dev/null
  if ($status) then
        echo "FAIL: ${tool} tool is not reachable" | tee "$REPORT"
        set NOK=1
  endif
end

# ---------------------------------------
if ( $NOK == 1 ) then
        echo "The report of the test of prerequisites is in ${REPORT}REPORT"
endif

exit $NOK

