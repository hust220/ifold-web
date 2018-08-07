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
	system("./gnuplot $OUTPUT_UTIL_DIR/EnergyvsTemp.plt");
  system("/usr/bin/convert -rotate 90 EnergyvsTemp.ps EnergyvsTemp.png; /bin/rm EnergyvsTemp.ps");

}

#read single atom from PDB
#======================================================================
sub parseAtomLine{
    my $line = shift;
    my %atom;
    $atom{temperature} = substr($line,20,6);
    $atom{energy} = substr($line,28,11);
    return %atom;
}

