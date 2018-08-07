#!/usr/bin/perl

if(@ARGV<3){
  printf("USAGE: run.pl DMD.linux(include path) [DMD-IN] [DMD-OUT]\n");
  exit(2);
}


if (@ARGV==3) {
  system("$ARGV[0] < $ARGV[1] > $ARGV[2]");
} 
else {
  my $dmd_argv;
  for (my $i=2; $i<@ARGV; $i++) {
    $dmd_argv .= "$ARGV[$i] "
  }
  #print  $dmd_argv . "\n";
  system("$ARGV[0] $dmd_argv < $ARGV[1]");
}
