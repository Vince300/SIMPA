#!/usr/bin/tcsh -f
set filename="/tmp/menage.$$"

echo "--------------------------------------------------------"         > $filename
echo "Total folder size (in kbytes)                           "         >> $filename
du -sk .                                                                >> $filename
echo "--------------------------------------------------------"         >> $filename
echo "Top N largest files and folders"					>> $filename
du -sk *								> /tmp/tmp.$$
sort -n /tmp/tmp.$$							>> $filename

echo "--------------------------------------------------------"		>> $filename
echo "Files that have not been accessed for more than 365 days"		>> $filename
\rm -f /tmp/tmp.$$
set LIST = (`find . -type f -atime +365 -print`)
foreach ITEM ($LIST)
	du -sk $ITEM >> /tmp/tmp.$$
end
sort -n /tmp/tmp.$$                                                     >> $filename
\rm -f /tmp/tmp.$$

#echo "--------------------------------------------------------"	>> $filename
#echo "Files that have not been modified for more than 365 days"	>> $filename
#find . -type f -mtime +365 -print 					>> $filename

echo "--------------------------------------------------------"		>> $filename
echo "Uncompressed tar files"						>> $filename
\rm -f /tmp/tmp.$$
set LIST = (`find . -name "*.tar"`)
foreach ITEM ($LIST)
	du -sk $ITEM >> /tmp/tmp.$$
end
sort -n /tmp/tmp.$$                                                     >> $filename
\rm -f /tmp/tmp.$$

echo "--------------------------------------------------------"         >> $filename
echo "All your CW executables"						>> $filename
set LIST = (`find . -name "*.eld"` `find . -name "icode"` `find . -name "quartz_icode"` `find . -name "llt*"` `find . -name "cobj"` `find . -name "runsc100"` `find . -name "sc100-sim"` `find . -name "sc100-ld"`)
foreach ITEM ($LIST)
        du -sk $ITEM >> /tmp/tmp.$$
end
sort -n /tmp/tmp.$$                                                     >> $filename
\rm -f /tmp/tmp.$$

echo "--------------------------------------------------------"		>> $filename
echo "Uncompressed PC applications files"				>> $filename
set LIST = (`find . -name "*.exe"` `find . -name "*.doc"` `find . -name "*.ppt"` `find . -name "*.xls"`)
foreach ITEM ($LIST)
	du -sk $ITEM >> /tmp/tmp.$$
end
sort -n /tmp/tmp.$$							>> $filename
\rm -f /tmp/tmp.$$

cat $filename
\rm -f $filename

#for QA reports
#find /home/comtools/QA/runtest/*/*/*/reports -type f -mtime +10 -print > /tmp/old_files_1
#grep -v "history" /tmp/old_files_1 > /tmp/old_files_2
