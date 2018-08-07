#!/usr/bin/perl

#main function
{

$OUTPUT_UTIL_DIR = "outputUtil";

  if (@ARGV<3) {
    printf("usage: plotCvvsTemp.pl equllibration_offset echofile1 echofile2 [echofile3 ...echofilen]\n");
    exit(1);
  }

  my $filenum;

  my @CvvsTempData;

  for($filenum=1;$filenum<@ARGV; $filenum++){

    open(echofile,"$ARGV[$filenum]") || die "couldn't open the echo file!";

		my %snapshot;
		my $snap_idx;
		
		my $thisE;
		my $thisTemp;
		my $thisTime;
		my $meanE;
		my $meanTemp;
		my $meanEsq;
		
		my $cv;
		
		my $eq_offset =  0+ @ARGV[0];
		my @trajectory;

		while(<echofile>){

			%snapshot = &parseAtomLine($_);

			$thistime  = 0+ $snapshot{simtime};
			if($thistime > $eq_offset){
				push @trajectory, {%snapshot};
				#print "$thistime \n";
		  }

		}#while ECHOFILE

		close(echofile);
	
		# Compute heat capacity
	
		# Number of snapshots:
  	$numsnaps = @trajectory;

		for($snap_idx=1; $snap_idx<$numsnaps; $snap_idx++){
		  $thisE = 0+ $trajectory[$snap_idx]{energy};
		  $thisTemp = 0+ $trajectory[$snap_idx]{temperature};
			
      $meanE   += $thisE;
      $meanEsq += $thisE*$thisE;

			$meanTemp += $thisTemp;
		}

		$meanE = $meanE/$numsnaps;
		$meanTemp = $meanTemp/$numsnaps;
		$meanEsq = $meanEsq/$numsnaps;

    $cv = ($meanEsq - $meanE*$meanE)/$meanTemp;

    # One Cv vs Temp data point:
    my %datapt;
		$datapt{Cv} = $cv;
		$datapt{temp} = $meanTemp;
	  push @CvvsTempData, {%datapt};

  }





  open(cvout,">  CvvsTemp.dat") || die "couldn't open the Cv data file for writing!";
	
	# Number of snapshots:
  $numdatapts = @CvvsTempData;

	for($idx=1; $idx<$numdatapts; $idx++){
	  print cvout "$CvvsTempData[$idx]{temp} $CvvsTempData[$idx]{Cv}\n";
	}
  close(cvout);
	system("/usr/bin/gnuplot $OUTPUT_UTIL_DIR/CvvsTemp.plt");

}

#read single atom from PDB
#======================================================================
sub parseAtomLine{
    my $line = shift;
    my %atom;

    $atom{simtime} = substr($line,3,10);
    $atom{temperature} = substr($line,20,6);
    $atom{energy} = substr($line,28,11);

    return %atom;
}

