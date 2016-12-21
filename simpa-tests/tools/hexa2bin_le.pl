#!/usr/bin/env perl

# auteur : guerte yves
# date : 12/05/00
# utilisation : hexa_to_bin.pl < fic_hexa.txt > fic.bin

$no_ligne = 0 ;
@outbuf = () ;

while (<STDIN>) {

  $no_ligne++ ;
  
  chomp($_) ;
  
  # On supprime les espaces
  #
  $_ =~ s/\s+//g;

  # test de longueur impaire de la ligne
  #
  if ((length($_) % 2) == 1) {
  
    print STDERR "Erreur, ligne no $no_ligne de longueur impaire.\n" ;
    
  } else {
  
    @f = ($_ =~ /[0-9a-f][0-9a-f]/gi) ;
    if (join('', @f) ne $_) {
      print STDERR "Erreur, ligne no $no_ligne avec des caractˆres inutilis‰s.\n" ;
    }
    else {
    
      push(@outbuf, @f) ;
      if ($#outbuf >=3) {
        for ($i=0 ; $i <= ($#outbuf - 1) ; $i += 2) {
            my $s=$outbuf[$i] ;
            $outbuf[$i]=$outbuf[$i + 1] ;
            $outbuf[$i + 1]=$s ;
        }
        foreach $v (@outbuf) {

          print STDOUT pack("c", hex($v)) ;
      
        } # fin du foreach @f
        @outbuf = () ;
      } # fin du test de buffer >= 3
    } # fin du test de caractˆres inutilis‰s
  } # fin du test de longueur impaire de la ligne
} # fin du while STDIN
if ($#outbuf >= 0) {
        foreach $v (@outbuf) {

          print STDOUT pack("c", hex($v)) ;
      
        } # fin du foreach @f
}
