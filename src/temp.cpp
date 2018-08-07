#include "PDBLib-NChain.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cmath>
using namespace std;

float ran1(int*);
float gasdev(int*);

int main(int argc, char* argv[]){
  if(argc<6){
    printf("usage: genDMD-TXT.linux pdb txt box_size nGhost rGost\n");
    exit(1);
  }
  
  protein p(argv[1]);
  int nchain, start, length;
  nchain = p.getNChains();
  ofstream txtout(argv[2],ios::out);
  double size = atof(argv[3]);
  int nGhost = atol(argv[4]);
  double rGhost = atof(argv[5]);
  const double hcDiameter = 3.70;
  const double cutoffD    = 7.50;
  
  cout << "Chains:" << endl;
  for(int i=0; i<nchain; i++){
    p.getChainInfor(i,start,length);
    cout << i+1 << " "  << start << " " << length << endl;
  }
  //.printCM(cout, "CB", 7.5);

  int npart=0;
  for(int i=0; i<p.getLength(); i++){
    if(p.getElementAt(i)->getName()=="GLY") npart+=1;
    else npart+=2;//has cb
  }
  cout << "Total part:" <<  npart << endl;
  double partxyz[npart][3];

  //calculate the minimum pairwise distances between
  //non-bonded atoms
  double min_dist=100000.0, dist;
  for(int i=0; i<p.getLength(); i++){
    aa* theAA = p.getElementAt(i);
    atom* theCA = theAA->getAtomAt(0);
    atom* theCB = NULL;
    if(theAA->getName()!="GLY") theCB = theAA->getAtomAt(1);
    //i,i+1
    if(i+1<p.getLength()){
      if(p.getElementAt(i+1)->getName()!="GLY" && theCB){
    	atom* nxtCB = p.getElementAt(i+1)->getAtomAt(1);
    	dist = theCB->getDist(*nxtCB);
    	if(dist < min_dist) min_dist = dist;
      }
    }
    //i,i+2
    if(i+2<p.getLength()){
      atom* nxtCA = p.getElementAt(i+2)->getAtomAt(0);
      if(theCB){
    	dist = theCB->getDist(*nxtCA);
    	if(dist < min_dist) min_dist = dist;
      }
      if(p.getElementAt(i+2)->getName()!="GLY"){
    	atom* nxtCB = p.getElementAt(i+2)->getAtomAt(1);
    	dist = theCA->getDist(*nxtCB);
    	if(dist < min_dist) min_dist = dist;
    	if(theCB){
    	  dist = theCB->getDist(*nxtCB);
    	  if(dist < min_dist) min_dist = dist;
    	}
      }
    }
    for(int j=i+3; j<p.getLength(); j++){
      aa* nxtAA = p.getElementAt(j);
      atom* nxtCA = nxtAA->getAtomAt(0);
      atom* nxtCB = NULL;
      if(nxtAA->getName()!="GLY") nxtCB = nxtAA->getAtomAt(1);
      dist = theCA->getDist(*nxtCA);
      if(dist < min_dist) min_dist = dist;
      if(theCB){
      	dist = theCB->getDist(*nxtCA);
      	if(dist < min_dist) min_dist = dist;
      	if(nxtCB){
      	  dist = theCB->getDist(*nxtCB);
      	  if(dist < min_dist) min_dist = dist;
      	}
      }
      if(nxtCB){
	dist = theCA->getDist(*nxtCB);
	if(dist < min_dist) min_dist = dist;
      }
    }
  }
  //cout << "MIN DIST: " << min_dist << endl;

  //output the DMD-txt using simple go model with CA-CB representation
  
  txtout << "A.SYSTEM SIZE" <<endl;
  txtout<<size<<" "<<size<<" "<<size<<endl;
  
  int ntotal = npart + nGhost;
  txtout << "B.NUMBER OF ATOMS" << endl;
  txtout << ntotal <<endl;

  double hcRadius = hcDiameter/2.0;
  double cutoffR  = cutoffD/2.0;
  double hD = min_dist-0.1;
  double hR = hD/2.0;
	if(hD>hcDiameter){hD=hcDiameter-0.1;}

  //indexing/typing the atoms
  int index=0;
  for(int i=0; i<p.getLength(); i++){
    aa* theAA = p.getElementAt(i);
    atom* theCA = theAA->getAtomAt(0);
    partxyz[index][0]=theCA->getR()->getX();
    partxyz[index][1]=theCA->getR()->getY();
    partxyz[index][2]=theCA->getR()->getZ();
    theCA->setIndex(++index);
    atom* theCB = NULL;
    if(theAA->getName()!="GLY"){
      theCB = theAA->getAtomAt(1);
      partxyz[index][0]=theCB->getR()->getX();
      partxyz[index][1]=theCB->getR()->getY();
      partxyz[index][2]=theCB->getR()->getZ();
      theCB->setIndex(++index);
    }
  }
  
  double mass=1.0;
  int ca1 = 1;
  int ca2 = 2;
  txtout << "C.TYPES OF ATOMS" <<endl;
  //for(int i=0; i< npart; i++)
  //txtout<<i+1<<" "<<mass<<" "<<hR<<" "<< cutoffR <<endl;
  txtout << ca1 << " " << mass << " " << hR << " " << cutoffR << endl;
  txtout << ca2 << " " << mass << " " << hR << " " << cutoffR << endl;
  for(int i=0; i<p.getLength(); i++){
    txtout << i+3 << " " << mass << " " << hR << " " << cutoffR << endl;
  }
  txtout<<p.getLength()+3<<" "<<mass<<" "<<rGhost<<" "<<cutoffR<<endl;
  
  const double ener = 10;
  const double eINF = 10000;

  txtout<<"D.NON-ELASTIC COLLISIONS"<<endl;
  //CA-CA
  txtout << ca1 << " " << ca1 << " " << hD << " " << hcDiameter << " 10.0" << endl;
  txtout << ca1 << " " << ca2 << " " << hD << " " << hcDiameter << " 10.0" << endl;
  txtout << ca2 << " " << ca2 << " " << hD << " " << hcDiameter << " 10.0" << endl;
  //CA-CB
  for(int i=0; i<p.getLength(); i++){
    txtout << ca1 << " " << i+3 << " " << hD << " " << hcDiameter << " 10.0" << endl;
    txtout << ca2 << " " << i+3 << " " << hD << " " << hcDiameter << " 10.0" << endl;
  }

  for(int i=0; i<p.getLength(); i++){
    aa* theAA = p.getElementAt(i);
    atom* theCA = theAA->getAtomAt(0);
    atom* theCB = NULL;
    if(theAA->getName()!="GLY") theCB = theAA->getAtomAt(1);
    //i,i+1
    if(i+1<p.getLength()){//CB-CB repulsion
      if(p.getElementAt(i+1)->getName()!="GLY" && theCB){
    	atom* nxtCB = p.getElementAt(i+1)->getAtomAt(1);
    	dist = theCB->getDist(*nxtCB);
	txtout<<i+3<<" "<<i+4<<" "
	      <<hD<<" "<<hcDiameter<<" 10.0 "<<endl;
      }
    }
    //i,i+2
    if(i+2<p.getLength()){
      atom* nxtCA = p.getElementAt(i+2)->getAtomAt(0);
      if(p.getElementAt(i+2)->getName()!="GLY"){
    	if(theCB){
    	  //dist = theCB->getDist(*nxtCB);
	  txtout<<i+3<<" "<<i+5<<" "
		<<hD<<" "<<hcDiameter<<" 10.0 "<<endl;
	  
    	}
      }
    }
    for(int j=i+3; j<p.getLength(); j++){
      aa* nxtAA = p.getElementAt(j);
      atom* nxtCA = nxtAA->getAtomAt(0);
      atom* nxtCB = NULL;
      if(nxtAA->getName()!="GLY") nxtCB = nxtAA->getAtomAt(1);
      if(theCB){
      	if(nxtCB){
      	  dist = theCB->getDist(*nxtCB);
	  if(dist<cutoffD){
	    /*txtout<<i+3<<" "<<j+3<<" "
	      <<hD<<" "<<hcDiameter<<" 10.0 "<<cutoffD<<" -1.0"<<endl;*/
	    txtout<<i+3<<" "<<j+3<<" "<<hD<<" "
		  <<hcDiameter<<" "<<ener<<" "
		  <<cutoffD<<" -1.0"<< endl;
	    
	    /*txtout<<i+3<<" "<<j+3<<" "<<hD<<" "
	      <<hcDiameter<<" "<<ener<<" "
	      <<cutoffD<<" "<<-eINF<< " "
	      <<cutoffD+0.1<< " " << eINF << endl;*/
	  }
	  else{
	    txtout<<i+3<<" "<<j+3<<" "
		  <<hD<<" "<<hcDiameter<<" 10.0 "<<cutoffD<<" 0.2"<<endl;
	  }
      	}
      }
    }
  }
  
  txtout<< "E.ELASTIC COLLISIONS"<<endl;
  txtout<< "F.LINKED PAIRS"<<endl;
  
  double cacbDev=0.02, cacanDev=0.02, cacbnDev=0.034, cacannDev=0.08;

  //CA-CA
  const double aveCACA = 3.8;
  const double minCACA = 3.8-0.12;
  const double maxCACA = 3.8+0.12;

  /*{
    double min_caca=1000000;
    double max_caca=-1000000;
    for(int ich=0; ich<nchain; ich++){
      p.getChainInfor(ich,start,length);
      for(int i=0; i<length-1; i++){
  	aa* theAA = p.getElementAt(i+start);
  	atom* theCA = theAA->getAtomAt(0);
  	aa* nxtAA = p.getElementAt(i+1+start);
  	atom* nxtCA = nxtAA->getAtomAt(0);
  	double dist = theCA->getDist(*nxtCA);
  	if(min_caca>dist) min_caca = dist;
  	if(max_caca<dist) max_caca = dist;
      }
    }
    cout << min_caca << " " << max_caca << endl;
  
    double min_canca=1000000;
    double max_canca=-1000000;
    for(int ich=0; ich<nchain; ich++){
      p.getChainInfor(ich,start,length);
      for(int i=0; i<length-2; i++){
  	aa* theAA = p.getElementAt(i+start);
  	atom* theCA = theAA->getAtomAt(0);
  	aa* nxtAA = p.getElementAt(i+2+start);
  	atom* nxtCA = nxtAA->getAtomAt(0);
  	double dist = theCA->getDist(*nxtCA);
  	if(min_canca>dist) min_canca = dist;
  	if(max_canca<dist) max_canca = dist;
      }
    }
    cout << min_canca << " " << max_canca << endl;
  }
  exit(1);
  */
  
  txtout << ca1 << " " << ca2 << " " 
	 << minCACA-1.0 << " " << minCACA << " " << ener << " "
	 << maxCACA << " " << -ener << " " 
	 << maxCACA+1.0 << " " << -eINF << " " 
	 << maxCACA+1.1 << " " << eINF+ener <<  " " << maxCACA+1.2 << endl;

  const double min_alpha = (5.48-0.25), max_alpha = (5.48+0.25);
  const double min_beta = (6.60-0.45), max_beta = (6.60+0.45);
  txtout << ca1 << " " << ca1 << " " 
	 << min_alpha-1.0 << " " << min_alpha << " " << ener << " "
	 << max_alpha << " " << -ener/10 << " " 
	 << min_beta << " " << ener/10 << " "
	 << max_beta << " " << -ener << " "
	 << max_beta+1.0 << " " << -eINF << " "
	 << max_beta+1.1 << " " << eINF+ener << " " << max_beta+1.2 <<  endl;
  
  txtout << ca2 << " " << ca2 << " " 
	 << min_alpha-1.0 << " " << min_alpha << " " << ener << " "
	 << max_alpha << " " << -ener/10 << " " 
	 << min_beta << " " << ener/10 << " "
	 << max_beta << " " << -ener << " "
	 << max_beta+1.0 << " " << -eINF << " "
	 << max_beta+1.1 << " " << eINF+ener << " " << max_beta+1.2 <<  endl;
  
  const double minCAnCB=(4.63-0.30);
  const double maxCAnCB=(4.63+0.30);
  const double minCACB =(1.53-0.037);
  const double maxCACB =(1.53+0.037);
  for(int ich=0; ich<nchain; ich++){
    p.getChainInfor(ich,start,length);
    for(int i=0; i<length; i++){
      aa* theAA=p.getElementAt(i+start);
      atom* theCA = theAA->getAtomAt(0);
      atom* theCB = NULL;
      if(theAA->getName()!="GLY"){
	theCB=theAA->getAtomAt(1);
	dist=theCA->getDist(*theCB);
	if(dist <= minCACB){
	  txtout<<(i+start)%2+1<<" "<<i+start+3<< " "
		<< dist-0.01 << " " 
		<< minCACB << " " << ener << " " 
		<< maxCACB << endl;
	}
	else if(dist>=maxCACB){
	  txtout<<(i+start)%2+1<<" "<<i+start+3<< " "
		<< minCACB << " " 
		<< maxCACB << " " << -ener << " " 
		<< dist+0.01 << " " << -eINF << " "
		<< dist+0.1 << " " << ener+eINF << " " 
		<< dist+0.2 << endl;
	}
	else{
	  txtout<<(i+start)%2+1<<" "<<i+start+3<< " "
		<<minCACB<<" "<<maxCACB<<endl;
	}
	double min_dist=1000000, max_dist=-10000000;
	if(i>0){
	  aa* preAA = p.getElementAt(i+start-1);
	  atom* preCA = preAA->getAtomAt(0);
	  dist = theCB->getDist(*preCA);
	  min_dist = max_dist = dist;
	  //cout << i << " " << dist << endl;
	}
	if(i<length-1){
	  aa* nxtAA = p.getElementAt(i+start+1);
	  atom* nxtCA = nxtAA->getAtomAt(0);
	  dist = theCB->getDist(*nxtCA);
	  if(dist<min_dist) min_dist = dist;
	  if(dist>max_dist) max_dist = dist;
	  //cout << i << " " << dist << endl;
	}
	if(min_dist>=minCAnCB-1.0){
	  min_dist  = minCAnCB-1.0;
	}
	else{
	  min_dist -= 0.000001;
	}
	if(max_dist<=maxCAnCB+1.0){
	  max_dist = maxCAnCB+1.0;
	}
	else{
	  max_dist += 0.000001;
	}
	//cout << min_dist << " "<< ca_cb_dist << " " << max_dist << " ";
	//cout << minCAnCB << " " << maxCAnCB << endl;
	//cb-CA
	
	txtout << (i+start+1)%2+1 << " " << i+start+3 << " " << min_dist << " " 
	       << minCAnCB << " " << ener << " "
	       << maxCAnCB << " " << -ener << " "
	       << max_dist << " " << -eINF << " "
	       << max_dist+0.1 << " " << eINF+ener << " "
	       << max_dist+0.2 << endl;
      }
    }
  }
  
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
  for(int nz=0; nz<nstp; nz++){
    for(int ny=0; ny<nstp; ny++){
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
    }
  }

  txtout << "H.LIST OF ATOMS" <<endl;
  double vx,vy,vz;
  char buf[1024];
  for(int i=0; i<p.getLength(); i++){
    aa* theAA = p.getElementAt(i);
    atom* theCA = theAA->getAtomAt(0);
    int index = theCA->getIndex();
    vx=vxyz[index-1][0];
    vy=vxyz[index-1][1];
    vz=vxyz[index-1][2];
    sprintf(buf,"%12.6lf %12.6lf %12.6lf %12.6lf %12.6lf %12.6lf",partxyz[index-1][0],partxyz[index-1][1],partxyz[index-1][2],vx,vy,vz);
    txtout <<index<<" "<<i%2+1 <<" "<< buf <<endl;    
    if(theAA->getName()!="GLY"){
      index = theAA->getAtomAt(1)->getIndex();
      vx=vxyz[index-1][0];
      vy=vxyz[index-1][1];
      vz=vxyz[index-1][2];
      sprintf(buf,"%12.6lf %12.6lf %12.6lf %12.6lf %12.6lf %12.6lf",partxyz[index-1][0],partxyz[index-1][1],partxyz[index-1][2],vx,vy,vz);
      txtout <<index<<" "<<i+3 <<" "<<buf<<endl;    
    }
  }

  for(int i=npart; i<ntotal;i++){
    double vx,vy,vz;
    x=ghostxyz[i-npart][0];
    y=ghostxyz[i-npart][1];
    z=ghostxyz[i-npart][2];
    vx=vxyz[i][0];
    vy=vxyz[i][1];
    vz=vxyz[i][2];
    sprintf(buf,"%12.6lf %12.6lf %12.6lf %12.6lf %12.6lf %12.6lf",x,y,z,vx,vy,vz);
    txtout << i+1<<" "<<p.getLength()+2<<" "<<buf<<endl;
  }
  
  txtout<<"I.LIST OF BONDS"<<endl;
  for(int ich=0; ich<nchain; ich++){
    p.getChainInfor(ich,start,length);
    for(int i=0; i<length; i++){
      aa* theAA=p.getElementAt(i+start);
      atom* theCA = theAA->getAtomAt(0);
      atom* theCB = NULL;
      if(theAA->getName()!="GLY"){
	theCB=theAA->getAtomAt(1);
	dist=theCA->getDist(*theCB);
	txtout<<" "<<theCA->getIndex()<<" "<<theCB->getIndex()<<endl;
      }
      if(i+1<length){
	//CA-CA
	aa* nxtAA = p.getElementAt(i+start+1);
	atom* nxtCA = nxtAA->getAtomAt(0);
	dist=theCA->getDist(*nxtCA);
	txtout<<" "<<theCA->getIndex()<<" "<<nxtCA->getIndex()<<endl;
	atom* nxtCB = NULL;
	if(nxtAA->getName()!="GLY"){
	  nxtCB=nxtAA->getAtomAt(1);
	  //CA-CB
	  dist=theCA->getDist(*nxtCB);
	  txtout<<" "<<theCA->getIndex()<<" "<<nxtCB->getIndex()<<endl;
	  //CB-CA
	  if(theCB){
	    dist=theCB->getDist(*nxtCA);
	    txtout<<" "<<theCB->getIndex()<<" "<<nxtCA->getIndex()<<endl;
	  }
	}
      }
      if(i+2<length){
	aa* nxtAA=p.getElementAt(i+start+2);
	atom* nxtCA=nxtAA->getAtomAt(0);
	dist=theCA->getDist(*nxtCA);
	//CA---ca---CA
	txtout<<" "<<theCA->getIndex()<<" "<<nxtCA->getIndex()<<endl;
      }
    }
  }
  txtout.close();
}
