#!/usr/bin/tcsh -f

set backup='/tmp/backup_noenv_perl_in_tools.tar'

rm -f "$backup" >& /dev/null
touch "$backup"

cd "$QA_TOOLS"
echo "Update $backup"
find . -type f -name '*.p[lm]' -exec egrep -l '^#\!/usr/bin/perl' {} \; \
       -exec tar -uf "$backup" -C "$QA_TOOLS" {} \; \
       -exec perl -n -i.old -e 'tr/\015//d ; s,^#\!/usr/bin/perl,#\!/usr/bin/env perl, ; print;' {} \; \
       -exec dos2unix.csh {} {} \; \
       -exec rm -f "{}.old" \;

echo "Update $backup done"

# --------------------------------------------------------------------------------------------------------

set backup='/tmp/backup_noenv_perl_in_root.tar'

rm -f "$backup" >& /dev/null
touch "$backup"

cd "$NEW_QA_ROOT"
echo "Update $backup"
find . -type f -name '*.p[lm]' -exec egrep -l '^#\!/usr/bin/perl' {} \; \
       -exec tar -uf "$backup" -C "$NEW_QA_ROOT" {} \; \
       -exec perl -n -i.old -e 'tr/\015//d ; s,^#\!/usr/bin/perl,#\!/usr/bin/env perl, ; print;' {} \; \
       -exec dos2unix.csh {} {} \; \
       -exec rm -f "{}.old" \;

echo "Update $backup done"

# --------------------------------------------------------------------------------------------------------

exit 0
