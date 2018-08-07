#!/usr/bin/perl

$RUN_UTIL_DIR = "runUtil";
$DMD_DIR = "dmd";
$PFOLD_UTIL_DIR = "pfoldUtil";

if (@ARGV<4) {
  printf("usage: calcPfold.pl origPDB deriPDB nRUN Tf\n");
  #printf("usage: calcPfold.pl origPDB deriPDB nRUN Tf randSeed\n");
  exit(1);
}
#input 
$origPDB = $ARGV[0];
$deriPDB = $ARGV[1];
$nSIM    = $ARGV[2];
$TF      = $ARGV[3];
#$randSeed= $ARGV[4];

#const
$randMAX = 999999999;

#definition
$size    = 500;
$HEAT_XC = 0.1;
$max_t   = 1000;

$nat_file = "$origPDB.nat";
system("$RUN_UTIL_DIR/pdb2nat.linux $origPDB $nat_file");

srand(time ^ $$);
#srand($randSeed);

$flag = "000";
$report = "$deriPDB\.report";
if (!open(REPORT,">$report")) {
  printf "can not open the report file";
  exit;
}

for (my $i=0; $i<$nSIM; $i++) {
  $flag++;
  $PREFIX="$deriPDB\.$flag";
  $start = $PREFIX . "\.inpt";
  $txt   = $PREFIX . "\.txt";
  $rmsf  = $PREFIX . "\.rms";
  #generate the random number
  $random = int(rand($randMAX));
  #print $random . "\n";
  #generate the input txt file
  `$PFOLD_UTIL_DIR/geneTXT.linux $origPDB $deriPDB $size $random > $txt`;
  #generate the start file
  create_input($start);
  #run simulation
  `env MALLOC_CHECK_=0 $DMD_DIR/dmd-en.linux < $start`;
  $txt0000 = $txt."0000";
  $rpdb    = $PREFIX . "\.pdb";
  getPDB($txt0000, $rpdb, $rmsd);
  reporting($rmsf, $rmsd);
}

close(REPORT);
$pfold = 0.0;
$pfold = `$PFOLD_UTIL_DIR/pfold.csh $report`;
`echo "Pfold Value: $pfold" >> $report`;

sub create_input{
  my $out_file = "$PREFIX.inpt";
  #my $out_file = $_[0];
  open(OUT,">$out_file");
  print OUT "$txt\n";
  print OUT "0 0 0\n";
  print OUT "n\n";
  print OUT "$PREFIX.rms\n";
  print OUT "n\n";
  print OUT "10\n";
  print OUT "n\n";
  print OUT "$nat_file\n";
  print OUT "y\n";
  print OUT "y\n";
  print OUT "n\n";
  print OUT "y\n";
  print OUT "n\n";
  print OUT "n\n";
  print OUT "y\n";
  print OUT "$PREFIX.txt\n";
  print OUT "n\n";
  print OUT "100000\n";
  print OUT "y\n";
  print OUT "n\n";
  print OUT "n\n";
  print OUT "10\n";
  print OUT "y\n";
  print OUT "$PREFIX.mov\n";
  print OUT "y\n";
  print OUT "y\n";
  print OUT "n\n";
  print OUT "y\n";
  print OUT "n\n";
  print OUT "$TF\n";
  print OUT "n\n";
  print OUT "$HEAT_XC\n";
  print OUT "n\n";
  print OUT "$TF\n";
  print OUT "y\n";
  print OUT "y\n";
  print OUT "$max_t\n";
  close(OUT);
}

sub getPDB{
  `$PFOLD_UTIL_DIR/txt2pdb.linux $_[0] $origPDB $_[1] 1\n`;
  $_[2]=`krms.linux $origPDB $_[1]`;
  chop($_[2]);
}

sub reporting{
  my($energy)=`$PFOLD_UTIL_DIR/lastE.scr $_[0]`;
  chop($energy);
  print REPORT ("$flag\t$energy\t$_[1]\n");
}


