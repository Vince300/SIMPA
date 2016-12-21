#!/usr/bin/env perl

# --------------------------- OPTIONS ---------------------------------------------------
# Title of the test in the header
$str15_title = ' hello world' ;

# --------------------------- FUNCTIONAL OPTIONS ----------------------------------------

# file of filenames for inputs, outputs and reference for the targets 
$fnames =  'files_in_out_ref.txt' ;

# file of filenames for inputs, outputs and reference for the targets in 'light' mode
$fnames_light = 'files_in_out_ref_light.txt' ;

# --------------------------- OPTIONS ---------------------------------------------------

# default mode is "functional" or "performance" or "functional+performance"
$default_test_mode = 'functional+performance' ;

# Normalisation function
$run_norm = '../inputs/run_norm' ;
# Files informations for normalisation
$files_infos = '../inputs/files.infos' ;

# --------------------------- OPTIONS END -----------------------------------------------
# next line is mandatory, don't change it, don't delete it
1 ;
