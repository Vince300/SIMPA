#!/usr/bin/tcsh -f

echo "# `date`"  | tr -d '\015'                                        >>  files_in_out_ref.txt
foreach i ($*)
        echo gmake -r -f makefile "$i" CC=gcc CFLAGS=-DDEBUG
        gmake -r -f makefile "$i" CC=gcc CFLAGS=-DDEBUG

        if ($status) then
            echo "# Error compiling $i"
        else

            printf '%s\n' "bin/$i.exe >  ../ref/$i.ref"
            bin/$i.exe  >  ../ref/$i.ref

            if (`is_text.csh "../ref/$i.ref"` == 'text') then
                echo dos2unix.csh "../ref/$i.ref" "../ref/$i.ref"
                dos2unix.csh "../ref/$i.ref" "../ref/$i.ref"

                echo ''
                echo "# Adding $i.ref to ../ref/.cvswrappers"
                echo "$i.ref      -k 'b'  -m 'COPY'" | tr -d '\015' >> ../ref/.cvswrappers
            endif

            echo ''
            echo "# Adding $i to files_in_out_ref.txt"
            printf '%29s ;   ; %29s ;    ; STDOUT   , %s.ref\n' $i $i $i | tr -d '\015' >> files_in_out_ref.txt

        endif
        echo ""
end

