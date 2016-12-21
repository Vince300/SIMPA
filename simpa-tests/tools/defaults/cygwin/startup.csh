#!/usr/bin/tcsh -f

# To define environment variables, this script must not run under a separate shell

if (! $?QA_TOOLS) then
    echo "ERROR, the QA_TOOLS variable must be defined."
    exit 1
endif

# We don't want that pattern matching applies with possibly existing files
set noglob

# We update the PATH variable
foreach i ( \
          )
     set quoted   = `echo "${i}" | perl -n -e 'print quotemeta()'`
     set sedexpr1 = "s,${quoted}"'/*:,,g'
     set sedexpr2 = "s,:${quoted}"'/*$,,g'
     # We remove already existing $i in PATH
     setenv PATH `printf '%s\n' "${PATH}" | sed -e "${sedexpr1}" -e "${sedexpr2}"`
     setenv PATH "${i}:${PATH}"
end

unset noglob
exit 0
