#!/usr/bin/tcsh -f
# version:              1.1
# date of creation:     xx/xx/200x
# date of modification: 12/05/2004
# author:               Guerte Yves
# usage:                is_text.csh
#                       reports "text" or "bin" in function of the kind of file (status = 0 is text file)

if ( -Z run_tests.pl < 4000) then
    if ( `tr -d '[[:print:][:punct:][:space:]]' < "${1}"  | wc -c` == 0 ) then

            set NAME = `basename "${1}"`
            set DIR = `dirname "${1}"`

            if ( -f "${DIR}/CVS/Entries" ) then
                grep -q '^/'"${NAME}"'/.*/-kb/$' "${DIR}/CVS/Entries"
                if (! $status) then
                    echo bin
                    exit 1
                endif
            endif

            if ( -f "${DIR}/CVS/Entries.Extra" ) then
                grep -q '^/'"${NAME}"'/.*/-kb/$' "${DIR}/CVS/Entries.Extra"
                if (! $status) then
                    echo bin
                    exit 1
                endif
            endif

            if ( -f "${DIR}/.cvswrappers" ) then
                pushd "${DIR}" > /dev/null
                eval ls -1d `awk "/-k  *'b'/"'{print $1}' < .cvswrappers` | grep -q '^'"${NAME}"'$'
                if (! $status) then
                    echo bin
                    exit 1
                endif
                popd > /dev/null
            endif

            echo text
            exit 0
    else
            echo bin
            exit 1
    endif
else
    set NAME = `basename "${1}"`
    set DIR = `dirname "${1}"`

    if ( -f "${DIR}/CVS/Entries" ) then
        grep -q '^/'"${NAME}"'/.*/-kb/$' "${DIR}/CVS/Entries"
        if (! $status) then
            echo bin
            exit 1
        endif
    endif

    if ( -f "${DIR}/CVS/Entries.Extra" ) then
        grep -q '^/'"${NAME}"'/.*/-kb/$' "${DIR}/CVS/Entries.Extra"
        if (! $status) then
            echo bin
            exit 1
        endif
    endif

    if ( -f "${DIR}/.cvswrappers" ) then
        pushd "${DIR}" > /dev/null
        eval ls -1d `awk "/-k  *'b'/"'{print $1}' < .cvswrappers` | grep -q '^'"${NAME}"'$'
        if (! $status) then
            echo bin
            exit 1
        endif
        popd > /dev/null
    endif

    if ( `tr -d '[[:print:][:punct:][:space:]]' < "${1}"  | wc -c` == 0 ) then
            echo text
            exit 0
    else
            echo bin
            exit 1
    endif
endif
