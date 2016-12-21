#!/usr/bin/tcsh -f

set scriptname=`basename $0`

if ( $#argv == 0 ) then
    tr -d '\015'
    exit $status
else if ( $#argv != 2 ) then
    perl -e "print STDERR 'ERROR, syntax: $scriptname in_file out_file';"
    perl -e 'print STDERR "\n";'
    exit 1
else
    if ( -d $argv[1] ) exit 0
    if ( `is_text.csh $argv[1]` == 'bin' ) exit 0
    set tmpnam = `perl -MPOSIX -e 'print tmpnam();'`
    rm -f "$tmpnam"
    tr -d '\015' < "$argv[1]" > "$tmpnam"
    if ( $status ) then
        perl -e "print STDERR 'ERROR converting $argv[1] to $tmpnam';"
        perl -e 'print STDERR "\n";'
        exit 1
    else
        cp "$tmpnam" "$argv[2]"
        if ( $status ) then
            perl -e "print STDERR 'ERROR copying $tmpnam to $argv[2]';"
            perl -e 'print STDERR "\n";'
            exit 1
        else
            rm -f "$tmpnam"
        endif
    endif
endif
exit 0

