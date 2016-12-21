#!/usr/bin/env perl

# auteur : guerte yves
# date : 12/05/00
# utilisation : hexa_to_bin.pl < fic_hexa.txt > fic.bin

$no_ligne = 0 ;

while (<STDIN>) {

  $no_ligne++ ;
  
  chomp($_) ;
  
  # On supprime les espaces
  #
  $_ =~ s/\s+//g;

  # test de longueur impaire de la ligne
  #
  if ((length($_) % 2) == 1) {
  
    print STDERR "Erreur, ligne no $no_ligne avec nombre de digits impair.\n" ;
    
  } else {
  
    @f = ($_ =~ /[0-9a-f][0-9a-f]/gi) ;
    if (join('', @f) ne $_) {
      print STDERR "Erreur, ligne no $no_ligne avec des caractˆres inutilis‰s.\n" ;
    }
    else {
      foreach $v (@f) {

        print STDOUT pack("c", hex($v)) ;

      } # fin du foreach @f
    } # fin du test de caractˆres inutilis‰s
  } # fin du test de longueur impaire de la ligne

} # fin du while STDIN
