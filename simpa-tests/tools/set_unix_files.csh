#!/usr/bin/tcsh -f
# version:              1.0
# date of creation:     12/02/2004
# date of modification: 12/05/2004
# author:               Guerte Yves
# usage:                set_unix_files.csh
#                       dos2unix all MSDOS text files in the QA if no directory is provided as parameter

if ( $#argv != 0 ) then

    @ i = 1
    while ($i <= $#argv)

            if ( -d "$argv[$i]" ) then
                pushd "$argv[$i]" > /dev/null
                if (! $status) then
                    find . -type d -name 'CVS' -prune \
                                    -o -type d -name 'lib' -prune \
                                    -o -type d -name 'bin' -prune \
                                    -o -type f \
                                               ! -name '*.bat' ! -name '*.cmd' \
                                               -exec grepdos.csh {} \; -exec printf 'is MSDOS and ' \; \
                                               -exec is_text.csh {} \; \
                                               -exec printf '%s\n' "tar rf /tmp/dos_files.$$.tar {}" \; \
                                               -exec tar rf /tmp/dos_files.$$.tar {} \; \
                                               -exec printf '%s\n\n' "dos2unix.csh {} {}" \; \
                                               -exec dos2unix.csh {} {} \;

                    popd > /dev/null
                endif
            endif
            @ i++
    end

else
    pushd "$QA_TOOLS" > /dev/null
    find . -type d -name 'CVS' -prune \
                    -o -type d -name 'lib' -prune \
                    -o -type d -name 'bin' -prune \
                    -o -type f \
                               ! -name '*.bat' ! -name '*.cmd' \
                               -exec grepdos.csh {} \; -exec printf 'is MSDOS and ' \; \
                               -exec is_text.csh {} \; \
                               -exec printf '%s\n' "tar rf /tmp/dos_tools.$$.tar {}" \; \
                               -exec tar rf /tmp/dos_tools.$$.tar {} \; \
                               -exec printf '%s\n\n' "dos2unix.csh {} {}" \; \
                               -exec dos2unix.csh {} {} \;

    popd > /dev/null

    pushd "$NEW_QA_ROOT/runtest" > /dev/null
    find . -type d -name 'CVS' -prune \
                    -o -type d -name 'lib' -prune \
                    -o -type d -name 'bin' -prune \
                    -o -type f \
                               ! -name '*.bat' ! -name '*.cmd' \
                               -exec grepdos.csh {} \; -exec printf 'is MSDOS and ' \; \
                               -exec is_text.csh {} \; \
                               -exec printf '%s\n' "tar rf /tmp/dos_root.$$.tar {}" \; \
                               -exec tar rf /tmp/dos_root.$$.tar {} \; \
                               -exec printf '%s\n\n' "dos2unix.csh {} {}" \; \
                               -exec dos2unix.csh {} {} \;

    popd > /dev/null
endif

