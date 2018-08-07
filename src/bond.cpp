#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
#include "bond.h"
using namespace std;

#define DIST(TMP,I,J) \
TMP=0;for(int k=0; k<3; k++)TMP+=(partxyz[I][k]-partxyz[J][k])* \
(partxyz[I][k]-partxyz[J][k]);TMP=sqrt(TMP);

#define RD(IN,TYPE, XYZ) \
IN >> TYPE;for(int ii=0; ii<3; ii++) IN >> XYZ[ii];


int main(){
  char file[20];
  cout << "Position Files should have four columes: \n"
       << "The first one is the amino acid name,\n" 
       << "Then followings are the xyz positon of CA or CB." << endl;
  
  cout << "Input file contains CA positions: ";
  cin >> file; 
  cout << endl;
  ifstream inCA(file);
  
  cout << "Input file contains CB positions: ";
  cin >> file; 
  cout << endl;
  ifstream inCB(file);
  
  int naa;
  cout << "Input the number of amino acids: ";
  cin >> naa;
  
  string type;
  int npart=0;
  double xyz[3];
  int caIndex[naa];
  int cbIndex[naa];
  int revIndex[naa*2];// +: CA; -; CB; 0: GLY
  double partxyz[2*naa][3];

  for(int i=0; i< naa; i++){
    RD(inCA, type, xyz);
    caIndex[i]=npart;
    revIndex[npart]=i+1;
    for(int j=0; j<3; j++)partxyz[npart][j]=xyz[j];
    npart++;
    if(type == "GLY"){
      //RD(inCB,type,xyz);
      npart--;
      cbIndex[i]=npart;
      revIndex[npart]=0;
      npart++;
    }
    else{
      RD(inCB, type, xyz);
      cbIndex[i]=npart;
      revIndex[npart]=-(i+1);
      for(int j=0; j<3; j++)partxyz[npart][j]=xyz[j];
      npart++;
    }
  }

  cout << "Total number of residues(CA&CB): " << npart <<endl;

  ofstream out1("mics.dat");
  out1 << "//A. CA index" << endl; 
  for( int i=0; i< naa; i++) 
    out1 << i+1 << "  " << caIndex[i]+1 <<endl;
  out1 << "//B. CB index" << endl; 
  for( int i=0; i< naa; i++) 
    out1 << i+1 << "  " << cbIndex[i]+1 <<endl;
  out1 << "//C. Reverse index" << endl; 
  for( int i=0; i< npart ; i++) 
    out1 << i+1 << "  " << revIndex[i] <<endl;

  double aved=0;
  for(int i=0; i< naa-1; i++){
    double dist=0;
    int ica=caIndex[i], ica1=caIndex[i+1];
    DIST(dist,ica,ica1);
    aved+=dist;
  }
  aved=aved/(naa-1);

  double unit;
  unit=10.0/aved;
  unit=1.0;
  

  out1 << "//D. The unit factor " << endl;
  out1 << unit << endl;

  for(int i=0; i< npart; i++)
    for(int j=0; j<3;j++) partxyz[i][j]=partxyz[i][j]*unit;
  
  double cm[3];
  for(int i=0; i<3;i++) cm[i]=0;

  for(int i=0; i< npart; i++)
    for(int j=0; j<3; j++) cm[j]+=partxyz[i][j];

  for(int i=0; i<3 ;i++)cm[i]=cm[i]/npart;

  for(int i=0; i< npart;i++)
    for(int j=0;j<3;j++)
      partxyz[i][j]=partxyz[i][j]-cm[3];

  out1 << "//E. Residues' positions(after zoom and shift)" << endl;
  ofstream NAT("nat");
  //NAT  << npart << " 1 " << 
  for(int i=0; i< npart; i++){
    for( int j=0; j <3; j++)out1 << partxyz[i][j] << " ";
    out1 << endl;
  }

  out1 << "//F. The connected paires"<< endl;
  for(int i=0; i < naa-1; i++){
    if(revIndex[caIndex[i]]!=0){

      int jcon=cbIndex[i];
      double dist=0;
      DIST(dist,caIndex[i],jcon);
      out1 << caIndex[i]+1 << "  " << jcon+1 
	   << "  " << dist <<endl;

      jcon= caIndex[i+1];
      DIST(dist,caIndex[i],jcon);
      out1 << caIndex[i]+1 << "  " << jcon+1 
	   << "  " << dist <<endl;
      
      if(revIndex[caIndex[i+1]]!=0){
	jcon= cbIndex[i+1];
	DIST(dist,caIndex[i],jcon);
	out1 << caIndex[i]+1 << "  " << jcon+1 
	     << "  " << dist <<endl;
      }
      
      if(i<naa-2){
	jcon= caIndex[i+2];
	DIST(dist,caIndex[i],jcon);
	out1 << caIndex[i]+1 << "  " << jcon+1 
	     << "  " << dist <<endl;
      }

      jcon= caIndex[i+1];
      DIST(dist,cbIndex[i],jcon);
      out1 << cbIndex[i]+1 << "  " << jcon+1 
	   << "  " << dist <<endl;
    
    }
    else{
      int jcon= caIndex[i+1];
      double dist=0;
      DIST(dist,caIndex[i],jcon);
      out1 << caIndex[i]+1 << "  " << jcon+1 
	   << "  " << dist <<endl;
      
      if(revIndex[caIndex[i+1]]!=0){
	jcon= cbIndex[i+1];
	DIST(dist,caIndex[i],jcon);
	out1 << caIndex[i]+1 << "  " << jcon+1 
	     << "  " << dist <<endl;
      }
      
      if(i<naa-2){
	jcon= caIndex[i+2];
	DIST(dist,caIndex[i],jcon);
	out1 << caIndex[i]+1 << "  " << jcon+1 
	     << "  " << dist <<endl;
      }
    }
  } 
  {
    int i=naa-1;
    int jcon=0;
    double dist=0;
    if(revIndex[caIndex[i]]!=0){
      jcon=cbIndex[i];
      DIST(dist,caIndex[i],jcon);
      out1 << caIndex[i]+1 << "  " << jcon+1 
	   << "  " << dist <<endl;
    }
  }
  
  double temp;
  int ica, icb;
  ofstream out("CA-CB.dist");
  for(int i=0; i < naa;  i++)if(revIndex[caIndex[i]]){ 
    ica=caIndex[i]; icb=cbIndex[i];
    DIST(temp,ica,icb);
    out << i+1 << " " << ica << " " << icb << " " << temp << endl;
  }

  ofstream out2("CB-CA'.dist");
  for(int i=0; i< naa; i++)if(revIndex[caIndex[i]]){
    if(i > 0 && i < naa-1){
      ica=caIndex[i-1];icb=cbIndex[i];
      DIST(temp,ica,icb);
      out2 << temp <<endl;

      ica=caIndex[i+1];icb=cbIndex[i];
      DIST(temp,ica,icb);
      out2 << temp <<endl;
    }
    else 
      if(i==0){
	ica=caIndex[i+1];icb=cbIndex[i];
	DIST(temp,ica,icb);
	out2 << temp <<endl;
      }
      else{
	ica=caIndex[i-1];icb=cbIndex[i];
	DIST(temp,ica,icb);
	out2 << temp <<endl;
      }
  }

  ofstream out3("CA-other.dist");
  double minDist=10000;
  for(int i=0; i< naa-3; i++){
    int startj;
    if(revIndex[caIndex[i+2]] !=0 ) 
      startj=cbIndex[i+2];
    else
      startj=caIndex[i+3];
    for(int j=startj; j< npart; j++){
      int ia=caIndex[i];
      DIST(temp,ia,j);
      out3 << temp << endl;
      if(temp < minDist) minDist = temp;
    }
  }
  cout << " The minimum distance between CA and other nonconnected atoms: " 
       << minDist << endl;
  
  ofstream out4("CB-otherCA.dist");
  for(int i=0; i< naa-2; i++){
    if(revIndex[cbIndex[i]]!=0){
      int ib=cbIndex[i];
      for(int j=i+2; j< naa; j++){
	int ia=caIndex[j];
	DIST(temp,ib,ia);
	out4 << temp << endl;
      }
    }
  }
  for(int i=2; i< naa; i++){
    if(revIndex[cbIndex[i]]!=0){
      int ib=cbIndex[i];
      for(int j=0; j< i-2; j++){
	int ia=caIndex[j];
	DIST(temp,ia,ib);
	out4 << temp << endl;
      }
    }
  }
  
  ofstream out5("CB-otherCB.dist");
  minDist=10000;
  for(int i=0; i< naa-1; i++){
    int ib1=cbIndex[i];
    for(int j=i+1; j< naa; j++){
      int ib2=cbIndex[j];
      if(revIndex[ib1]+1!=revIndex[ib2]){
	DIST(temp,ib1,ib2);
	out5 << i <<" "<< j << " " << temp << endl;
	if(minDist>temp) minDist=temp;
      }
    }
  }
  cout << " The minimum distance between CB and other CBs(no include GLY): " 
       << minDist << endl;
 
  cout << " Do you want to generate INPUT file(.txt file)? y[Yes]/n[No] " 
       << endl;
  char choose;
  cin >> choose;
  double cacbDev=0.0075, cacanDev=0.02, cacbnDev=0.034, cacannDev=0.08;
  double ener;
  
  switch(choose){
  case 'n':
    cout << " The program is closing! BYE-BYE " << endl;
    break;
  case 'y':
    cout << " Please choose the hard core diameter: ";
    double hcDiameter=0;
    cin >> hcDiameter;
    cout << " Input the file to save data with TXT style: " ;
    cin >> file;
    ofstream txtout(file);
    txtout << "//(simulation time 0)\n";
    txtout << "//length of search table (o currnet length)\n";
    
    txtout << "A.SYSTEM SIZE" <<endl;
    double size;
    cout << "What is the system size?" << endl;
    cin >> size;
    txtout<<size<<" "<<size<<" "<<size<<endl;

    NAT  << npart << " 1 " << size << endl;
    for(int i=0; i< npart; i++){
      for( int j=0; j <3; j++)NAT << partxyz[i][j] << " ";
      NAT << endl;
    }
    NAT.close();
    
    int ntotal;
    cout << "What is total number of particles(residues + ghostParticles)?"
	 <<endl;
    cin >> ntotal;
    txtout << "B.NUMBER OF ATOMS" << endl;
    txtout << ntotal <<endl;
    
    double mass=1.0;
    double hcRadius=hcDiameter/2;
    double cutoffD,cutoffR;
    cout << " What is the cutoff distance?(FOR CB in Anstrom)" <<endl;
    cin >> cutoffD;
    cutoffD=cutoffD*unit;
    cutoffR=cutoffD/2;
    txtout << "C.TYPES OF ATOMS" <<endl;
    txtout << "//type,mass,ellastic radius,interaction radius" <<endl;
    for(int i=0; i< npart+1; i++)
      txtout << i+1<<" "<< mass<<" "<< hcRadius<<" "<< cutoffR <<endl;
    
    txtout << "D.NON-ELASTIC COLLISIONS"<<endl;
    txtout <<"//pair types, repulsive dist, interaction distance, energy"
	   <<endl;
    for(int i=0; i< naa-1; i++){
      int ia=caIndex[i];
      int ib;
      
      if(revIndex[caIndex[i]]!=0){
	//the following code works on CA	
	ib=cbIndex[i];
	DIST(temp,ia,ib);
	txtout << ia+1 <<" "<< ib+1 << " " << temp*(1.0-cacbDev)<<endl;
	
	ib=caIndex[i+1];
	DIST(temp,ia,ib);
	txtout << ia+1 <<" "<< ib+1 << " " << temp*(1.0-cacanDev)<<endl;
	
	ib=cbIndex[i+1];
	if(revIndex[ib]!=0){
	  DIST(temp,ia,ib);
	  txtout << ia+1 <<" "<< ib+1 <<" "<< temp*(1.0-cacbnDev)<<endl;
	}
	
	if(i<naa-2){
	  ib=caIndex[i+2];
	  DIST(temp,ia,ib);
	  txtout << ia+1 <<" "<< ib+1 <<" "<< temp*(1.0-cacannDev)<<endl;
	  
	  int start;
	  if(revIndex[caIndex[i+2]]!=0)
	    start=cbIndex[i+2];
	  else
	    start=cbIndex[i+2]+1;
	  for(int j=start; j< npart;j++){ 
	    DIST(temp,ia,j);
	    txtout << ia+1 <<" "<< j+1 <<" "<< hcDiameter<<endl;
	  }
	}
	ib=cbIndex[i];
	// the follwing code works on CB
	ia=caIndex[i+1];
	if(revIndex[ia]!=0){
	  DIST(temp,ib,ia);
	  txtout << ib+1 <<" "<< ia+1 <<" "<< temp*(1.0-cacbnDev)<<endl;
	  
	  ia=cbIndex[i+1];
	  DIST(temp,ib,ia);
	  txtout << ib+1 <<" "<< ia+1 <<" "<<hcDiameter<< endl;
	}
	else{
	  ia=cbIndex[i+1];
	  DIST(temp,ib,ia);
	  txtout << ib+1 <<" "<< ia+1 <<" "<<hcDiameter<< endl;
	}
	if(i<naa-2){
	  for(int j=i+2;j<naa;j++){
	    if(revIndex[caIndex[j]]!=0){
	      ia=caIndex[j];
	      DIST(temp,ib,ia);
	      txtout<< ib+1<<" "<<ia+1<<" "<< hcDiameter<<endl;
	      
	      ia=cbIndex[j];
	      DIST(temp,ib,ia);
	      if(temp<cutoffD)ener=-1.0;
	      else ener=1.0;
	      txtout<< ib+1<<" "<<ia+1<<" "<<hcDiameter<<" "<<cutoffD<<" "
		    <<ener<<endl;
	    }
	    else{
	      ia=cbIndex[j];
	      DIST(temp,ib,ia);
	      if(temp<cutoffD)ener=-1.0;
	      else ener=1.0;
	      txtout<< ib+1<<" "<<ia+1<<" "<<hcDiameter<<" "<<cutoffD<<" "
		    <<ener<<endl;
	    }
	  }
	}
      }
      else{
	ib=caIndex[i+1];
	DIST(temp,ia,ib);
	txtout << ia+1 <<" "<< ib+1 << " " << temp*(1.0-cacanDev)<<endl;
	
	if(revIndex[caIndex[i+1]]!=0){
	  ib=cbIndex[i+1];
	  DIST(temp,ib,ia);
	  if(temp< cutoffD)ener=-1.0;
	  else ener=1.0;
	  txtout << ia+1 <<" "<< ib+1 <<" "<< hcDiameter << endl;
	}
	
	if(i<naa-2){
	  for(int j=i+2;j<naa;j++){
	    if(revIndex[caIndex[j]]!=0){
	      ib=caIndex[j];
	      DIST(temp,ib,ia);
	      txtout<< ia+1<<" "<<ib+1<<" "<< hcDiameter<<endl;
	      
	      ib=cbIndex[j];
	      DIST(temp,ib,ia);
	      if(temp<cutoffD)ener=-1.0;
	      else ener=1.0;
	      txtout<< ia+1<<" "<<ib+1<<" "<<hcDiameter<<" "<<cutoffD<<" "
		    <<ener<<endl;
	    }
	    else{
	      ib=cbIndex[j];
	      DIST(temp,ib,ia);
	      if(temp<cutoffD)ener=-1.0;
	      else ener=1.0;
	      txtout<< ia+1<<" "<<ib+1<<" "<<hcDiameter<<" "<<cutoffD<<" "
		    <<ener<<endl;
	    }
	  }
	}	
      }
    }    
    if(caIndex[naa-1]!=cbIndex[naa-1]){
      DIST(temp,caIndex[naa-1],cbIndex[naa-1]);
      txtout << caIndex[naa-1]+1<<" "<<cbIndex[naa-1]+1<<" "
	     <<temp*(1.0-cacbDev)<<endl;
    }

    txtout<< "E.ELASTIC COLLISIONS"<<endl;
    txtout<< "//pair types, repulsive dist"<<endl;
    for(int i=0; i<npart;i++)txtout << i+1<<" "<<i+1<<" "<<hcDiameter<<endl;
    for(int i=0; i<npart;i++)txtout<< npart+1 <<" "<< i+1<<" "
				   <<hcDiameter<<endl;
    //the collision between ghostparticles can be reduced when the number of 
    //ghostparticles increase
    txtout << npart+1 << " "<< npart+1 <<" "<< hcDiameter/2<< endl;

    txtout<< "F.LINKED PAIRS"<<endl;
    txtout<<"//pair types, repulsive dist, attractive distace"<<endl;
    
    for(int i=0; i < naa-1; i++){
      if(revIndex[caIndex[i]]!=0){
	int jcon=cbIndex[i];
	double dist=0;
	DIST(dist,caIndex[i],jcon);
	txtout << caIndex[i]+1 << "  " << jcon+1 << "  " << dist*(1.0-cacbDev)
	       <<" " << dist*(1.0+cacbDev) <<endl;
	
	jcon= caIndex[i+1];
	DIST(dist,caIndex[i],jcon);
	txtout << caIndex[i]+1 << "  " << jcon+1 << "  " 
	       << dist*(1.0-cacanDev)<< " " << dist*(1.0+cacanDev) <<endl;
	
	if(revIndex[caIndex[i+1]]!=0){
	  jcon= cbIndex[i+1];
	  DIST(dist,caIndex[i],jcon);
	  txtout << caIndex[i]+1 << "  " << jcon+1 << "  " 
		 << dist*(1.0-cacbnDev)<< " " << dist*(1.0+cacbnDev) <<endl;
	}
	
	if(i<naa-2){
	  jcon= caIndex[i+2];
	  DIST(dist,caIndex[i],jcon);
	  txtout << caIndex[i]+1 << "  " << jcon+1 << "  " 
		 << dist*(1.0-cacannDev)<< " " << dist*(1.0+cacannDev) <<endl;
	}
	
	jcon= caIndex[i+1];
	DIST(dist,cbIndex[i],jcon);
	txtout << cbIndex[i]+1 << "  " << jcon+1 << "  " 
	       << dist*(1.0-cacbnDev)<< " " << dist*(1.0+cacbnDev) <<endl;
	
      }
      else{
	int jcon= caIndex[i+1];
	double dist=0;
	DIST(dist,caIndex[i],jcon);
	txtout << caIndex[i]+1 << "  " << jcon+1 << "  " 
	       << dist*(1.0-cacanDev)<< " " << dist*(1.0+cacanDev) <<endl;
	
	if(revIndex[caIndex[i+1]]!=0){
	  jcon= cbIndex[i+1];
	  DIST(dist,caIndex[i],jcon);
	  txtout << caIndex[i]+1 << "  " << jcon+1 << "  " 
		 << dist*(1.0-cacbnDev)<< " " << dist*(1.0+cacbnDev) <<endl;
	}
	
	if(i<naa-2){
	  jcon= caIndex[i+2];
	  DIST(dist,caIndex[i],jcon);
	  txtout << caIndex[i]+1 << "  " << jcon+1 << "  " 
		 << dist*(1.0-cacannDev)<< " " << dist*(1.0+cacannDev) <<endl;
	}
      }
    }    
    {
      int i=naa-1;
      int jcon=0;
      double dist=0;
      if(revIndex[caIndex[i]]!=0){
	jcon=cbIndex[i];
	DIST(dist, caIndex[i], jcon);
	txtout << caIndex[i]+1 << "  " << jcon+1 << "  " << dist*(1.0-cacbDev)
	       << " " << dist*(1.0+cacbDev) <<endl;
      }
    }
 
    txtout << "G.REACTIONS" <<endl;
    txtout << "//old1,old2,new1,new2,bond,radius energy" <<endl;
    
    double vxyz[ntotal][3],vcm[3];
    int idum;
    double Temp=1.0;
    idum=-17;
    ran1(&idum);
    for(int i=0; i<npart; i++)
      for(int j=0; j<3; j++) partxyz[i][j]+=size/2;

    for(int i=0; i<3; i++)
      for(int j=0; j<ntotal;j++) vxyz[j][i] = gasdev(&idum)*sqrt(2.0f*Temp);
    for(int i=0; i<3; i++)vcm[i]=0;
    for(int i=0; i<3; i++)
      for(int j=0; j<ntotal; j++) vcm[i]+=vxyz[j][i];
    for(int i=0; i<3; i++)vcm[i]=vcm[i]/ntotal;
    for(int i=0; i<3; i++)
      for(int j=0; j<ntotal; j++) vxyz[j][i]=vxyz[j][i]-vcm[i];
    
    double xmin=10000, xmax=-10000;
    double ymin=10000, ymax=-10000;
    double zmin=10000, zmax=-10000;
    for(int i=0; i< npart; i++){
      if(partxyz[i][0] > xmax) 
	xmax=partxyz[i][0];
      else 
	if(partxyz[i][0] < xmin)
	  xmin=partxyz[i][0];
      
      if(partxyz[i][1] > ymax) 
	ymax=partxyz[i][1];
      else 
	if(partxyz[i][1] < ymin)
	  ymin=partxyz[i][1];
      
      if(partxyz[i][2] > zmax) 
	zmax=partxyz[i][2];
      else 
	if(partxyz[i][2] < zmin)
	  zmin=partxyz[i][2];
    }    

    double ghostxyz[ntotal-npart][3];
    
    int count=0;
    double x,y,z;
    bool goon= true;
    int nstp;
    double stp,hstp;
    nstp=(int)exp(log((float)ntotal)/3.0F)+1;
    stp=size/nstp;
    hstp=stp/2.0f;
    for(int nz=0; nz<nstp; nz++)
      for(int ny=0; ny<nstp; ny++)
	for(int nx=0; nx<nstp; nx++){
	  if(goon){
	    x=nx*stp+hstp;
	    y=ny*stp+hstp;
	    z=nz*stp+hstp;
	    if(x > (xmin-hcDiameter) && x < (xmax+hcDiameter) &&
	       y > (ymin-hcDiameter) && y < (ymax+hcDiameter) &&
	       z > (zmin-hcDiameter) && z < (zmax+hcDiameter));
	    else {
	      count++;
	      if(count <= ntotal-npart){
		ghostxyz[count-1][0]=x;
		ghostxyz[count-1][1]=y;
		ghostxyz[count-1][2]=z;
	      }
	      else goon=false;
	    }
	  }
	}
    
    txtout << "H.LIST OF ATOMS" <<endl;
    txtout << "//number, type, x, y, z, Vx, Vy, Vz" << endl;
    for( int i=0; i< npart; i++){
      double vx,vy,vz;
      vx=vxyz[i][0];
      vy=vxyz[i][1];
      vz=vxyz[i][2];
      txtout << i+1 <<" "<< i+1 <<" "<<partxyz[i][0]<<" "<<partxyz[i][1]
	     <<" "<<partxyz[i][2]<<" "<<vx<<" "<<vy<<" "<<vz<<endl;
    }
    for(int i=npart; i<ntotal;i++){
      double vx,vy,vz;
      x=ghostxyz[i-npart][0];
      y=ghostxyz[i-npart][1];
      z=ghostxyz[i-npart][2];
      vx=vxyz[i][0];
      vy=vxyz[i][1];
      vz=vxyz[i][2];
      txtout << i+1<<" "<<npart+1<<" "<<x<<" "<<y<<" "<<z
	     <<" "<<vx<<" "<<vy<<" "<<vx<<endl;
    }
    
    txtout<<"I.LIST OF BONDS"<<endl;
    txtout<<"//number1, number2"<<endl;
    for(int i=0; i<naa-1;i++){
      if(caIndex[i]!=cbIndex[i])
	txtout<<caIndex[i]+1<<" "<<cbIndex[i]+1<<endl;
      
      txtout<<caIndex[i]+1<<" "<<caIndex[i+1]+1<<endl;
      
      if(caIndex[i+1]!=cbIndex[i+1])
	txtout<<caIndex[i]+1<<" "<<cbIndex[i+1]+1<<endl;
      
      if(i<naa-2)
	txtout<<caIndex[i]+1<<" "<<caIndex[i+2]+1<<endl;
      
      if(caIndex[i]!=cbIndex[i])
	txtout <<cbIndex[i]+1<<" "<<caIndex[i+1]+1<<endl;
    }
    if(caIndex[naa-1]!=cbIndex[naa-1])
      txtout<< caIndex[naa-1]+1<< " "<<cbIndex[naa-1]+1<<endl;
    break;
  }
}

