#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "movie.h"

/*-------------------------------------------
  This program read the movie file using movie class and 
  calculate the freq map based on CB atoms. It can works 
  for multiple proteins. 
  
  The model can be either 4bead or 2bead.
  
  Author: Feng Ding
  fding@bu.edu
  -------*/
using namespace std;
const static double ndn   =  1.4872 ;
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

void readPDB(char* name, vector<int>& aalist)
{
  fstream in;
  in.open(name, ios::in);
  string line;
  string AtomField("ATOM  ");
  while(getline(in, line))
    {
      string field = line.substr(0, 6);
      if(field==AtomField) break;
    }
  
  int pnum=-999, num;
  while(1)
    {
      char tmp[81];
      string substr;
      
      char res[4];
      substr=line.substr(12,4);
      substr.copy(tmp, 4); tmp[4]='\0';
      sscanf(tmp,"%s", res);

      char acid[20];
      substr=line.substr(17,3);
      substr.copy(tmp, 3); tmp[3]='\0';
      sscanf(tmp, "%s", acid);

      double x, y , z;
      substr=line.substr(30,24);
      substr.copy(tmp, 24); tmp[24]='\0';
      sscanf(tmp,"%lf%lf%lf", &x, &y, &z);

      substr=line.substr(22, 4);
      substr.copy(tmp, 4); tmp[4]='\0';
      sscanf(tmp, "%d", &num);

      //check the chain continuity
      if( pnum < 0 ) pnum = num - 1;
      if( pnum == num-1 ) pnum = num;
      else if( pnum == num ) ;
      else{
	printf("This protein chain is somewhere broken!\n");
	break ;
      }
      //make operation
      if( strcmp(res, "CA")==0 )
	aalist.push_back(AminoToNum(acid));
      //read new line
      if(!getline(in,line)) break;
      string field=line.substr(0,6);
      if(field != AtomField) break;
    }
}

int main(int argc, char* argv[]){
  if(argc<6){
    cout << "usage: mov2Freq.linux movie(bin) samplePDB aaModel[4/2] cutoff[A] freqFile [initFrame nFrame]" << endl;
    cout << "  movie    -- the binary movie file stored by DMD" << endl;
    cout << "  samplePDB-- the sample PDB" << endl;
    cout << "  aaModel  -- the amino acid model 4 or 2" << endl;
    cout << "  cutoff   -- the distance to define contact, e.g 7.5" << endl;
    cout << "  freqFile -- the frequency file" << endl;
    cout << "  initFrame-- OPTIONAL, the initial Frame. Without these, just dump all the frames." << endl;
    cout << "  nFrame   -- OPTIONAL, the Frame number." << endl;
    exit(1);
  }
  
  char* mov = argv[1];
  char* pdb = argv[2];
  char* freq= argv[5];
  const int nmod = atoi(argv[3]);
  double cutoff = atof(argv[4]);
  
  if(nmod!=4 && nmod!=2){
    cout << "The model must be either 4bead or 2bead." << endl;
    exit(1);
  }
  
  vector<int> aalist;
  //get the seq
  readPDB(pdb, aalist);

  int na = aalist.size();
  int ca[na];
  int cb[na];
  int nres=0;
  char* amino;
  for(int i=0; i<na; i++){
    amino=NumToAmino(aalist[i]);
    if(strcmp(amino,"GLY")==0){
      if(nmod==4){
	ca[i]=nres+2;
	cb[i]=nres+2;
	nres+=3;
      }
      else{
	ca[i]=nres;
	cb[i]=nres;
	nres+=1;
      }      
    }
    else{
      if(nmod==4){
	ca[i]=nres+2;
	cb[i]=nres+3;
	nres+=4;
      }
      else{
	ca[i]=nres;
	cb[i]=nres+1;
	nres+=2;
      }
    }
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
  if(argc>6) start=atoi(argv[6]);
  int nframe=nmax;
  if(argc>6) nframe = atoi(argv[7]);

  npart = nres;
  int np=(int)(npart/nres);

  if(npart%nres!=0){
    cout << "The input PDB is not compatible with the movie!" << endl;
    exit(1);
  }
  cout << "Frame separation dt:" << dt << endl;
  cout << "Number of frames   :" << nmax << endl;
  cout << "Number of particles:" << npart << endl;
  cout << "Number of peptides :" << np << endl;
  
  //find out the coef
  double coef=1.0;
  m.jumpto(start-1);
  m.nextFrame();
  int iframe=1;
  double tmp=0;
  double x,y,z;
  /*
    for(int i=1; i<nres; i++){
    if(r[i][0]-r[i-1][0] > boundary/2.0f) r[i][0]-=boundary;
    if(r[i][0]-r[i-1][0] < -boundary/2.0f) r[i][0]+=boundary;
    if(r[i][1]-r[i-1][1] > boundary/2.0f) r[i][1]-=boundary;
    if(r[i][1]-r[i-1][1] < -boundary/2.0f) r[i][1]+=boundary;
    if(r[i][2]-r[i-1][2] > boundary/2.0f) r[i][2]-=boundary;
    if(r[i][2]-r[i-1][2] < -boundary/2.0f) r[i][2]+=boundary;
    }
    for(int i=1; i<na; i++){
    x=r[ca[i-1]][0]-r[ca[i]][0];
    y=r[ca[i-1]][1]-r[ca[i]][1];
    z=r[ca[i-1]][2]-r[ca[i]][2];
    tmp+=sqrt(x*x + y*y + z*z);
    }
    tmp/=(double)(na-1);
  */
  //coef=tmp/3.81;
  //cutoff *= coef;
  
  //initialize the arrays
  ofstream out(freq);
  double*** freqmap=new double**[np];
  for(int ip=0; ip<np; ip++){
    freqmap[ip] = new double*[na];
    freqmap[ip][0] = new double[(na*(na-1))/2];
    for(int j=1; j<na; j++) freqmap[ip][j] = freqmap[ip][j-1]+j-1; 
    for(int j=0; j<(na*(na-1))/2; j++) freqmap[ip][0][j]=0;
  }

  //start to calculate the freq for different chains:
  while(iframe<=nframe){
    for(int ip=0; ip<np; ip++){
      //consider the boundary condition
      for(int ia=ip*nres+1; ia<(ip+1)*nres; ia++){
	if(r[ia][0]-r[ia-1][0] > boundary/2.0f) r[ia][0]-=boundary;
	if(r[ia][0]-r[ia-1][0] < -boundary/2.0f) r[ia][0]+=boundary;
	if(r[ia][1]-r[ia-1][1] > boundary/2.0f) r[ia][1]-=boundary;
	if(r[ia][1]-r[ia-1][1] < -boundary/2.0f) r[ia][1]-=boundary;
	if(r[ia][2]-r[ia-1][2] > boundary/2.0f) r[ia][2]-=boundary;
	if(r[ia][2]-r[ia-1][2] < -boundary/2.0f) r[ia][2]-=boundary;
      }
      //calculate the contact map
      for(int ires=0; ires<na; ires++){
	for(int jres=0; jres<ires-1; jres++){
	  x = r[ip*nres+cb[ires]][0]-r[ip*nres+cb[jres]][0];
	  y = r[ip*nres+cb[ires]][1]-r[ip*nres+cb[jres]][1];
	  z = r[ip*nres+cb[ires]][2]-r[ip*nres+cb[jres]][2];
	  tmp = sqrt(x*x + y*y + z*z);
	  if(tmp<=cutoff){//a contact
	    freqmap[ip][ires][jres]+=1.0;
	  }
	}
      }
    }
    
    if(m.nextFrame() && iframe<nframe){
      cout << "error in reading movie" << endl;
      break;
    }
    else iframe++;
  }
  
  for(int ip=0; ip<np; ip++)
    for(int i=0; i<(na*(na-1))/2; i++) 
      freqmap[ip][0][i] /= (double)nframe;
  //write out the stuff
  int pt=0;
  for(int ires=0; ires<na; ires++){
    for(int jres=0; jres<ires-1; jres++){
      pt=sprintf(&field[0],"%4ld %4ld ", jres+1, ires+1);
      for(int ip=0; ip<np; ip++){
	pt+=sprintf(&field[pt], "%13.8lf ", freqmap[ip][ires][jres]);
      }
      out<< field<< endl;
    }
  }
  out.close();
}
