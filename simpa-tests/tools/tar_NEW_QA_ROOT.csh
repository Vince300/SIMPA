#!/usr/bin/tcsh -f
# version:              1.0
# date of creation:     20/12/2001
# date of modification: 09/04/2003
# author:               Guerte Yves
#
# usage: tar_NEW_QA_ROOT -t <tarfile> -d <nb_days_with_modification>
#        default values are following ones:
# 	 use '-' as <tarfile> to use STDOUT
# 	 use 0 as <nb_days_with_modification> to use all files


# for Cygwin
setenv GREP_OPTIONS '--binary-files=without-match --directories=skip'

if ( ! $?NEW_QA_ROOT || ! $?QA_TOOLS ) then
    echo "Variables NEW_QA_ROOT and QA_TOOLS must be set !\n" ;
    exit 1
endif

set ARGS=()
unset HELP
set TARFILE='-'
set NB_DAYS=0

while ( $#argv != 0 )
      switch ( $1:al )
            case -help:
            case -h:
                    set HELP
                    shift
                    breaksw

            case  -t:
                    shift
                    if ( $#argv != 0 ) then
                        set TARFILE=$1
                        shift
                    else
                        set HELP
                    endif
                    breaksw

            case  -d:
                    shift
                    if ( $#argv != 0 ) then
                        set NB_DAYS=$1
                        shift
                    else
                        set HELP
                    endif
                    breaksw

            default:
                    set ARGS = ($ARGS $1)
                    set HELP
                    shift
                    breaksw
      endsw
end


if ( $?HELP ) then
    if ( $#ARGS ) then
       echo ""
       echo "Unrecognized parameters: " $ARGS
       echo ""
    endif
    echo "Usage: $0:t -t <tarfile> -d <nb_days_with_modification>"
    echo "<tarfile> can be '-' for STDOUT"
    echo "<nb_days_with_modification> can be 0 to tar all files"
    echo ""
    exit 1
endif

set TMP1=`perl -MPOSIX -e 'print tmpnam()'`.exclude
set TMP2=`perl -MPOSIX -e 'print tmpnam()'`.exclude
touch $TMP1

pushd ${NEW_QA_ROOT} >& /dev/null

foreach master (\
                runtest/applications/*/v[0-9]*/run_all \
                runtest/standards/*/v[0-9]*/run_all \
                runtest/unit_tests/*/v[0-9]*/run_all \
                runtest/bug_reports/*/v[0-9]*/run_all \
                runtest/customers/*/*/v[0-9]*/run_all \
                )
    set master_dir="$master:h"

    find "$master_dir" \( -name '*.el[bnd]' -o -name '*.obj' -o -name '*.map' -o -name '*.s[1l]' -o -name '*.trc' \
                          -o -name '*.lock' -o -name 'stdout_sim' -o -name '*.o' -o -name 'self_test.txt' \
                          -o -name '*.bak' -o -name '*.bck' -o -name '*~' \) -print \
        >> $TMP1

    find "$master_dir/reports" \( -name 'report_*' -o -type f -size 0 \) -print \
        | egrep -v 'report.*(history|number).*' \
        >> $TMP1

    if ( -d "$master_dir/.bak" ) then
        find "$master_dir/.bak" >> $TMP1
    endif

    find "$master_dir/outputs" -type f -print >> $TMP1
end

find runtest/allapp_reports -name '*' -type f >> $TMP1
find runtest -name 'current_run_id' >> $TMP1

ls -1 runtest/standards/plumhall/v[0-9]*/plum_reports_scripts/{score,src,summary,txtchk,phchk,unarc}{,.exe} >> $TMP1

if ($NB_DAYS) then
    find runtest -mtime +$NB_DAYS -name '*' -type f >> $TMP1
endif

sort -u $TMP1 | tr -d '\015' > $TMP2

popd >& /dev/null

\nice -n 19 \
  tar cfX $TARFILE $TMP2 \
    -C ${NEW_QA_ROOT} runtest/allapp_reports \
    -C ${NEW_QA_ROOT} runtest/Xicode-F \
    -C ${NEW_QA_ROOT} runtest/scenarios \
    -C ${NEW_QA_ROOT} runtest/applications \
    -C ${NEW_QA_ROOT} runtest/standards \
    -C ${NEW_QA_ROOT} runtest/unit_tests \
    -C ${NEW_QA_ROOT} runtest/bug_reports \
    -C ${NEW_QA_ROOT} runtest/customers \
    -C ${NEW_QA_ROOT} runtest/generic_test

rm -f $TMP1 $TMP2 >& /dev/null
exit 0

