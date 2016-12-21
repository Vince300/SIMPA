#!/usr/bin/tcsh -f
# version:              1.0
# date of creation:     xx/xx/2001
# date of modification: 25/09/2002
# author:               Guerte Yves
#
# usage: tar_QA_TOOLS -t <tarfile> -d <nb_days_with_modification>
#        default values are following ones:
# 	 use '-' as <tarfile> to use STDOUT
# 	 use 0 as <nb_days_with_modification> to use all files


if ( ! $?QA_ROOT || ! $?QA_TOOLS ) then
    echo "Variables QA_ROOT and QA_TOOLS must be set !\n" ;
    exit 1
endif

set ARGS=()
unset HELP
set TARFILE='-'
set NB_DAYS=0

while ( $#argv != 0 )
      switch ( $1:al )
            case -help:
            case -h:
                    set HELP
                    shift
                    breaksw

            case  -t:
                    shift
                    if ( $#argv != 0 ) then
                        set TARFILE=$1
                        shift
                    else
                        set HELP
                    endif
                    breaksw

            case  -d:
                    shift
                    if ( $#argv != 0 ) then
                        set NB_DAYS=$1
                        shift
                    else
                        set HELP
                    endif
                    breaksw

            default:
                    set ARGS = ($ARGS $1)
                    set HELP
                    shift
                    breaksw
      endsw
end


if ( $?HELP ) then
    if ( $#ARGS ) then
       echo ""
       echo "Unrecognized parameters: " $ARGS
       echo ""
    endif
    echo "Usage: $0:t -t <tarfile> -d <nb_days_with_modification>"
    echo "<tarfile> can be '-' for STDOUT"
    echo "<nb_days_with_modification> can be 0 to tar all files"
    echo ""
    exit 1
endif

set TMP1=/tmp/excl.$$
touch $TMP1

pushd ${QA_TOOLS} >& /dev/null
if ($NB_DAYS) then
    find . -mtime +$NB_DAYS -name '*' -type f | tr -d '\015'>> $TMP1
endif
popd >& /dev/null

\nice -n 19 tar cfX $TARFILE $TMP1 -C ${QA_TOOLS} .

rm -f $TMP1 >& /dev/null
exit 0
