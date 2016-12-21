#!/usr/bin/tcsh -f
# Usage: $0 file command
# and the stdout of the command will be in <file>

if ($#argv < 2) then
    echo "Usage:" `basename $0` "file command"
    exit 1
endif

set output=$argv[1]
shift

\rm -f $output.stderr >& /dev/null
\rm -f $output.status >& /dev/null
($* > $output) |& tee $output.stderr

set RETVAL=$status
echo $RETVAL
exit $RETVAL
