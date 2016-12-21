hello world for regression

You have to first make sure your target with with this 
example/generic makefile. Multiple targets setup seems
to be non-trival under current 'QA' framework, original
implementation handle that in the generic makefile using
defines(pls see ARM), but I choosed to deal with those 
architecture specific issues from the warpers in target 
specific area.

create a corresponding folder in runtest/<your arch>
-create scenarios, utils folder in it
-define warper compile/assemble/link like this:

#!/bin/perl
require "$ENV{'NEW_QA_ROOT'}/runtest/dsp56800e/utils/cwenv.pm";

#set environment for PATH, include header, runtime libraries, 
#cygdrive, CWFOLDER so you can call it like GCC
&setenv;

system("mwcc56800e @ARGV");

If your runtime rely on assembly startup file/vector table that
is not included in the runtime lib, you might want to create
one more warper "linkruntime" and use that in place of link.
Or you can consider dropping your custom prebuilt lib with
runtime + those startup file/vector table in your util folder.

runtest/generic_test/unit_tests/last/makefile_generic.mk
-add entries in those two sections that have ifeq "$(CC)" "your arch"	
(I followed MWTH) using the warpers you just defined.

edit run_sim_(your latest points to).pm
-# Available simulators :
add mwrunsim56800e
-run_sim_cmd {
add a case
-run_sim {
add a case
-run_sim_errbrkhdl {
add a case

follow these steps, assuming single file programs

-copy this template

-create makefile.xxx following makefile.gcc
MAKEFILENAME = makefile.xxx
MADATORY_(capitialize version of XXX) = <additional flags/defines you want to pass to compiler>
CC = xxx
include ./makefile

-edit run_all_params.pm at str15_title:

-edit files_in_out_ref.txt and files_in_out_ref_light.txt 
and change target, change the control case, input/output file
if necessary

-edit makefile, change the list SRC_FILES, ASM_SRC, LIB

-prepare your control case (defaulted to ref/control1.ref, ref/control2.ref)
you might want to consider using -no_clean to capture the first control case

-under tcsh at your directory containing run_all, issue
"./run_all -m makefile.xxx -v <your unique tag> -s <your simulator or "none" if hosted>"

