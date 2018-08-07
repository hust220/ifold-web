#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

float ran1(int*);
float gasdev(int*);
void nrerror(char*);

#define DIST(TMP,I,J) \
TMP=0;for(int k=0; k<3; k++)TMP+=(partxyz[I][k]-partxyz[J][k])* \
(partxyz[I][k]-partxyz[J][k]);TMP=sqrt(TMP);

#define RD(IN,TYPE, XYZ) \
IN >> TYPE;for(int ii=0; ii<3; ii++) IN >> XYZ[ii];

struct atom
{
  char* carbon;
  char* residue;
  int type;
  double x;
  double y;
  double z;
};

typedef struct atom* ATOM;

char* Carbon[2]=
{
  "CA", "CB"
};

ATOM AtomNew(char* carbon, char* res, double x, double y, double z)
{
  ATOM atom = (ATOM)malloc(sizeof(struct atom));
  atom->carbon = carbon;
  atom->residue = res;
  atom->x = x;
  atom->y = y;
  atom->z = z;
  return atom;
}

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

char* sequence[20] = {
  "C","M","F","I","L",
  "V","W","Y","A","G",
  "T","S","Q","N","E",
  "D","H","R","K","P"
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
      //printf("Wrong Amino Acid name!\n");
      return -1;
    }
  
  for(i=0; i<20 ; i++)
    {
      if( strcmp(amino, pt[i])==0 )
        return i;
    }
  
  //printf("Can not find the Amino Acid!\n");
  return -1;
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

int readPDB(char* name, vector<ATOM>& pool )
{
  fstream in;
  in.open(name, ios::in);
  string line;
  string AtomField("ATOM  ");
  int yes = 0;
  while(getline(in,line))
    {
      string field = line.substr(0, 6);
      if(field==AtomField) { yes = 1; break ;}
    }
  int pnum=-999, num;
  int i=0;
  while(yes)
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

      //check the continuity
      if(pnum = -999) pnum = num - 1;
      if( pnum == num-1 ) pnum = num;
      else if( pnum == num ) ;
      else
        {
          printf("This protein chain is somewhat broken!\n");
          return i;
        }
      
      //reading
      if(strcmp(res, "CA")==0)
	{
	  int iaa = AminoToNum( acid );
          if( iaa < 0 ) break;
	  pool.push_back(AtomNew(Carbon[0], NumToAmino(iaa), x, y, z));
	  i++;
	}
      else if(strcmp(acid, "GLY")!=0 && strcmp(res,"CB")==0)
	{
	  int iaa = AminoToNum( acid );
	  if( iaa <0 ) break;
	  pool.push_back(AtomNew(Carbon[1], NumToAmino(iaa), x , y, z ));
	}
      
      //read new line
      if(!getline(in,line)) break;
      string field=line.substr(0,6);
      if(field != AtomField) break;
    }
  return i;
}

char** stringpt;

int main(int argc, char* argv[]){
    if(argc<8){
	cout << "usage: command origPDB outTXT boundary emf hdMatrix cutoff[A] CACA-stength" << endl
	     << "\t origPDB    : original PDB file" << endl
	     << "\t outTXT     : the output TXT file" << endl
	     << "\t boundary   : the size of the simulation box " << endl
	     << "\t emf        : the amino acid specific initeraction matrix, JUNK for GO model" << endl
	     << "\t hdMatrix   : the amino acid specific hard-core matrix"<< endl
	     << "\t cutoff[A]  : the interaction range cutoff in Angstrom" << endl
	     << "\t CACA-stength : the interactionstregth of CA CA(no-bonded) " << endl;
	exit(1);
    }
    
    vector<ATOM> pool;
    int naa=readPDB(argv[1], pool);
    double boundary = atof(argv[3]);
    //int norm_func = atol(argv[7]);
    int norm_func = 0;
    double hbe = atof(argv[7]);
    double hbc = 5.5;
    char field[256];
    int caIndex[naa];
    char* seq[naa];
    int cbIndex[naa];
    int revIndex[naa*2];// +: CA; -; CB; 0: GLY
    double partxyz[2*naa][3];
    int nghost = 0;  //no ghost particles
    
    double d0 = 0.001;
    double erep;
    
    int npart=0;
    int type=3;
    for(int i=0; i<naa; i++){
	if(strcmp(pool[npart]->residue, "GLY")!=0){
	    caIndex[i]=npart;
	    revIndex[npart]=i+1;
	    seq[i]=pool[npart]->residue;
	    partxyz[npart][0]=pool[npart]->x;
	    partxyz[npart][1]=pool[npart]->y;
	    partxyz[npart][2]=pool[npart]->z;
	    pool[npart]->type=1+(i%2);
	    npart++;
	    cbIndex[i]=npart;
	    revIndex[npart]=-(i+1);
	    partxyz[npart][0]=pool[npart]->x;
	    partxyz[npart][1]=pool[npart]->y;
	    partxyz[npart][2]=pool[npart]->z;
	    pool[npart]->type = type;
	    type++;
	    npart++;
	}
	else{
	    caIndex[i]=npart;
	    cbIndex[i]=npart;
	    seq[i]=pool[npart]->residue;
	    revIndex[npart]=0;
	    partxyz[npart][0]=pool[npart]->x;
	    partxyz[npart][1]=pool[npart]->y;
	    partxyz[npart][2]=pool[npart]->z;
	    pool[npart]->type=1+(i%2);
	    npart++;
	}
    }
    int nTYPE = type-1;

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
    
    out1 << "//D. The unit factor " << endl;
    out1 << unit << endl;
    
    for(int i=0; i< npart; i++)
	for(int j=0; j<3;j++) partxyz[i][j]=partxyz[i][j]*unit;
    
    double cm[3];
    for(int i=0; i<3;i++) cm[i]=0;
    for(int i=0; i< npart; i++)
	for(int j=0; j<3; j++) 
	    cm[j]+=partxyz[i][j];
    for(int i=0; i<3 ;i++) cm[i]=cm[i]/npart;
    for(int i=0; i< npart;i++)
	for(int j=0;j<3;j++)
	    partxyz[i][j]=partxyz[i][j] - cm[j] + boundary/2.0;
    
    out1 << "//E. Residues' positions(after zoom and shift)" << endl;
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
    out1.close();
    
    
    double temp;
    //non-bonded ca - ca minimum distance
    double minDist=10000;
    for(int i=0; i< naa-3; i++){
      if(revIndex[caIndex[i]] !=0 ) {
	int ia=caIndex[i];               //ca
	for(int j=i+3; j< naa; j++){
	  if(revIndex[caIndex[j]] != 0){ 
	    DIST(temp, ia, caIndex[j]);  //ca
	    if(temp < minDist) minDist = temp;
	  }
	}
      }
    }
    double minCACA = minDist - 0.0001;
    
    //non-bonded ca - cb minimum distance
    minDist=10000;
    for(int i=0; i< naa-3; i++){
      if(revIndex[caIndex[i]] !=0 ) {
	int ia=caIndex[i];                //ca
	for(int j=i+3; j< naa; j++){
	  DIST(temp, ia, cbIndex[j]);     //cb
	  if(temp < minDist) minDist = temp;
	}
      }
    }
    for(int i=0; i< naa-3; i++){
      int ib=cbIndex[i];                  //cb
      for(int j=i+3; j< naa; j++){
	if(revIndex[caIndex[j]] != 0){  
	  DIST(temp, ib, caIndex[j]);     //ca
	  if(temp < minDist) minDist = temp;
	}
      }
    }
    double minCACB = minDist - 0.0001;
    
    //non-bonded cb - cb minimum distance
    minDist=10000;
    for(int i=0; i< naa-1; i++){
      if(revIndex[caIndex[i]]!=0){
	int ib1=cbIndex[i];                      //cb
	for(int j=i+1; j< naa; j++)
	  if(revIndex[caIndex[j]]!=0 || j!=i+1){ //!(next ca GLY)
	    int ib2=cbIndex[j];
	    DIST(temp,ib1,ib2);
	    if(minDist>temp) minDist=temp;
	  }
      }
      else{
	int ib1=cbIndex[i];                      //ca GLY
	for(int j=i+2; j<naa; j++){
	  if(revIndex[caIndex[j]]!=0 || j!=i+2){ //cb
	    int ib2=cbIndex[j];
	    DIST(temp,ib1,ib2);
	    if(minDist>temp) minDist=temp;
	  }
	}
      }
    }
    double minCBCB = minDist - 0.0001;
    
    double cacbDev=0.02, cacanDev=0.02, cacbnDev=0.034, cacannDev=0.08;
    double ener, hd_core;
    
    double hcDiameter = minCACA;
    {
      if(hcDiameter>minCACB) hcDiameter = minCACB;
      if(hcDiameter>minCBCB) hcDiameter = minCBCB;
    }
    
    ofstream txtout(argv[2]);
    {
      double interaction[21][21];
      double hd[21][21];
      {  
	ifstream matrix_in(argv[4]);
	ifstream hd_in(argv[5]);
	
	double offset=0;
	
	double interaction_tmp[21][21];
	for(int i=0; i<20; i++)
	  for(int j=0; j<20; j++) {
	    interaction_tmp[i][j] += offset;
	  }
	matrix_in >> erep;
	
	//normalize the interaction matrix
	
	double norm_coef = 1;
	if(norm_func == 1){
	  norm_coef = 10.00/erep;
	}
	else if(norm_func == 2){
	  double junk=0;
	  int ijunk = 0;
	  for(int i=0; i<20; i++)
	    for(int j=0; j<=i; j++){
	      double tmp = fabs(interaction_tmp[i][j]);
	      if(tmp !=0){
		junk += tmp;
		ijunk++;
	      }
	    }
	  norm_coef = (double)ijunk / junk;
	}
	else if(norm_func == 0)
	  norm_coef = 1;
	else{
	  cout << "Wrong normalization coefficient! Out of range." << endl; 
	  exit(1);
	}
	
	double hd_tmp[21][21];
	for(int i=0; i<20; i++)
	  for(int j=0; j<20; j++){
	    hd_in >> hd_tmp[i][j];
	  }
	
	int mseqIndex[21];
	char c[10];
	stringpt=OneLetterCode;
	for(int i=0; i<20; i++){
	  mseqIndex[i] = AminoToNum(sequence[i]);
	}
	
	for(int i=0; i<20; i++)
	  for(int j=0; j<20; j++){
	    interaction[mseqIndex[i]][mseqIndex[j]]=interaction_tmp[i][j]*norm_coef;
	    hd[mseqIndex[i]][mseqIndex[j]]=hd_tmp[i][j];
	  }
	erep *= norm_coef;
	
	//fclose(matrix_seq_in);
	matrix_in.close();
	hd_in.close();
      }
      
      erep = 100;
      
      int seqIndex[naa+1];
      stringpt=TriLetterCode;
      for(int i=0; i<naa; i++){
	seqIndex[i] = AminoToNum(seq[i]);
      }
      txtout << "//(simulation time 0)\n";
      txtout << "//length of search table (0 currnet length)\n";
	
      txtout << "A.SYSTEM SIZE" <<endl;
      double size = boundary;
      txtout<<size<<" "<<size<<" "<<size<<endl;
      
      int ntotal = npart + nghost;
      txtout << "B.NUMBER OF ATOMS" << endl;
      txtout << ntotal <<endl;
      
      double mass=1.0;
      double hcRadius = minCACA/2;
      double cutoffD,cutoffR;
      cutoffD = atof(argv[6]);
      cutoffD=cutoffD*unit;
      hbc *= unit;
      cutoffR=cutoffD/2;
      txtout << "C.TYPES OF ATOMS" <<endl;
      txtout << "//type,mass,ellastic radius,interaction radius" <<endl;

      sprintf(field, "1 %lf %lf %lf", mass, hcRadius, cutoffR); txtout << field << endl;
      sprintf(field, "2 %lf %lf %lf", mass, hcRadius, cutoffR); txtout << field << endl;
      
      const double minCBCB = 4.24*unit;
      for(int i=0; i< nTYPE-2; i++){
	sprintf(field, "%ld %lf %lf %lf", i+3, mass, minCBCB/2.0, cutoffR);
	txtout << field << endl;
      }
	
      txtout << "D.NON-ELASTIC COLLISIONS"<<endl;
      txtout <<"//pair types, repulsive dist, interaction distance, energy"<<endl;
      
      double aveCACB = 4.24 * unit;
      double aveCACA = 4.00 * unit;
      ener = 10;
      sprintf(field, "1 1 %lf %lf %lf %lf %lf %lf %lf", d0, (d0+aveCACA)/2, ener, aveCACA, ener, hbc, -ener/10); txtout << field << endl;
      sprintf(field, "1 2 %lf %lf %lf %lf %lf %lf %lf", d0, (d0+aveCACA)/2, ener, aveCACA, ener, hbc, -ener/10); txtout << field << endl;
      sprintf(field, "2 2 %lf %lf %lf %lf %lf %lf %lf", d0, (d0+aveCACA)/2, ener, aveCACA, ener, hbc, -ener/10); txtout << field << endl;
      for(int i=3; i<=nTYPE; i++){
	sprintf(field, "1 %ld %lf %lf %lf %lf %lf", i, d0, (d0+aveCACB)/2, ener, aveCACB, ener);
	txtout << field << endl;
	sprintf(field, "2 %ld %lf %lf %lf %lf %lf", i, d0, (d0+aveCACB)/2, ener, aveCACB, ener);
	txtout << field << endl;
      }
      
      for(int i=0; i< naa-1; i++){
	int ia;
	int ib;
	if(revIndex[caIndex[i]]!=0){
	  ib=cbIndex[i];
	  ia=caIndex[i+1];
	  if(revIndex[ia]!=0){
	    ia=cbIndex[i+1];
	    DIST(temp,ib,ia);  //cb next cb
	    ener = 10;
	    if(temp<=minCBCB){
	      printf("too small distance between atoms %ld and %ld: %lf < %lf\n",ib, ia, temp, minCBCB);
	      sprintf(field, "%ld %ld %lf %lf %lf %lf %lf %lf %lf %lf %lf", pool[ib]->type, pool[ia]->type, 
		      d0, minCBCB-3.0, ener, minCBCB-2.0, ener, minCBCB-1.0, ener, minCBCB, ener);
	    }
	    else{
	      sprintf(field, "%ld %ld %lf", pool[ib]->type, pool[ia]->type, minCBCB);
	    }
	    txtout << field << endl;
	  }
	  if(i<naa-2){
	    for(int j=i+2;j<naa;j++){
	      if(revIndex[caIndex[j]]!=0){
		ia=cbIndex[j];
		DIST(temp,ib,ia);
		if(temp>cutoffD){
		  sprintf(field, "%ld %ld %lf", 
			  pool[ib]->type, pool[ia]->type, cutoffD);
		}
		else{
		  hd_core = hd[seqIndex[i]][seqIndex[j]];
		  ener = 10;
		  if(temp<hd_core){
		    printf("too small distance between atoms %ld and %ld: %lf < %lf\n",ib, ia, temp, hd_core);
		    sprintf(field, "%ld %ld %lf %lf %lf %lf %lf %lf %lf", 
			    pool[ib]->type, pool[ia]->type, d0, temp-0.001, ener, hd_core, ener, cutoffD, -ener);
		  }
		  else{
		    sprintf(field, "%ld %ld %lf %lf %lf %lf %lf", 
			    pool[ib]->type, pool[ia]->type, d0, hd_core, ener, cutoffD, -ener);
		  }
		}
		txtout<< field << endl;
	      }
	    }
	  }
	}
      }
      txtout<< "E.ELASTIC COLLISIONS"<<endl;
      txtout<< "//pair types, repulsive dist"<<endl;
      
      txtout<< "F.LINKED PAIRS"<<endl;
      txtout<<"//pair types, repulsive dist, attractive distace"<<endl;
      ener = 10;
      const double minCACA = 10.0*(1-0.12/3.80);
      const double maxCACA = 10.0*(1+0.12/3.80);
      sprintf(field, "1 2 %lf %lf %lf %lf %lf %lf", minCACA-1.0, minCACA, ener, maxCACA, -ener, maxCACA+1.0); txtout << field << endl;
      
      const double min_alpha = (5.48-0.25)*unit, max_alpha = (5.48+0.25)*unit;
      const double min_beta = (6.60-0.45)*unit, max_beta = (6.60+0.45)*unit;
      sprintf(field, "1 1 %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", min_alpha-1.0, min_alpha, ener, max_alpha, -ener/10, 
	      min_beta, ener/10, max_beta, -ener, max_beta+1.0); 
      txtout << field << endl;
      sprintf(field, "2 2 %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", min_alpha-1.0, min_alpha, ener, max_alpha, -ener/10, 
	      min_beta, ener/10, max_beta, -ener, max_beta+1.0); 
      txtout << field << endl;
      
      const double minCACB=(1.53-0.037)*unit, maxCACB=(1.53+0.037)*unit;
      const double minCAnCB=(4.63-0.30)*unit, maxCAnCB=(4.63+0.30)*unit;
      for(int i=0; i<naa; i++){
	if(revIndex[caIndex[i]]!=0){
	  int ib = pool[cbIndex[i]]->type;
	  int ia = pool[caIndex[i]]->type;
	  ener = 10;
	  sprintf(field, "%ld %ld %lf %lf %lf %lf %lf %lf", ib, ia, minCACB-1.0, minCACB, ener, maxCACB, -ener, maxCACB+1.0);
	  txtout << field << endl;
	  int ica = (ia%2)+1;
	  sprintf(field, "%ld %ld %lf %lf %lf %lf %lf %lf", ib, ica, minCAnCB-2.0, minCAnCB, ener, maxCAnCB, -ener, maxCAnCB+2.0);
	  txtout << field << endl;
	}
      }
      
      txtout << "G.REACTIONS" <<endl;
      txtout << "//old1,old2,new1,new2,bond,radius energy" <<endl;
      
      double vxyz[ntotal][3],vcm[3];
      int idum;
      double Temp=0.01;
      idum=-17;
      ran1(&idum);
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
	sprintf(field, "%ld %ld %lf %lf %lf %lf %lf %lf",
		i+1, pool[i]->type, partxyz[i][0], partxyz[i][1], partxyz[i][2],
		vx, vy, vz);
	txtout << field << endl;
      }
      for(int i=npart; i<ntotal;i++){
	double vx,vy,vz;
	x=ghostxyz[i-npart][0];
	y=ghostxyz[i-npart][1];
	z=ghostxyz[i-npart][2];
	vx=vxyz[i][0];
	vy=vxyz[i][1];
	  vz=vxyz[i][2];
	  sprintf(field, "%ld %ld %lf %lf %lf %lf %lf %lf",
		  i+1, npart+1, x, y, z, vx, vy, vz);
	  txtout << field << endl;
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
    }
}

void nrerror(char* error_text)
{
    fprintf(stderr,"Numerical Recipes run-time error...\n");
    fprintf(stderr,"%s\n",error_text);
    fprintf(stderr,"...now exiting to system...\n");
    exit(1);
}

float gasdev(int* idum)
{
    static int iset=0;
    static float gset;
    float fac,r,v1,v2;
    
    if  (iset == 0) {
	do {
	    v1=2.0*ran1(idum)-1.0;
	    v2=2.0*ran1(idum)-1.0;
	    r=v1*v1+v2*v2;
	} while (r >= 1.0);
	fac=sqrt(-2.0*log(r)/r);
	gset=v1*fac;
	iset=1;
	return v2*fac;
    } else {
	iset=0;
	return gset;
    }
}

#define M1 259200
#define IA1 7141
#define IC1 54773
#define RM1 (1.0/M1)
#define M2 134456
#define IA2 8121
#define IC2 28411
#define RM2 (1.0/M2)
#define M3 243000
#define IA3 4561
#define IC3 51349

float ran1(int* idum){
    static long ix1,ix2,ix3;
    static float r[98];
    float temp;
    static int iff=0;
    int j;
    
    if (*idum < 0 || iff == 0) {
	iff=1;
	ix1=(IC1-(*idum)) % M1;
	ix1=(IA1*ix1+IC1) % M1;
	ix2=ix1 % M2;
	ix1=(IA1*ix1+IC1) % M1;
	ix3=ix1 % M3;
	for (j=1;j<=97;j++) {
	    ix1=(IA1*ix1+IC1) % M1;
	    ix2=(IA2*ix2+IC2) % M2;
	    r[j]=(ix1+ix2*RM2)*RM1;
	}
	*idum=1;
    }
    ix1=(IA1*ix1+IC1) % M1;
    ix2=(IA2*ix2+IC2) % M2;
    ix3=(IA3*ix3+IC3) % M3;
    j=1 + ((97*ix3)/M3);
    if (j > 97 || j < 1) nrerror("RAN1: This cannot happen.");
    temp=r[j];
    r[j]=(ix1+ix2*RM2)*RM1;
    return temp;
}

#undef M1
#undef IA1
#undef IC1
#undef RM1
#undef M2
#undef IA2
#undef IC2
#undef RM2
#undef M3
#undef IA3
#undef IC3
