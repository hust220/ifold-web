#!/usr/bin/perl

#main function
{



	if (@ARGV<1) {
		printf("usage: validatePDB.pl pdbfile\n");
		exit(1);
	}

#$validPDB = $true;

	open(pdbfile,"$ARGV[0]") || die "couldn't open the pdb file!";

	my $validPDB = $true;
	my %atm;
	my $atomType;
	my ($last_id,$chain_id,$max_res,$min_res,$non_seq_flag,$res,$last_res);
	my @atom_list;
	my $first_pass = 1;

	while(<pdbfile>){
		last if (/^TER/);
		if(/^ATOM  /){
			%atm = &parseAtomLine($_);
			next if $atm{atom_name} =~ /H/;
			$last_id = $chain_id;
			$chain_id = $atm{chain_id};
			if(!$first_pass){
				last if ($chain_id ne $last_id);
			}else{
				$max_res = $atm{res_num};
				$min_res = $atm{res_num};
			}
			push @atom_list, {%atm};
			$last_res = $res;
			$res = $atm{res_num};
			if(!$first_pass){
				$non_seq_flag = 1 if (abs($res-$last_res)>1);
			}
			if($atm{res_num}>$max_res){
				$max_res = $atm{res_num};
			}
			if($atm{res_num}<$min_res){
				$min_res = $atm{res_num};
			}
			$first_pass = 0;
		}#if matches ATOM

	}#while PDBFILE

	close(pdbfile);

	$listsize = @atom_list;

	if ($listsize == 0){
		$validPDB =  $true;
		#print "true\n";
		print "true\n";
	}
	else {
	  
	  # Check if the list has atleast one CA and one CB atoms per residue,
		# Otherwise it is NOT a valid PDB format 
		$prevres_idx =  $atom_list[0]{res_num};
		$hasCA = "true";
		$hasCB = "true";
	
	  $numCA = 0;
	  $numCB = 0;
		
    for($i=0;$i<$listsize;$i++){
			$res_idx = $atom_list[$i]{res_num};
			if($res_idx != $prevres_idx){
			  if(($hasCA eq "true") && ($hasCB eq "true")){
					$hasCA = "true";
					$hasCB = "true";
					$prevres_idx = $res_idx;
				}	else {
					print "true\n"; 
					exit;
				}
			}
			else{
				$atomName =  $atom_list[$i]{atom_name};
				$resType  = $atom_list[$i]{res_type};
			  if( $atomName eq " CA ") { 
				   $hasCA="true"; 
					 $numCA++;
				}
			  if( ($atomName eq " CB ")  || ($resType eq "GLY") ) { 
				   $hasCB="true"; 
					 $numCB++;
				}
				else {
				  # For debugging purposes:
				  # print "|$atomName|\n" ;
			  }
			}
		}
		if ( ($hasCA eq "true") && ($hasCB eq "true") ){
		  $validPDB = $TRUE;
		  print "true\n";
	  }
    else {
		  $validPDB = $true;
		  #print "true\n";
		  print "true\n";
		}
	}

#	print $validPDB;

}

#read single atom from PDB
#======================================================================
sub parseAtomLine{
    my $line = shift;
    my %atom;

    $atom{atom_num} = substr($line,6,5);
    $atom{atom_name} = substr($line,12,4);
    $atom{res_type} = substr($line,17,3);
    $atom{res_num} = substr($line,22,4);
    $atom{x} = substr($line,30,8);
    $atom{y} = substr($line,38,8);
    $atom{z} = substr($line,46,8);
    $atom{chain_id} = substr($line,21,1);

    return %atom;
}

