#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "movie.h"
#include "krms.h"
#include "PDBLib-NChain.h"

/*-------------------------------------------
  This program read the movie file using movie class and 
  convert a sepcified frames into pdb format. It can works 
  for multiple proteins. 
  
  The model can be either 4bead or 2bead
  
  Author: Feng Ding
  fding@bu.edu
  -------*/
using namespace std;

const static double ndc   = -0.7784 ;
const static double ndca  = -0.7088 ;
const static double cdc   =  1.3379 ;
const static double cdca  = -0.6144 ;
const static double cdn   = -0.7235 ;

char* TriLetterCode[20]=
{
  "ALA","CYS","ASP","GLU","PHE",
  "GLY","HIS","ILE","LYS","LEU",
  "MET","ASN","PRO","GLN","ARG",
  "SER","THR","VAL","TRP","TYR"
};

char* OneLetterCode[20]=
  {
    "A"  ,  "C",  "D",  "E",  "F",
    "G"  ,  "H",  "I",  "K",  "L",
    "M"  ,  "N",  "P",  "Q",  "R",
    "S"  ,  "T",  "V",  "W",  "Y"
  };

int AminoToNum(char* amino)
{
  int length = strlen( amino );
  char** pt;
  int i;
  
  if( length == 1 )
    pt = OneLetterCode;
  else if( length == 3 )
    pt = TriLetterCode;
  else
    {
      printf("Wrong Amino Acid name!\n");
      exit(1);
    }
  
  for(i=0; i<20 ; i++)
    {
      if( strcmp(amino, pt[i])==0 )
        return i;
    }
  
  printf("Can not find the Amino Acid!\n");
  exit(1);
}

char* NumToAmino( int i )
{
  if( i >=20 || i < 0 )
    {
      printf("It is out of Amino Acid range!\n");
      exit(1);
    }
  return TriLetterCode[i];
}

int main(int argc, char* argv[]){
  if(argc<4){
    cout << "usage: mov2rmsd.linux movie(bin) refPDB rmsdFile [rmsd_per_res_file]"<<endl ;
    cout << "  movie    -- the binary movie file stored by DMD" << endl;
    cout << "  origPDB  -- the original PDB" << endl;
    exit(1);
  }
  
  char* mov = argv[1];
  char* ipdb = argv[2];
  char* opdb = argv[3];
  
  protein p(ipdb);
  int na = p.getLength();
  
  int ca[na];
  int nres=0;
  
  double** ref = new double*[na];
  ref[0] = new double[na*3];
  for(int i=1; i<na; i++) ref[i] = ref[i-1]+3;
  
  int nmod=2;

  for(int i=0; i<na; i++){
    int t = AminoToNum(cstr(p.getElementAt(i)->getName()).getStr());
    if(p.getElementAt(i)->getName()=="GLY"){
      if(nmod==4){
	ca[i]=nres+2;
	nres+=3;
      }
      else{
	ca[i]=nres;
	nres+=1;
      }      
    }
    else{
      if(nmod==4){
	ca[i]=nres+2;
	nres+=4;
      }
      else{
	ca[i]=nres;
	nres+=2;
      }
    }
  }
  
  double cm[3];
  for(int i=0; i<3; i++) cm[i]=0;
  for(int i=0; i<na; i++){
    ref[i][0]=p.getElementAt(i)->getAtomAt(0)->getR()->getX();
    ref[i][1]=p.getElementAt(i)->getAtomAt(0)->getR()->getY();
    ref[i][2]=p.getElementAt(i)->getAtomAt(0)->getR()->getZ();
    for(int j=0; j<3; j++){
      cm[j]+=ref[i][j];
    }
  }
  for(int j=0; j<3; j++) cm[j]/=(double)na;
  for(int i=0; i<na; i++)
    for(int j=0; j<3; j++){
      ref[i][j] -= cm[j];
    }
  
  double** snapshot = new double*[na];
  snapshot[0] = new double[na*3];
  for(int i=1; i<na; i++) snapshot[i] = snapshot[i-1]+3;
  
  double* dr = NULL;
  double* dr_sum = NULL;
  
  if(argc==5){
    dr = new double[na];
    for(int i=0; i<na; i++) dr[i]=0;
    
    dr_sum = new double[na];
    for(int i=0; i<na; i++) dr_sum[i]=0;
  }
  
  char field[1024];
  /*read the movie parameter*/
  movie m(argv[1]);
  if(m.getErrorStatus()){
    cout << m.getMsg() << endl;
    exit(1);
  }
  int nmax   = m.getNFrames();
  double dt  = m.getDeltaT();
  int npart  = m.getNAtoms();
  double boundary = m.getDimensions()[0];
  double** r = m.getCoords();
  
  int start=1;
  if(argc>4) start=atoi(argv[4]);
  int nframes=nmax;
  if(argc>5) nframes = atoi(argv[5]);
  
  if(npart!=nres){
    cout << "The input PDB is not compatible with the movie!" << endl;
    exit(1);
  }
  
  //cout << boundary << endl;
  double coef=1;
  ofstream out(opdb);
  m.jumpto(start-1);
  m.nextFrame();
  cout << nmax << endl;
  int iframe=1;
  while(iframe<=nframes){
    
    for(int i=1; i<nres; i++){
      if(r[i][0]-r[i-1][0] > boundary/2.0f) r[i][0]-=boundary;
      if(r[i][0]-r[i-1][0] < -boundary/2.0f) r[i][0]+=boundary;
      if(r[i][1]-r[i-1][1] > boundary/2.0f) r[i][1]-=boundary;
      if(r[i][1]-r[i-1][1] < -boundary/2.0f) r[i][1]+=boundary;
      if(r[i][2]-r[i-1][2] > boundary/2.0f) r[i][2]-=boundary;
      if(r[i][2]-r[i-1][2] < -boundary/2.0f) r[i][2]+=boundary;
    }
    
    for(int j=0; j<3; j++) cm[j]=0;
    for(int i=0; i<na; i++)
      for(int j=0; j<3; j++) {
	snapshot[i][j] = r[ca[i]][j];
	cm[j] += snapshot[i][j];
      }
    for(int j=0; j<3; j++) cm[j]/=(double)na;
    for(int i=0; i<na; i++)
      for(int j=0; j<3; j++){
	snapshot[i][j]-=cm[j];
	//cout << ca[i] << " " << snapshot[i][j] << endl;
	
      }
    
    {
      double rmsd=get_rms(ref, snapshot, na, dr);
      out << m.getCurrentFrame()*dt << " " << sqrt(rmsd/na) << endl;
      if(dr_sum) for(int i=0; i<na; i++)dr_sum[i]+=dr[i];
    }
    if(m.nextFrame() && iframe<nframes){
      cout << "error in reading movie" << endl;
      break;
    }
    else iframe++;
  }
  out.close();
  if(dr_sum){
    out.open(argv[4], ios::out);
    for(int i=0; i<na; i++){
      dr_sum[i] /= (double) iframe;
      out << i+1 << " " << sqrt(dr_sum[i]) << endl;
    }
    out.close();
  }
  return 0;
}
