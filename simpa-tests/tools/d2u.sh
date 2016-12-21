#!/usr/bin/tcsh -f

if (-w "_Tmp") then
        \rm _Tmp
endif
if( "$OSTYPE" == "linux" ) then
	foreach ITEM ($argv)
	if (-e $ITEM) then
		dos2unix $ITEM
		chmod 553 $ITEM
	else
		 echo "Input file $ITEM doesnt exits"
	endif
else
foreach ITEM ($argv)
	if (-e $ITEM) then
		dos2unix $ITEM > _Tmp
		chmod +w $ITEM
		\mv _Tmp $ITEM
	else
		echo "Input file $ITEM doesnt exits"
	endif
endif
end

if (-w "_Tmp") then
        \rm _Tmp
endif
