#!/usr/bin/tcsh -f

if ($#argv != 0) then
    set list = ()
    while ( $#argv != 0 )
      set list = ($list $1)
      shift
    end
else
  set list = (chamechaude granier ongaku pinea vercors veymont)
endif


foreach myhost ($list)
  echo === checking $myhost
  echo 'Bug$nest' | rexec.pl $myhost -l qatools -cygwin /cygdrive/z/local_tools/stop_test.csh
  sleep 5
end
