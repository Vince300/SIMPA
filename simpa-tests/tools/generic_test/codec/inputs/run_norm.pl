#!/usr/bin/env perl

# version:              1.0
# date of creation:     12/07/2002
# date of modification: 12/07/2002
# author:               Guerte Yves
# usage:                run_norm <files.infos> <input file name> <number of cycles>
#
#         This script prints the value normalized and its unit

use FileHandle ;
use Math::BigFloat;

if (exists($ENV{'QA_TOOLS'})) {
    use lib "$ENV{'QA_TOOLS'}/libperl" ;
    use tools ;
}
else {
    print STDERR "Variable QA_TOOLS must be set !\n" ;
    exit 1
}

autoflush STDOUT 1 ;
autoflush STDERR 1 ;
umask 002 ;

# --------------------------- Function that calculate the MIPS --------------------------
sub norm_mips {
    
    my $nb_cycles       = Math::BigFloat->new(shift);
    my $nb_frames       = Math::BigFloat->new(shift);
    my $samples_per_frm = Math::BigFloat->new(shift);
    my $sample_acq_freq = Math::BigFloat->new(shift);
    
    my $Million         = new Math::BigFloat "1000000.0";
    
    my $nb_mips = $nb_cycles * $sample_acq_freq / $Million / $nb_frames / $samples_per_frm ;
    
    return $nb_mips ;
}

# --------------------------- MAN -------------------------------------------------------
# Manual

$scriptname = $0 ;
$scriptname =~ s/[^\/]*\///g ;

sub man {
    print STDERR "usage: $scriptname <files.infos> <input file name> <number of cycles>\n\n" ;
}

# --------------------------- WE READ THE PARAMETERS ------------------------------------
# Without 3 parameters: manual
#
if ($#ARGV != 2) {
        man() ;
        exit 1 ;
}
# --------------------------- WE READ THE PARAMETERS ------------------------------------
$files_infos = shift @ARGV ;
$input_file_name = shift @ARGV ;
$nb_cycles = shift @ARGV ;

# We test if the number of cycles is a number or an error message
if ( ! ($nb_cycles =~ /[0-9]+/)) {
    print STDOUT "$nb_cycles MIPS\n" ;
    exit 0 ;
}    
    
# Filename ;              number of frames ; number of samples per frame ; frequency of acquisition of the samples (Hz)
my $nb_items = 4 ;

if ( -f "$files_infos" ) {
    
    # We read all the lines of the file 'inputs/files.infos'
    my @inputs_infos = read_goodlines("$files_infos") ;
    
    # We search the lines beginning with $input_file_name
    my @input_infos  = grep(/^\s*$input_file_name\s*;/, @inputs_infos) ;
    
    # if there is a line beginning with $input_file_name
    if (@input_infos) {
        my $line = @input_infos[0] ;
        my (@items) = ($line =~ /[^;]+/gs) ;
        
        # if the number of items separated by ';' is not equal to $nb_items
        if ($#items + 1 < $nb_items) {
            print STDERR "\nERROR: line of '$files_infos' not recognized:\n\n" ;
            print STDERR "$line\n\n" ;
            print STDOUT "(???) MIPS\n" ;
            exit 1 ;
        }
        else {
            foreach my $item (@items) {
                $item =~ s/^\s+//;
                $item =~ s/\s+$//;
            }
            # Filename ;              number of frames ; number of samples per frame ; frequency of acquisition of the samples (Hz)
            shift @items ;
            my $nb_frames       = shift @items ;
            my $samples_per_frm = shift @items ;
            my $sample_acq_freq = shift @items ;
            
            printf STDOUT "%    9.0f, %.3f MIPS\n", $nb_cycles / $nb_frames
                                                   , norm_mips($nb_cycles, $nb_frames, $samples_per_frm, $sample_acq_freq), "\n" ;
        }
    } # end if (@input_infos)
    else {
        print STDERR "\nERROR: no line of '$files_infos' beginning with '$input_file_name'.\n\n" ;
        print STDOUT "(???) MIPS\n" ;
        exit 1 ;
    } # end if ! (@input_infos)
} # end if ( -f "inputs/files.infos" )
else {
    # No information about the input files
    print STDERR "\nERROR: file '$files_infos' not found.\n\n" ;
    print STDOUT "(???) MIPS\n" ;
    exit 1 ;
}

exit 0 ;


