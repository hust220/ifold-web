#!/usr/bin/perl

$DMD_DIR = "dmd";


#simAnneal.pl input_txt nIteration T0 HEAT_XC T1 TimePerIteration
if (@ARGV<6){
    printf("usage: simAnneal.pl input_txt nIteration T0 HEAT_XC T1 TimePerIteration\n");
    exit(1);
}

$dmd     = "env MALLOC_CHECK_=0 $DMD_DIR/dmd-en.linux";
$txt     = $ARGV[0];
$nIter   = $ARGV[1];
$temp0   = $ARGV[2];
$HEAT_XC = $ARGV[3];
$temp1   = $ARGV[4];
$max_t   = $ARGV[5];

$DT_RMS = 10;
$DT_TXT = 1000000;
$DT_MOV = 10;
$DT_ECHO = 10;

#temp0 the initial temperature
#temp1 the final tempearture
#HEAD_XC is the heat-exchange rate
$nat_file = "native";

for(my $iter=0; $iter<$nIter; $iter++){
    $PREFIX = sprintf("Iter%04d_T0%05.3f_XC%05.3f_T1%05.3f_MAXt%d",$iter,$temp0,$HEAT_XC,$temp1,$max_t);
    my $tmp_out = ".$PREFIX.input";
    &create_input($tmp_out,$iter);
    system("$dmd < $tmp_out > .$PREFIX.output");
		$txt = "$PREFIX.txt0000";
}

sub create_input{
  my $out_file = $_[0];
	my $start_time = $max_t*$_[1];
	my $max_sim_time = $max_t*($_[1]+1);
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
  print OUT "n\n";
	print OUT "$start_time\n";
  print OUT "n\n";
  print OUT "$temp0\n";
  print OUT "n\n";
  print OUT "$HEAT_XC\n";
  print OUT "n\n";
  print OUT "$temp1\n";
  print OUT "y\n";
  print OUT "y\n";
  print OUT "$max_sim_time\n";
  close(OUT);
}


