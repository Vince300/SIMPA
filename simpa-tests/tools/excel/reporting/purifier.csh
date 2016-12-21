#!/usr/bin/tcsh -f
gmake -r clean
rm -f *.stackdump >& /dev/null
cd ..
tar cf  reporting.tar reporting
rm -f   reporting.tar.gz >& /dev/null
gzip -9 reporting.tar
echo -n 'Purifier ' ; ftpput.pl -s ecrins -u purifier -d yves -f reporting.tar.gz
exit $status

