#!/usr/bin/perl

if (@ARGV < 2) {
  printf("usage: prepareForDmd.pl PDB ModelType\n");
  exit(1);
}

$RUN_UTIL_DIR = "runUtil";

#genetate the native file
$pdb2nat = "$RUN_UTIL_DIR/pdb2nat.linux";
system("$pdb2nat $ARGV[0] native");

#find the number of residues
my $line1 = `head -n 1 native`;
my @tmp = split(" ",$line1);
my $nRES = $tmp[0];

$SIZE = $nRES*3;
#generate the INIT.TXT file
$txtgene = "$RUN_UTIL_DIR/genDMD-TXT.linux";
$init_txt = "init.txt";
system("$txtgene $ARGV[0] $init_txt $SIZE 0 1.0");
