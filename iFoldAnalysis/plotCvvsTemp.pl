#!/usr/bin/perl

#  iFoldAnalysis v1.0
#
#  Copyright 2006 Shantanu Sharma, Feng Ding, Huifen Nie, Daniel Watson,
#  Aditya Unnithan, Jameson Lopp, Diane Pozefsky, Nikolay V. Dokholyan
#
#  Permission to use, copy, and distribute this software and its
#  documentation for any purpose with or without fee is hereby granted,
#  provided that the above copyright notice appear in all copies and
#  that both that copyright notice and this permission notice appear
#  in supporting documentation.
#
#  Permission to modify the software is granted, and also the right to
#  distribute the complete modified source code.  Modifications are to
#  be distributed as patches to the released version.  Permission to
#  distribute binaries produced by compiling modified sources is granted,
#  provided you
#    1. distribute the corresponding source modifications from the
#     released version in the form of a patch file along with the binaries,
#    2. add special version identification to distinguish your version
#     in addition to the base release version number,
#    3. provide your name and address as the primary contact for the
#     support of your modified version, and
#    4. retain our contact information in regard to use of the base
#     software.
#  Permission to distribute the released version of the source code along
#  with corresponding source modifications in the form of a patch file is
#  granted with same provisions 2 through 4 for binary distributions.
#
#  This software is provided "as is" without express or implied warranty
#  to the extent permitted by applicable law.
#


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
	system("./gnuplot $OUTPUT_UTIL_DIR/CvvsTemp.plt");
  system("/usr/bin/convert -rotate 90 CvvsTemp.ps CvvsTemp.png; /bin/rm CvvsTemp.ps");

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

