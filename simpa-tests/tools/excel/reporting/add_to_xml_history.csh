#!/usr/bin/tcsh -f

# date of creation:     02/12/2004
# date of modification: 24/01/2005
# author:               Guerte Yves
# usage:                launch with -help option

if ( ($#argv == 0) || ("$1:al" == '-help') || ("$1:al" == '--help') ) then

        set SCRIPT_NAME=`basename $0`
        echo 'Syntax:'
        echo "\t" $SCRIPT_NAME 'history_file.xml' 'report_1_file.xml' 'report_2_file.xml' '..' 'report_n_file.xml'
        echo 'The "history_file.xml" may be empty.'
        echo ''
        exit 0
endif

set history="$1"
shift
set reports=( $* )

echo adding $#reports 'report(s)' to "$history".

if ( -er "$history" ) then
    echo copy "$history" to "$history.bak"
    cp "$history" "$history.bak"
    if ($status) exit 1
else
    echo Creating "$history"
    echo '' | dos2unix.csh > "$history"
    echo '' | dos2unix.csh > "$history.bak"
endif

set TMPFILE=`perl -e 'use File::Temp qw/tempfile/ ; (undef, $filename) = tempfile(history_XXXX, DIR=>"/tmp", SUFFIX=>".xml", OPEN=>1, UNLINK=>0) ; print $filename;'`

# We remove XML and "history" tags from the original history concatenated with reports
cat "$history.bak" | cat - $reports | grep -v '</*HISTORY>' | fgrep -vi '<?xml version' > "$TMPFILE"

# We add XML and "history" tags
printf '%s\n' '<?xml version="1.0" ?>' '<HISTORY>' | cat - "$TMPFILE" | dos2unix.csh > "$history"
printf '%s\n' '</HISTORY>' | dos2unix.csh >> "$history"

rm -f "$TMPFILE"

echo "$history" updated.

exit 0
