#!/usr/bin/tcsh -f

# version:              1.1
# date of creation:     03/09/2002
# date of modification: 11/03/2005
# author:               Guerte Yves
# usage:                new_cleanup.csh
#                       removes all temporary files from the QA

if (! $?NEW_QA_ROOT) then
    echo "ERROR, the variable NEW_QA_ROOT must be set !"
    exit 1
endif

pushd $NEW_QA_ROOT/runtest >& /dev/null

unset master
unset master_dir
onintr INTR

foreach master (\
                applications/*/v*/run_all.pl \
                standards/*/v*/run_all.pl \
                unit_tests/*/v*/run_all.pl \
                bug_reports/*/v*/run_all.pl \
                customers/*/*/v*/run_all.pl \
                )
    set master_dir="$master:h"

    lock.pl "$master" >& /dev/null
    if (! $status ) then
        set lock_id = `head -1 "$master_dir/run_all.pl.lock"`

        foreach srep (bin outputs obj dasm)
            if ( -d "$master_dir/$srep" ) then
                find "$master_dir/$srep" -type d -name 'CVS' -prune \
		                      -o -type f -print \
                    | egrep -v '(\.cvsignore|\.cvswrappers)' \
                    | perl -n -e 'chomp ; if (($file = $_) !~ /^\s*$/) {print "\# Cannot " unless (unlink "$file") ; print "rm $file\n"}'
            endif
        end

        find "$master_dir/reports" -type d -name 'CVS' -o -name lib -prune -o \
                                   \(    -mtime +30 -name 'report_*' \
                                      -o -mtime +30 -name 'fail_report_*' \
                                      -o -type f -size 0 \) -print \
            | egrep -v '(\.cvsignore|\.cvswrappers|report.*(history|number))' \
            | perl -n -e 'chomp ; if (($file = $_) !~ /^\s*$/) {print "\# Cannot " unless (unlink "$file") ; print "rm $file\n"}'

	find "$master_dir" -type d \( -name 'CVS' -o -name lib -o -name asm -o -name src \
	                              -o -name coder -o -name decoder -o -name common -o -name include \) -prune \
			-o -type f \( -name '*.el[bnd]' -o -name '*.obj' -o -name '*.map' -o -name '*.s[1lw]' -o -name '*.trc' \
                                      -o -name 'stdout_sim' -o -name 'stderr_sim' -o -name '*.o' -o -name 'self_test.txt' \) -print \
            | perl -n -e 'chomp ; if (($file = $_) !~ /^\s*$/) {print "\# Cannot " unless (unlink "$file") ; print "rm $file\n"}'

        unlock.pl "$master"  >& /dev/null
        unset lock_id
    else
        echo "# $master locked"
    endif
end

popd >& /dev/null

pushd $NEW_QA_ROOT/test_compiler >& /dev/null
if ($status) exit 1

# We remove empty temporary compiler directories older than 5 days
foreach dd (*/.)
    set d=`dirname "${dd}"`
    set l=(`ls -1 "${d}"`)

    set ok=0
    if ($#l == 0) set ok=1
    if ($#l == 1) then
        if ("$l[1]" == 'env.csh') set ok=1
    endif
    if ($ok == 1) then
        find "${d}" -type d -name "${d}" -mtime +5 -print \
        | perl -n -e 'use File::Path ; chomp ; if (($dir = $_) !~ /^\s*$/) {print "\# Cannot " unless (rmtree("$dir", 0, 0)) ; print "rm -rf $dir\n"}'
    endif
end

popd >& /dev/null
exit 0

INTR:
echo "Interruption occurred."
cd $NEW_QA_ROOT/runtest >& /dev/null

if ($?lock_id) then
    echo "Master script $master_dir/run_all.pl perhaps locked"

    if ( -f "$master_dir/run_all.pl.lock" ) then
        if ( "$lock_id" == `head -1 "$master_dir/run_all.pl.lock"`) then
            echo "Master script $master_dir/run_all.pl was locked by me."
            unlock.pl "$master_dir/run_all.pl"
        else
            echo "Master script $master_dir/run_all.pl was locked by someone else."
        endif
    else
        echo "Lock $master_dir/run_all.pl.lock doesn't exist."
    endif
endif
popd >& /dev/null
exit 0

