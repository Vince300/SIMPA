#!/usr/bin/tcsh -f

# version:              1.0
# date of creation:     14/01/2003
# date of modification: 17/04/2003
# author:               Guerte Yves
# usage:                new_rt_compile.csh <core>*
#          <core> must be among sc110,sc120,sc140,sc140e
#          <core> is sc140 by default

# It uses the new structure of the compiler
# with $SC100_UHOME/lib/{sc110,sc120,sc140,sc140e}/prototype_{le,be}.obj
# instead of $SC100_UHOME/lib/pro{110,120,140,141}[lb].obj with the old one

# prototype files are taken from /cygdrive/${SHAREDDRIVE}/rtlib-src if it exists
# else they are taken from //maxtor/nfs/comtools/rtlib_bucharest if it exists
# else they are taken from ${QA_USER}@${QASTATION}:/home/comtools/enterprise/rtlib-src/rtlib_bucharest

setenv QASTATION scherzo
setenv QA_USER guertey
set    DEFAULT_CORES=('gcc')

umask 022

if (! $?SC100_HOME ) then
    echo "The variable SC100_HOME must be defined !"
    exit 1
endif

# The SYST variable will be "windows" on PCs with Cygwin
#
set SYST = `uname -s | sed -e 's/^\([a-zA-Z]*\).*$/\1/g'`
if ( "$SYST" == 'CYGWIN' ) then
    setenv GREP_OPTIONS '--binary-files=without-match --directories=skip'
    setenv SC100_UHOME `cygpath -u "$SC100_HOME"`
else
    setenv SC100_UHOME "$SC100_HOME"
endif


    #########################################################
    #
    # PARSING OF THE COMMAND LINE
    #
    #########################################################
set ARGS=()
set CORES=()
unset SC100_DEST
unset SC100_OVER

while ( $#argv != 0 )
      switch ( $1:al )
            case -help:
            case -h:
                    set HELP
                    shift
                    breaksw
            case -dest:
                    shift
                    set SC100_DEST="$1"
                    shift
                    breaksw
            case -overwrite:
                    shift
                    set SC100_OVER
                    breaksw
            case sc110:
            case sc120:
            case sc140:
            case sc140e:
                    set CORES=($CORES $1)
                    shift
                    breaksw
            default:
                    set ARGS = ($ARGS $1)
                    set HELP
                    shift
                    breaksw
      endsw
end

if ( ! $?SC100_DEST && ! $?SC100_OVER ) then
    echo ""
    echo "ERROR, you must have either the -overwrite or the -dest <NEW_SC100_HOME> parameters."
    echo ""
    set HELP
endif

# DEFAULTS
unset DEFAULTS
if ( $#CORES == 0 ) then
    set CORES=($DEFAULT_CORES)
    set DEFAULTS
endif


if ( $?HELP || $?DEFAULTS ) then
    if ( $#ARGS ) then
       echo ""
       echo "Unrecognized parameters: " $ARGS
       echo ""
    endif
    echo ""
    echo "usage: $0:t [ -overwrite | -dest <NEW_SC100_HOME> ] "'<core>*'
    echo "      <core> must be among sc110,sc120,sc140,sc140e"
    echo "      <core> is sc140 by default"
    echo ""
    if ( $?HELP || $#ARGS ) then
        exit 1
    endif
endif

# Creating a copy of the compiler if necessary
if ( $?SC100_DEST ) then
    if ( "$SYST" == 'CYGWIN' ) then
        setenv SC100_UDEST `cygpath -u "$SC100_DEST"`
    else
        setenv SC100_UDEST "$SC100_DEST"
    endif

    if ( "$SC100_UDEST" == "$SC100_UHOME" ) then
        echo "Error, destination equals origin. Use -overwrite instead"
        exit 1
    endif

    mkdir -p "$SC100_UDEST"
    if ( $status ) then
        echo "ERROR, cannot create $SC100_UDEST"
        exit 1
    endif
else
    setenv RT_COMP_HOME `perl -e 'use File::Temp qw/ tempdir / ; print tempdir ("RT_COMPILE_XXXXXX", DIR => "/tmp" );'`
    setenv SC100_UDEST  "$RT_COMP_HOME/compiler"
    setenv SC100_DEST   "$SC100_UDEST"
    mkdir -p "$SC100_UDEST"
endif

echo "Copy from $SC100_UHOME to $SC100_UDEST"
pushd "$SC100_UDEST" > /dev/null
tar cf - -C "$SC100_UHOME" . | tar xf -
popd > /dev/null


#########################################################
# PROTOTYPES
mkdir -p       "$SC100_UDEST/../rtlib-src"
chmod -R ug+rw "$SC100_UDEST/../rtlib-src"
pushd "$SC100_UDEST/../rtlib-src" > /dev/null

    # we get prototype.c and prototype.h
if ( "$SYST" == 'CYGWIN' ) then
    getbase utils-src
else
    getfile -r utils-src
endif

chmod -R ug+rw "$SC100_UDEST/include"
chmod -R ug+rw "$SC100_UDEST/src/host"

cp utils-src/*.h "$SC100_UDEST/include/."
cp utils-src/*.c "$SC100_UDEST/src/host/."

mkdir -p   "$SC100_UDEST"/lib/{sc110,sc120,sc140,sc140e,rainbow,msc8101,msc8102,pog}
chmod ug+w "$SC100_UDEST"/lib/{sc110,sc120,sc140,sc140e,rainbow,msc8101,msc8102,pog}

echo "cd $SC100_UDEST/src/host"
cd "$SC100_UDEST/src/host"
echo "build_proto.sh"
./build_proto.sh

if ( $?SC100_OVER ) then
    cd "$SC100_UHOME"
    tar cf - -C "$SC100_UDEST" include src/host lib/{sc110,sc120,sc140,sc140e,rainbow,msc8101,msc8102,pog} | tar xf -
endif

popd > /dev/null

#########################################################
# RUNTIMES

if ( "$SYST" == 'CYGWIN' ) then

    # remote copy of the sources of the library
    mkdir -p       "$SC100_UDEST"
    chmod -R ug+rw "$SC100_UDEST"
    pushd "$SC100_UDEST" > /dev/null
    chmod -R ug+rw lib include src

    unset OK_SHAREDDRIVE
    if ( $?SHAREDDRIVE ) then
        if ( -d /cygdrive/${SHAREDDRIVE}/rtlib-src ) then
            set OK_SHAREDDRIVE
        endif
    endif
    if ( $?OK_SHAREDDRIVE ) then
            echo "Copy of ${SHAREDDRIVE}:\\rtlib-src\\{lib,include,src}"
            tar cf - -C /cygdrive/${SHAREDDRIVE}/rtlib-src lib include src | tar xfBip - --ignore-failed-read

    else if ( $?QASTATION ) then
        set perlcmd="use Socket; print inet_ntoa(inet_aton('$QASTATION'))"
        set hostaddr=`perl -e "$perlcmd"`
        if ( $status ) then
            echo "Remote '${QASTATION}' computer not found."
            exit 1
        else
            echo "Remote copy of ${QASTATION}:/home/comtools/enterprise/rtlib-src/rtlib_bucharest/{lib,include,src}"
            set counter=0
            DO_RCP_LIB:
            @ counter++
            rsh -n -l $QA_USER ${QASTATION} 'cd /home/comtools/enterprise/rtlib-src/rtlib_bucharest > /dev/null ; tar cf - lib include src' | tar xfBip - --ignore-failed-read
            if ($status && ( $counter < 5)) then
                goto DO_RCP_LIB
            endif
        endif
    else
        echo "ERROR, no rtlib-src found"
        exit 1
    endif

    chmod -R ug+rw lib
    popd > /dev/null
else
    mkdir -p       "$SC100_UDEST"
    chmod -R ug+rw "$SC100_UDEST"
    pushd "$SC100_UDEST" > /dev/null
    cp -rf /home/comtools/enterprise/rtlib-src/rtlib_bucharest/{lib,include,src} .
    chmod -R ug+rw lib
    popd > /dev/null
endif

# We get the prototype again...
pushd "$SC100_UDEST/../rtlib-src" > /dev/null
cp utils-src/*.h "$SC100_UDEST/include/."
cp utils-src/*.c "$SC100_UDEST/src/host/."
popd > /dev/null

# We build the runtimes
echo "cd $SC100_UDEST"
pushd "$SC100_UDEST" > /dev/null

if ( `grep -c 'ifneq *( *\$(MAKECMDGOALS), *target_clean *)' src/rtlib/Makefile` == 0 ) then
    perl -n -i.old -e 'tr/\015//d ; \
                       if (/-include \$\(TMPDIR\)\/\.depend/) \
                            {print "ifneq (\$(MAKECMDGOALS),clean)\n", \
                                   "ifneq (\$(MAKECMDGOALS),target_clean)\n", \
                                   "-include \$(TMPDIR)/.depend\n", \
                                   "endif\n", \
                                   "endif\n"} \
                       elsif (/^\s*clean:\s*$/) \
                            {print "target_clean:\n", \
                                   "\t- rm -f \$(TMPDIR)/.depend \$(TMPDIR)/*.elb \$(TMPDIR)/*.eln \$(TMPDIR)/*.sl\n", \
                                   "\t- rm -f \$(TARGET_PATH)/*_\$(ENDIAN).elb \$(TARGET_PATH)/*_\$(ENDIAN).eln\n\n", \
                                   "clean:\n"} \
                       else {print}' src/rtlib/Makefile
endif
foreach CORE ($CORES)
    foreach ENDIAN ('le' 'be')
        echo "gmake -C src/rtlib target_clean CORE=$CORE ENDIAN=$ENDIAN"
        gmake -C src/rtlib target_clean CORE=$CORE ENDIAN=$ENDIAN
        echo "gmake -C src/rtlib CORE=$CORE ENDIAN=$ENDIAN"
        gmake -C src/rtlib CORE=$CORE ENDIAN=$ENDIAN
    end
end


if ( $?SC100_OVER ) then
    cd "$SC100_UHOME"
    tar cf - -C "$SC100_UDEST" include src/host lib/{sc110,sc120,sc140,sc140e,rainbow,msc8101,msc8102,pog} | tar xf -
endif

popd > /dev/null

exit 0

