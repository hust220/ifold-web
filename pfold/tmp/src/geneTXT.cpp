#include "PDBLib.h"
#include "random.h"
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

struct satom{
public:
  char* carbon;
  char* residue;
  int index;
  double x;
  double y;
  double z;
};

typedef struct satom* ATOM;

char* Carbon[2]=
{
  "CA", "CB"
};

ATOM AtomNew(char* carbon, char* res, double x, double y, double z)
{
  ATOM satom = (ATOM)malloc(sizeof(struct satom));
  satom->carbon = carbon;
  satom->residue = res;
  satom->x = x;
  satom->y = y;
  satom->z = z;
  return satom;
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

double getDist(ATOM a, ATOM b){
  double d=0;
  d+= (a->x-b->x)*(a->x-b->x);
  d+= (a->y-b->y)*(a->y-b->y);
  d+= (a->z-b->z)*(a->z-b->z);
  return sqrt(d);
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
  

int main(int argc, char* argv[]){
  if(argc<5){
    printf("usage: geneTXT.linux origPDB confPDB boxSIZE random_seed\n");
    exit(1);
  }

  protein p(argv[1],1,7.5);
  
  vector<ATOM> pool;
  int naa=readPDB(argv[2], pool);
  for(int i=0; i<pool.size(); i++){
    pool[i]->index = i+1;
  }

  
  if(naa!=p.getLength()){
    cerr << "mismatching of lengths between " 
	 << argv[1] << " " << argv[2] << endl;
    exit(1);
  }
  
  double size = atof(argv[3]);
  int seed = atol(argv[4]);
  int npart = pool.size();
  
  int* ca_index = new int[naa];
  int* cb_index = new int[naa];
  int index=0;
  for(int i=0; i<p.getLength(); i++){
    ca_index[i] = index;
    if(p.getElementAt(i)->getName()=="GLY"){
      cb_index[i] = index;
      index+=1;
    }
    else{
      cb_index[i] = index+1;
      index+=2;
    }
  }

  if(index!=npart){
    cerr << "mismatching of sequences between " 
	 << argv[1] << " " << argv[2] << endl;
    exit(1);
  }
  
  //creat txt
  cout << "A.SYSTEM SIZE" <<endl;
  cout << size << " " << size << " " << size << endl;
  
  cout << "B.NUMBER OF ATOMS" << endl;
  cout << npart <<endl;
  
  double hcD  = 3.32;
  double hcR  = hcD/2.0;
  double iD   = 7.5;
  double iR   = iD/2.0;
  double mass = 1.0;
  double eATTR = -1.0;
  double eREP  = 1.0;
  
  cout << "C.TYPES OF ATOMS" <<endl;
  cout << "//type,mass,ellastic radius,interaction radius" <<endl;
  for(int i=0; i<npart; i++){
    printf("%ld %lf %lf %lf\n",i+1,mass,hcR,iR);
  }
  
  cout << "D.NON-ELASTIC COLLISIONS"<<endl;
  cout <<"//pair types, repulsive dist, interaction distance, energy"<<endl;

  for(int i=0; i<naa; i++){
    for(int j=i+2; j<naa; j++){
      if(p.getCMap()[i][j]){
	printf("%ld %ld %lf %lf %lf\n", cb_index[i]+1, cb_index[j]+1, hcD, iD, eATTR);
      }
      else{
	printf("%ld %ld %lf %lf %lf\n", cb_index[i]+1, cb_index[j]+1, hcD, iD, eREP);
      }
    }
  }
  
  cout<< "E.ELASTIC COLLISIONS"<<endl;
  cout<< "//pair types, repulsive dist"<<endl;
  
  cout<< "F.LINKED PAIRS"<<endl;
  cout<<"//pair types, repulsive dist, attractive distace"<<endl;
  
  double cacbDev=0.02, cacanDev=0.02, cacbnDev=0.034, cacannDev=0.08;
  double dmin, dmax;
  for(int i=0; i<naa; i++){
    //CACB
    if(strcmp(pool[ca_index[i]]->residue,"GLY")==0){
      if(ca_index[i]!=cb_index[i]){
	cout << "error" << endl;
	exit(1);
      }
    }
    else{
      if(ca_index[i]==cb_index[i]){
	cout << "error" << endl;
	exit(1);
      } 
      double the_dist = getDist(pool[ca_index[i]], pool[cb_index[i]]);
      double dist = p.getElementAt(i)->getAtomAt(0)->getDist(*p.getElementAt(i)->getAtomAt(1));
      dmin = dist*(1-cacbDev);
      dmax = dist*(1+cacbDev);
      if(the_dist < dmin){
	dmin = the_dist - 0.0001;
      }
      if(the_dist > dmax){
	dmax = the_dist + 0.0001;
      }
      printf("%ld %ld %lf %lf\n", ca_index[i]+1, cb_index[i]+1, dmin, dmax);
    }
    if(i>0){
      //CAnCA
      double the_dist = getDist(pool[ca_index[i-1]], pool[ca_index[i]]);
      double dist = p.getElementAt(i-1)->getAtomAt(0)->getDist(*p.getElementAt(i)->getAtomAt(0));
      dmin = dist*(1-cacanDev);
      dmax = dist*(1+cacanDev);
      if(the_dist < dmin){
	dmin = the_dist - 0.0001;
      }
      if(the_dist > dmax){
	dmax = the_dist + 0.0001;
      }
      printf("%ld %ld %lf %lf\n", ca_index[i-1]+1, ca_index[i]+1, dmin, dmax);
      //CAnCB
      if(strcmp(pool[ca_index[i]]->residue,"GLY")!=0){
	the_dist = getDist(pool[ca_index[i-1]], pool[cb_index[i]]);
	dist = p.getElementAt(i-1)->getAtomAt(0)->getDist(*p.getElementAt(i)->getAtomAt(1));
	dmin = dist*(1-cacbnDev);
	dmax = dist*(1+cacbnDev);
	if(the_dist < dmin){
	  dmin = the_dist - 0.0001;
	}
	if(the_dist > dmax){
	  dmax = the_dist + 0.0001;
	}
	printf("%ld %ld %lf %lf\n", ca_index[i-1]+1, cb_index[i]+1, dmin, dmax);
      }
      //CBnCA
      if(strcmp(pool[ca_index[i-1]]->residue,"GLY")!=0){
	the_dist = getDist(pool[cb_index[i-1]], pool[ca_index[i]]);
	dist = p.getElementAt(i-1)->getAtomAt(1)->getDist(*p.getElementAt(i)->getAtomAt(0));
	dmin = dist*(1-cacbnDev);
	dmax = dist*(1+cacbnDev);
	if(the_dist < dmin){
	  dmin = the_dist - 0.0001;
	}
	if(the_dist > dmax){
	  dmax = the_dist + 0.0001;
	}
	printf("%ld %ld %lf %lf\n", cb_index[i-1]+1, ca_index[i]+1, dmin, dmax);
      }
    }
    if(i>1){
      //CAnnCA
      double the_dist = getDist(pool[ca_index[i-2]], pool[ca_index[i]]);
      double dist = p.getElementAt(i-2)->getAtomAt(0)->getDist(*p.getElementAt(i)->getAtomAt(0));
      dmin = dist*(1-cacannDev);
      dmax = dist*(1+cacannDev);
      if(the_dist < dmin){
	dmin = the_dist - 0.0001;
      }
      if(the_dist > dmax){
	dmax = the_dist + 0.0001;
      }
      printf("%ld %ld %lf %lf\n", ca_index[i-2]+1, ca_index[i]+1, dmin, dmax);
    }
  }
  
  cout << "G.REACTIONS" <<endl;
  cout << "//old1,old2,new1,new2,bond,radius energy" <<endl;
  
  cout << "H.LIST OF ATOMS" <<endl;
  cout << "//number, type, x, y, z, Vx, Vy, Vz" << endl;
  
  randomGenerator rand(_RAN2_, -abs(seed));
  for(int i=0; i<npart; i++){
    printf("%ld %ld %lf %lf %lf %lf %lf %lf\n",i+1,i+1,
	   pool[i]->x, pool[i]->y, pool[i]->z,
	   rand.nextGauss(),rand.nextGauss(),rand.nextGauss());
  }

  cout<<"I.LIST OF BONDS"<<endl;
  cout<<"//number1, number2"<<endl;
  for(int i=0; i<naa; i++){
    
    if(strcmp(pool[ca_index[i]]->residue,"GLY")!=0){
      printf("%ld %ld\n", ca_index[i]+1, cb_index[i]+1);
    }
    if(i>0){
      printf("%ld %ld\n", ca_index[i-1]+1, ca_index[i]+1);
      if(strcmp(pool[ca_index[i]]->residue,"GLY")!=0){
	printf("%ld %ld\n", ca_index[i-1]+1, cb_index[i]+1);
      }
      if(strcmp(pool[ca_index[i-1]]->residue,"GLY")!=0){
	printf("%ld %ld\n", cb_index[i-1]+1, ca_index[i]+1);
      }
    }
    if(i>1){
      printf("%ld %ld\n", ca_index[i-2]+1, ca_index[i]+1);
    }
  }

}
