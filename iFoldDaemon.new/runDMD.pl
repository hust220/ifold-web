#!/usr/bin/perl

$DMD_DIR = "dmd";

if (@ARGV<5) {
  printf("usage: runDMD.pl input_txt T0 HEAT_XC T1 max_Time\n");
  printf(" dmd_path : the path to the dmd-executable\n");
  printf(" input_txt: the initial text file\n");
  printf(" T0 : the initial temperature for the simulation\n");
  printf(" HEAT_XC : the thermal exchange coefficient of the simulation\n");
  printf(" T1 : the final temperature for the simulation\n");
  printf(" max_Time : the maximum simulation time\n");
  exit(1);
}

$dmd     = "env MALLOC_CHECK_=0 ".$DMD_DIR."/dmd-en.linux";
$txt     = $ARGV[0];
$temp0   = $ARGV[1];
$HEAT_XC = $ARGV[2];
$temp1   = $ARGV[3];
$max_t   = $ARGV[4];

$DT_RMS = 10;
$DT_TXT = 10000;
$DT_MOV = 10;
$DT_ECHO = 10;

#temp0 the initial temperature
#temp1 the final tempearture
#HEAD_XC is the heat-exchange rate
$nat_file = "native";

$PREFIX = sprintf("T0%05.3f_XC%05.3f_T1%05.3f_MAXt%d",$temp0,$HEAT_XC,$temp1,$max_t);
#print $PREFIX . "\n";

# For folding simulations:
if($temp0<$temp1) {
	my $tmp_out = ".$PREFIX.input";
	# First unfold the input rapidly and then perform the folding simulation on resultant trajectory:
	&fast_unfold($tmp_out);
	system("$dmd < $tmp_out > .$PREFIX.fastunfold");
	system("mv $PREFIX.txt0001 $tmp_out");
	&create_input($tmp_out);
	
	system("bsub -m ifold_nodes runOnCluster.pl $dmd  $tmp_out  .$PREFIX.output");
	
}

#For unfolding simulations:
else {
	my $tmp_out = ".$PREFIX.input";
	&create_input($tmp_out);
	system("$dmd < $tmp_out > .$PREFIX.output");
}


sub fast_unfold{
  my $out_file = $_[0];
  open(OUT,">$out_file");
  print OUT "$txt\n";
  print OUT "0 0 0\n";
  print OUT "y\n";
  print OUT "n\n";
  print OUT "n\n";
  print OUT "y\n";
  print OUT "n\n";
  print OUT "n\n";
  print OUT "y\n";
  print OUT "$PREFIX.txt\n";
  print OUT "n\n";
  print OUT "1000\n";
  print OUT "y\n";
  print OUT "y\n";
	print OUT "y\n";
	print OUT "n\n";
	print OUT "1.2\n";
	print OUT "n\n";
	print OUT "0.5\n";
  print OUT "y\n";
  print OUT "y\n";
  print OUT "y\n";
	print OUT "1000\n";
  close(OUT);
}

sub create_input{
  my $out_file = $_[0];
  open(OUT,">$out_file");
  print OUT "$txt\n";
  print OUT "0 0 0\n";
  print OUT "n\n";
  print OUT "$PREFIX.rms\n";
  print OUT "n\n";
  print OUT "$DT_RMS\n";
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
  print OUT "$DT_TXT\n";
	
	print OUT "n\n";
  print OUT "y\n";
  print OUT "$PREFIX.echo\n";
	print OUT "n\n";
	print OUT "$DT_ECHO\n";
	
  # print OUT "y\n";
  
	print OUT "n\n";
  print OUT "n\n";
  print OUT "$DT_MOV\n";
  print OUT "y\n";
  print OUT "$PREFIX.mov\n";
  print OUT "y\n";
  print OUT "y\n";
  print OUT "n\n";
  print OUT "y\n";
  print OUT "n\n";
  print OUT "$temp0\n";
  print OUT "n\n";
  print OUT "$HEAT_XC\n";
  print OUT "n\n";
  print OUT "$temp1\n";
  print OUT "y\n";
  print OUT "y\n";
  print OUT "$max_t\n";
  close(OUT);
}
