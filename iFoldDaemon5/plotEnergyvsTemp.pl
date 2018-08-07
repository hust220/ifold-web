#!/usr/bin/perl

#main function
{

	$OUTPUT_UTIL_DIR = "outputUtil";

  if (@ARGV<1) {
    printf("usage: plotEnergyvsTemp.pl echofile\n");
    exit(1);
  }

  open(echofile,"$ARGV[0]") || die "couldn't open the echo file!";

  my %snapshot;
#  my ($chain_id,$max_res,$min_res,$non_seq_flag,$res,$last_res);
  my $snap_idx;
  my @trajectory;
  my $first_pass = 1;

  while(<echofile>){
  
    %snapshot = &parseAtomLine($_);
    push @trajectory, {%snapshot};

  }#while ECHOFILE

  close(echofile);

  open(energyout,">  EnergyvsTemp.dat") || die "couldn't open the energy data file!";
	
	# Number of snapshots:
  $numsnaps = @trajectory;

	for($snap_idx=1; $snap_idx<$numsnaps; $snap_idx++){
	  print energyout "$trajectory[$snap_idx]{temperature} $trajectory[$snap_idx]{energy}\n";
	}
  close(enegyout);
	system("/usr/bin/gnuplot $OUTPUT_UTIL_DIR/EnergyvsTemp.plt");

}

#read single atom from PDB
#======================================================================
sub parseAtomLine{
    my $line = shift;
    my %atom;

#    $atom{simtime} = substr($line,3,10);
    $atom{temperature} = substr($line,20,6);
    $atom{energy} = substr($line,28,11);
#    $atom{radius} = substr($line,42,15);
#    $atom{pressure} = substr($line,61,15);


    return %atom;
}

