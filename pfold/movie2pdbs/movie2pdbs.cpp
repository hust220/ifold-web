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
  convert a sepcified frames into pdb format. It can works 
  for multiple proteins. 
  
  The model can be either 4bead or 2bead
  
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
    cout << "usage: mov2pdbs.linux movie(bin) origPDB outPDB aamodel[4/2] fixProt [initFrame nFrame]" << endl;
    cout << "  movie    -- the binary movie file stored by DMD" << endl;
    cout << "  origPDB  -- the original PDB" << endl;
    cout << "  outPDB   -- the output PDB" << endl;
    cout << "  aamodel  -- amino acid model 4(bead) or 2(bead)" << endl;
    cout << "  fixProt  -- 1, fix the protein(1st for multiple prot); or O, do not fix" << endl;
    cout << "  initFrame-- OPTIONAL, the initial Frame. Without these, just dump all the frames." << endl;
    cout << "  nFrame   -- OPTIONAL, the Frame number." << endl;
    exit(1);
  }
  
  char* mov = argv[1];
  char* ipdb = argv[2];
  char* opdb = argv[3];
  int nmod = atoi(argv[4]);
  if(nmod!=4 && nmod!=2){
    cout << "The model must be either 4bead or 2bead." << endl;
    exit(1);
  }
  
  vector<int> aalist;
  readPDB(ipdb, aalist);//get the seq
  int na = aalist.size();
  char* amino[na];
  int nGLY=0;
  int ca[na];
  int nres=0;
  for(int i=0; i<na; i++){
    amino[i]=NumToAmino(aalist[i]);
    if(strcmp(amino[i],"GLY")==0){
      nGLY++;
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

  int fix1st = atoi(argv[5]);

  int start=1;
  if(argc>6) start=atoi(argv[6]);
  int nframes=nmax;
  if(argc>6) nframes = atoi(argv[7]);
  
  int np=(int)(npart/nres);
  if(npart%nres!=0){
    cout << "The input PDB is not compatible with the movie!" << endl;
    exit(1);
  }
  
  //cout << boundary << endl;
  ofstream out(opdb);
  double coef=0;
  double range = 10;
  m.jumpto(start);
  int iframe=1;
  cout << nmax << endl;
  while(iframe<=nframes){
    {
      double cm[np][3];
      
      if(coef==0){  //determine the coef
	for(int i=1; i<nres; i++){
	  if(r[i][0]-r[i-1][0] > boundary/2.0f) r[i][0]-=boundary;
	  if(r[i][0]-r[i-1][0] < -boundary/2.0f) r[i][0]+=boundary;
	  if(r[i][1]-r[i-1][1] > boundary/2.0f) r[i][1]-=boundary;
	  if(r[i][1]-r[i-1][1] < -boundary/2.0f) r[i][1]+=boundary;
	  if(r[i][2]-r[i-1][2] > boundary/2.0f) r[i][2]-=boundary;
	  if(r[i][2]-r[i-1][2] < -boundary/2.0f) r[i][2]+=boundary;
	}
	double tmp=0;
	double x, y, z;
	for(int i=1;i<na; i++){
	  x=r[ca[i-1]][0]-r[ca[i]][0];
	  y=r[ca[i-1]][1]-r[ca[i]][1];
	  z=r[ca[i-1]][2]-r[ca[i]][2];
	  tmp+=sqrt(x*x + y*y + z*z);
	}
	tmp/=(double)(na-1);
	coef=tmp/3.80;
	boundary /= coef;
	//range /=coef;
	//cout << boundary << " " << range << endl;
      }
      if(coef != 1.0){
	for(int i=0; i<npart; i++){
	  for(int j=0; j<3; j++)
	    r[i][j] /= coef;
	} 
      }
      
      for(int ip=0; ip<np; ip++){
	cm[ip][0]=r[ip*nres][0];
	cm[ip][1]=r[ip*nres][1];
	cm[ip][2]=r[ip*nres][2];
	for(int i=1+ip*nres; i<nres*(ip+1); i++){
	  if(r[i][0]-r[i-1][0] > boundary/2.0f  && r[i-1][0]+boundary-r[i][0]<range) r[i][0]-=boundary;
	  if(r[i][0]-r[i-1][0] < -boundary/2.0f && r[i][0]+boundary-r[i-1][0]<range) r[i][0]+=boundary;
	  if(r[i][1]-r[i-1][1] > boundary/2.0f  && r[i-1][1]+boundary-r[i][1]<range) r[i][1]-=boundary;
	  if(r[i][1]-r[i-1][1] < -boundary/2.0f && r[i][1]+boundary-r[i-1][1]<range) r[i][1]+=boundary;
	  if(r[i][2]-r[i-1][2] > boundary/2.0f  && r[i-1][2]+boundary-r[i][2]<range) r[i][2]-=boundary;
	  if(r[i][2]-r[i-1][2] < -boundary/2.0f && r[i][2]+boundary-r[i-1][2]<range) r[i][2]+=boundary;
	  cm[ip][0]+=r[i][0];
	  cm[ip][1]+=r[i][1];
	  cm[ip][2]+=r[i][2];
	} 
	for(int i=0; i<3; i++)cm[ip][i]/=(double)nres;
      }
      
      int alloc[np];
      for(int ip=0; ip<np; ip++)alloc[ip]=1;
      int next=0;
      alloc[next]=0;
      double cmCurr[3];
      
      for(int ncount=1; ncount<np; ncount++){
	for(int j=0; j<3; j++) cmCurr[j]=0;
	int ialloc=0;
	for(int i=0; i<np; i++)if(!alloc[i]){
	  ialloc++;
	  for(int j=0;j<3;j++)cmCurr[j]+=cm[i][j];
	}
	for(int j=0; j<3; j++) cmCurr[j]/=(double)ialloc;
	
	double dist=0, min=3000*pow(boundary,2);
	int imin;
	for(int i=0; i<np; i++)if(alloc[i]){
	  for(int j=0; j<3;j++){
	    double temp = fabs(cm[i][j]-cmCurr[j]);
	    if(temp>boundary/2.0f)temp-=boundary;
	    dist+=temp*temp;
	  }
	  if(min>dist){
	    min = dist;
	    imin = i;
	  }
	}
	
	if(cm[imin][0]-cmCurr[0]>boundary/2.0f){
	  cm[imin][0]-=boundary;
	  for(int i= imin*nres; i<(imin+1)*nres; i++) r[i][0]-=boundary;
	}
	if(cm[imin][0]-cmCurr[0]<-boundary/2.0f){
	  cm[imin][0]+=boundary;
	  for(int i= imin*nres; i<(imin+1)*nres; i++) r[i][0]+=boundary;
	}
	
	if(cm[imin][1]-cmCurr[1]>boundary/2.0f){
	  cm[imin][1]-=boundary;
	  for(int i= imin*nres; i<(imin+1)*nres; i++) r[i][1]-=boundary;
	}
	if(cm[imin][1]-cmCurr[1]<-boundary/2.0f){
	  cm[imin][1]+=boundary;
	  for(int i= imin*nres; i<(imin+1)*nres; i++) r[i][1]+=boundary;
	}
	
	if(cm[imin][2]-cmCurr[2]>boundary/2.0f){
	  cm[imin][2]-=boundary;
	  for(int i= imin*nres; i<(imin+1)*nres; i++) r[i][2]-=boundary;
	}
	if(cm[imin][2]-cmCurr[2]<-boundary/2.0f){
	  cm[imin][2]+=boundary;
	  for(int i= imin*nres; i<(imin+1)*nres; i++) r[i][2]+=boundary;
	}
	alloc[imin]=0;
      }
      
      for(int i=0; i<3; i++)cmCurr[i]=cm[0][i];
      if(!fix1st){
	for(int ip=1; ip<np;ip++)
	  for(int i=0;i<3;i++)cmCurr[i]+=cm[ip][i];
	for(int i=0; i<3; i++)cmCurr[i]/=(double)np;
      }
      for(int i=0; i<npart; i++){
	r[i][0]-=(cmCurr[0]-boundary/2.0);
	r[i][1]-=(cmCurr[1]-boundary/2.0);
	r[i][2]-=(cmCurr[2]-boundary/2.0);
      }
      
      /*convert the xyz to PDB*/
      if(nmod==2){
	int j=0;
	double x, y, z;
	for(int ip=0;ip<np;ip++){
	  for(int i=0; i<na; i++){
	    if(strcmp(amino[i],"GLY")!=0){
	      x=r[j][0]; y=r[j][1]; z=r[j][2]; j++;
	      sprintf(&field[0],"ATOM  %5d  CA  %3s  %4d    %8.3lf%8.3lf%8.3lf  1.00  0.00              ",
		      // j,amino[i],i+1,x,y,z);  
		      j,amino[i],i+1+ip*na,x,y,z);  
	      out << field << endl;
	      x=r[j][0]; y=r[j][1]; z=r[j][2]; j++;
	      sprintf(&field[0],"ATOM  %5d  CB  %3s  %4d    %8.3lf%8.3lf%8.3lf  1.00  0.00              ",
		      j,amino[i],i+1+ip*na,x,y,z); 
	      out << field << endl;
	    }
	    else{
	      x=r[j][0]; y=r[j][1]; z=r[j][2]; j++;
	      sprintf(&field[0],"ATOM  %5d  CA  %3s  %4d    %8.3lf%8.3lf%8.3lf  1.00  0.00              ",
		      j,amino[i],i+1+ip*na,x,y,z); 
	      out << field << endl;
	    }
	  }
	  if(ip<np-1) out << "TER" << endl;
	  else out << "END"<< endl;
	}
      }
      else{
	int iatom=0;
	int atomIndex=0;
	int ic, in, ica;
	double x, y, z;
	for(int ip=0; ip<np; ip++){
	  for(int i=0; i<na; i++){
	    x = r[iatom][0];
	    y = r[iatom][1];
	    z = r[iatom][2];
	    sprintf(&field[0],"ATOM  %5d  N   %3s  %4d    %8.3lf%8.3lf%8.3lf  1.00  0.00              ",
		    ++atomIndex, amino[i], i+1+ip*na, x, y, z);
	    out << field << endl;
	    in=iatom; 
	    iatom++;
	    if(i>0){//reconstruct H atom
	      if(strcmp(amino[i-1],"GLY")==0){
		ic=in-2;
	      }
	      else{
		ic=in-3;
	      }
	      ica = in+2;
	      x=r[ic][0]*ndc*1.02 + r[in][0]*(ndn*1.02+1.0) + r[ica][0]*ndca*1.02;
	      y=r[ic][1]*ndc*1.02 + r[in][1]*(ndn*1.02+1.0) + r[ica][1]*ndca*1.02;
	      z=r[ic][2]*ndc*1.02 + r[in][2]*(ndn*1.02+1.0) + r[ica][2]*ndca*1.02;
	      sprintf(&field[0],"ATOM  %5d  H   %3s  %4d    %8.3lf%8.3lf%8.3lf  1.00  0.00              ",
		      ++atomIndex, amino[i], i+1+ip*na, x, y, z);
	      out << field << endl;
	    }
	    //C
	    x = r[iatom][0];
	    y = r[iatom][1];
	    z = r[iatom][2];
	    sprintf(&field[0],"ATOM  %5d  C   %3s  %4d    %8.3lf%8.3lf%8.3lf  1.00  0.00              ",
		    ++atomIndex, amino[i], i+1+ip*na, x, y, z);
	    out << field << endl;
	    ic=iatom;
	    iatom++;
	    if(i<na-1){//reconstruct O atom
	      if(strcmp(amino[i],"GLY")==0) in =ic+2;
	      else in = ic+3;
	      ica=ic+1;
	      x=r[ica][0]*cdca*1.24 + r[ic][0]*(cdc*1.24+1.0) + r[in][0]*cdn*1.24;
	      y=r[ica][1]*cdca*1.24 + r[ic][1]*(cdc*1.24+1.0) + r[in][1]*cdn*1.24;
	      z=r[ica][2]*cdca*1.24 + r[ic][2]*(cdc*1.24+1.0) + r[in][2]*cdn*1.24;
	      sprintf(&field[0],"ATOM  %5d  O   %3s  %4d    %8.3lf%8.3lf%8.3lf  1.00  0.00              ",
		      ++atomIndex, amino[i], i+1+ip*na, x, y, z);
	      out << field << endl;
	    }
	    //CA
	    x = r[iatom][0];
	    y = r[iatom][1];
	    z = r[iatom][2];
	    sprintf(&field[0],"ATOM  %5d  CA  %3s  %4d    %8.3lf%8.3lf%8.3lf  1.00  0.00              ",
		    ++atomIndex, amino[i], i+1+ip*na, x, y, z);
	    out << field << endl;
	    ica=iatom;
	    iatom++;
	    //CB
	    if(strcmp(amino[i],"GLY")!=0){
	      x = r[iatom][0];
	      y = r[iatom][1];
	      z = r[iatom][2]; 
	      sprintf(&field[0],"ATOM  %5d  CB  %3s  %4d    %8.3lf%8.3lf%8.3lf  1.00  0.00              ",
		      ++atomIndex, amino[i], i+1+ip*na, x, y, z);
	      out << field << endl;
	      iatom++;
	    }
	  }
	  if(ip < np-1) out << "TER" << endl;
	  else out << "END" << endl;
	}
      }
    }
    if(m.nextFrame() && iframe<nframes){
      cout << "error in reading movie" << endl;
      break;
    }
    else iframe++;
  }
  out.close();
  return 0;
}
