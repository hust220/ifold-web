#!/usr/bin/perl

$OUTPUT_UTIL_DIR = "outputUtil";

#main function
{

  if (@ARGV<6) {
    printf("usage: getTraj.pl movfile PDBfile startNo endNo Interval ModelType\n");
    exit(1);
  }

  $mov = $ARGV[0];
	$origPDB = $ARGV[1];
	$start = (1+ $ARGV[2])/10;
	$end = (0+ $ARGV[3])/10;
	$interval = (0+ $ARGV[4]);
	$modelType = $ARGV[5];
  
	printf($interval."\n");

	my $mod;
 
	if($modelType=="2" || $modelType=="1"  ){
	  $mod = 2;
	}
	else { 
	  $mod = 4;
	}

  $nframe = ($end - $start)/$interval + 1;

  system("$OUTPUT_UTIL_DIR/movie2pdbs.linux $mov $origPDB Trajectory.pdb $mod 1 $start $nframe");
  #system("zip -r Trajectory.pdb.zip Trajectory.pdb");
  #system("rm -f Trajectory.pdb");
	
}

