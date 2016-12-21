#!/usr/bin/tcsh -f
# Usage: $0 file command
# and the stdin of the command will be <file>

if ($#argv < 2) then
    echo "Usage:" `basename $0` "file command"
    exit 1
endif

set input=$argv[1]
shift
exec $* < $input
