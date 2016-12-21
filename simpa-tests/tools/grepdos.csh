#!/usr/bin/tcsh -f
# version:              1.0
# date of creation:     xx/xx/200x
# date of modification: 12/05/2004
# author:               Guerte Yves
# usage:                grep_dos.csh file_list
#                       reports all the MSDOS files from the list (status = 1 if none is found)

unset has_msdos
@ i = 1
while ($i <= $#argv)
  if ( -f "$argv[$i]" && ! -l "$argv[$i]" ) then
      perl -e 'while (<>) {if (/\r/) {exit 1}}' < "$argv[$i]"
      if (  $status ) then
         printf '%s\n' "$argv[$i]"
         set has_msdos
      endif
  endif
  @ i++
end

if ($?has_msdos) then
  exit 0
endif
exit 1

