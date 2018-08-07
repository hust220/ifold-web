#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <vector>
using namespace std;

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

int main(int argc, char* argv[])
{
  char name[20];
  char pdbname[20], field[100];
  
  if(argc < 6) 
    {
      cout << "Usage: command txtFILE np origPDB outPDBfile convertCOEF\n";
      return -2;
    }
  
  vector<int> aalist;
  readPDB(argv[3], aalist);
  int np= atoi(argv[2]);
  int na = aalist.size();
  int nres=0;
  int ca[na], cb[na];
  char* amino[na];
  for(int i=0; i<na; i++)
    {
      amino[i]=NumToAmino(aalist[i]);
      if(strcmp(amino[i],"GLY")!=0)
	{
	  nres++;
	  ca[i]=nres;
	  nres++;
	  cb[i]=nres;
	}
      else
	{
	  nres++;
	  ca[i]=nres;
	  cb[i]=nres;
	}
    }
  
  fstream in;
  in.open(argv[1],ios::in);
  if(!in)
    {
      cout << "no such file!" << endl;
      return -1;
    }
  
  fstream out;
  out.open(argv[4],ios::out);
  
  double convcoef;
  convcoef = atof(argv[5]);
  
  static double boundary=400;    
  
  string line ;
  static string Afield = "A.SYSTEM SIZE";
  while(line!=Afield) getline(in,line);
  in >> boundary >> boundary >> boundary;
  /*
    static string Bfield = "B.NUMBER OF ATOMS";
    while(line!=Bfield) getline(in,line);
    in >> npart;
    
    int np = npart/nres;
    cout << np << " proteins" << endl;
  */
  int npart=np*nres;
  
  static string Hfield = "H.LIST OF ATOMS";
  getline(in, line);
  while(line!=Hfield) getline(in,line);
  getline(in,line);
  
  {
    double range = 10*convcoef;
    int natom, tmp;
    double x,y,z,junk;
    
    double x0[npart], y0[npart], z0[npart];
    for(int i=0; i<npart; i++)
      in >> natom >> tmp >> x0[i] >> y0[i] >> z0[i] >> junk >> junk >> junk;
    
    double cm[np][3];
    for(int ip=0; ip<np; ip++){
      cm[ip][0]=x0[ip*nres];
      cm[ip][1]=y0[ip*nres];
      cm[ip][2]=z0[ip*nres];
      for(int i=1+ip*nres; i<nres*(ip+1); i++){
	if(x0[i]-x0[i-1] > boundary/2.0f  && x0[i-1]+boundary-x0[i]<range) x0[i]-=boundary;
	if(x0[i]-x0[i-1] < -boundary/2.0f && x0[i]+boundary-x0[i-1]<range) x0[i]+=boundary;
	if(y0[i]-y0[i-1] > boundary/2.0f  && y0[i-1]+boundary-y0[i]<range) y0[i]-=boundary;
	if(y0[i]-y0[i-1] < -boundary/2.0f && y0[i]+boundary-y0[i-1]<range) y0[i]+=boundary;
	if(z0[i]-z0[i-1] > boundary/2.0f  && z0[i-1]+boundary-z0[i]<range) z0[i]-=boundary;
	if(z0[i]-z0[i-1] < -boundary/2.0f && z0[i]+boundary-z0[i-1]<range) z0[i]+=boundary;
	cm[ip][0]+=x0[i];
	cm[ip][1]+=y0[i];
	cm[ip][2]+=z0[i];
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
	for(int i= imin*nres; i<(imin+1)*nres; i++) x0[i]-=boundary;
      }
      if(cm[imin][0]-cmCurr[0]<-boundary/2.0f){
	cm[imin][0]+=boundary;
	for(int i= imin*nres; i<(imin+1)*nres; i++) x0[i]+=boundary;
      }

      if(cm[imin][1]-cmCurr[1]>boundary/2.0f){
	cm[imin][1]-=boundary;
	for(int i= imin*nres; i<(imin+1)*nres; i++) y0[i]-=boundary;
      }
      if(cm[imin][1]-cmCurr[1]<-boundary/2.0f){
	cm[imin][1]+=boundary;
	for(int i= imin*nres; i<(imin+1)*nres; i++) y0[i]+=boundary;
      }
      
      if(cm[imin][2]-cmCurr[2]>boundary/2.0f){
	cm[imin][2]-=boundary;
	for(int i= imin*nres; i<(imin+1)*nres; i++) z0[i]-=boundary;
      }
      if(cm[imin][2]-cmCurr[2]<-boundary/2.0f){
	cm[imin][2]+=boundary;
	for(int i= imin*nres; i<(imin+1)*nres; i++) z0[i]+=boundary;
      }
      alloc[imin]=0;
    }

    for(int i=0; i<3; i++)cmCurr[i]=cm[0][i];
    for(int ip=0; ip<np;ip++)
      for(int i=0;i<3;i++)cmCurr[i]+=cm[ip][i];
    for(int i=0; i<3; i++)cmCurr[i]/=(double)np;
    for(int i=0; i<npart; i++){
      x0[i]-=(cmCurr[0]-boundary/2.0);
      y0[i]-=(cmCurr[1]-boundary/2.0);
      z0[i]-=(cmCurr[2]-boundary/2.0);
    }
    
    int j=0;
    for(int ip=0;ip<np;ip++){
      for(int i=0; i<na; i++)
	{
	  if(ca[i]!=cb[i]){
	    x=x0[j]; y=y0[j]; z=z0[j]; j++;
	    x/=convcoef;
	    y/=convcoef;
	    z/=convcoef;
	    sprintf(&field[0],"ATOM  %5d  CA  %3s C%4d    %8.3lf%8.3lf%8.3lf  1.00  0.00           C  ",
		    j,amino[i],i+1+ip*na,x,y,z);  
	    out << field << endl;
	    x=x0[j]; y=y0[j]; z=z0[j]; j++;
	    x/=convcoef;
	    y/=convcoef;
	    z/=convcoef;
	    sprintf(&field[0],"ATOM  %5d  CB  %3s C%4d    %8.3lf%8.3lf%8.3lf  1.00  0.00           C  ",
		    j,amino[i],i+1+ip*na,x,y,z); 
	    out << field << endl;
	  }
	  else{
	    x=x0[j]; y=y0[j]; z=z0[j]; j++;
	    x/=convcoef;
	    y/=convcoef;
	    z/=convcoef;
	    sprintf(&field[0],"ATOM  %5d  CA  %3s C%4d    %8.3lf%8.3lf%8.3lf  1.00  0.00           C  ",
		    j,amino[i],i+1+ip*na,x,y,z); 
	    out << field << endl;
	  }
	}
      //out << "TER" << endl;
    }
    
    out.close();
  }
  
  in.close();
  
  return 0;
}


