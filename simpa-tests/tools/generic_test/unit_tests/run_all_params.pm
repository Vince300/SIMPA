#!/bin/perl

# --------------------------- OPTIONS ---------------------------------------------------
# Title of the test in the header
$str15_title = 'Benchmarks loop' ;

# --------------------------- FUNCTIONAL OPTIONS ----------------------------------------

# file of filenames for inputs, outputs and reference for the targets 
$fnames =  'files_in_out_ref.txt' ;

# file of filenames for inputs, outputs and reference for the targets in 'light' mode
$fnames_light = 'files_in_out_ref_light.txt' ;

# --------------------------- PERFORMANCES OPTIONS --------------------------------------

# file of target names and their launching options
$ftargets =  'targets_opt.txt' ;

# file of target names and their launching options, in 'light' mode
$ftargets_light = 'targets_opt_light.txt' ;

# --------------------------- OPTIONS ---------------------------------------------------

# default mode is "functional" or "performance" or "functional+performance"
$default_test_mode = 'functional+performance' ;

# Default targets when the -t option is not used
# We let the completion made after parsing the parameters
@default_targets = () ;

$default_makefile = 'makefile.scc' ;

# Normalisation function
$run_norm = '../inputs/run_norm' ;
# Files informations for normalisation
$files_infos = '../inputs/files.infos' ;

# --------------------------- OPTIONS END -----------------------------------------------
# next line is mandatory, don't change it, don't delete it
1 ;
