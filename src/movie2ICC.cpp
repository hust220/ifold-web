#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "movie.h"
#include "PDBLib-NChain.h"
/*-------------------------------------------
  This program read the movie file using movie class and 
  convert a sepcified frames into pdb format. It can works 
  for multiple proteins. 
  
  The model can be either 4bead or 2bead
  
  Author: Feng Ding
  fding@bu.edu
  -------*/

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


class contacts{
public:
  int iaa;
  int jaa;
  int ich;
  int jch;
  
  contacts(int ia, int ic, int ja, int jc){
    iaa=ia;
    ich=ic;
    jaa=ja;
    jch=jc;
  }
  
  ~contacts(){}
  
  contacts(const contacts& theContact){
    iaa = theContact.iaa;
    ich = theContact.ich;
    jaa = theContact.jaa;
    jch = theContact.jch;
  }
};

int main(int argc, char* argv[]){
  if(argc<6){
    cout << "usage: mov2pdbs.linux movie(bin) origPDB outLIST aamodel[4/2] fixProt [initFrame nFrame]" << endl;
    cout << "  movie    -- the binary movie file stored by DMD" << endl;
    cout << "  origPDB  -- the original PDB" << endl;
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

  protein p(ipdb);
  int na = p.getLength();

  char* amino[na];
  char chainID[na];
  int nGLY=0;
  int ca[na];
  int nres=0;
  for(int i=0; i<na; i++){
    int t = AminoToNum(cstr(p.getElementAt(i)->getName()).getStr());
    amino[i] = NumToAmino(t);
    if(p.getElementAt(i)->getName()=="GLY"){
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
  
  int nchain = p.getNChains();
  int istart, length;
  for(int i=0; i<nchain; i++){
    p.getChainInfor(i,istart, length);
    for(int j=0; j<length; j++){
      chainID[istart+j]='A'+i;
    }
  }

  /*calculate the native Chain-Chain contacts*/
  double** NCont = new double*[nchain];
  NCont[0]= new double[nchain*nchain];
  for(int i=1; i<nchain; i++) NCont[i] = NCont[i-1]+nchain;
  
  /*frequency between chains*/
  double** FREQ = new double*[nchain];
  FREQ[0]= new double[nchain*nchain];
  for(int i=0; i<nchain*nchain; i++) FREQ[0][i]=0;
  for(int i=1; i<nchain; i++) FREQ[i] = FREQ[i-1]+nchain;
  
  double** Cont = new double*[nchain];
  Cont[0]= new double[nchain*nchain];
  for(int i=1; i<nchain; i++) Cont[i] = Cont[i-1]+nchain;
  
  
  vector<contacts> contact_list;
  for(int ich=0; ich<nchain; ich++){
    int istart, ilength;
    p.getChainInfor(ich, istart, ilength);
    for(int jch=ich+1; jch<nchain; jch++){
      int jstart, jlength;
      p.getChainInfor(jch, jstart, jlength);
      int nContact=0;
      for(int iaa=0; iaa<ilength; iaa++){
	atom* iatom = NULL;
	if(p.getElementAt(istart+iaa)->getName()!="GLY")
	  iatom = p.getElementAt(istart+iaa)->getAtomAt(1);
	else
	  iatom = p.getElementAt(istart+iaa)->getAtomAt(0);
	for(int jaa=0; jaa<jlength; jaa++){
	  atom* jatom = NULL;
	  if(p.getElementAt(jstart+jaa)->getName()!="GLY")
	    jatom = p.getElementAt(jstart+jaa)->getAtomAt(1);
	  else
	    jatom = p.getElementAt(jstart+jaa)->getAtomAt(0);
	  
	  double dist = iatom->getDist(*jatom);
	  if(dist<7.5){
	    contact_list.push_back(contacts(istart+iaa, ich,jstart+jaa, jch));
	    nContact++;
	  }
	}
      }
      NCont[ich][jch]=NCont[jch][ich]=nContact;
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
  if(argc>7) nframes = atoi(argv[7]);
  int dN = 0;
  if(argc>8) dN = atoi(argv[8]);

  int np=(int)(npart/nres);
  npart = nres;
  if(npart%nres!=0){
    cout << "The input PDB is not compatible with the movie!" << endl;
    exit(1);
  }
  
  //cout << boundary << endl;
  ofstream out(opdb);
  double coef=1;
  double range = 10;
  m.jumpto(start-1);
  m.nextFrame();
  int iframe=1;
  //cout << nmax << " " << nframes << " " << dN << endl;
  //cout << np << " " << na << endl;
  while(iframe<=nframes){
    {
      //out << iframe << endl;
      double cm[np][3];
      
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
	    if(p.getElementAt(i)->getName()!="GLY"){
	      x=r[j][0]; y=r[j][1]; z=r[j][2]; j++;//CA
	      *(p.getElementAt(i)->getAtomAt(0)->getR()) = 
		vec(x,y,z);
	      x=r[j][0]; y=r[j][1]; z=r[j][2]; j++;
	      *(p.getElementAt(i)->getAtomAt(1)->getR()) = 
		vec(x,y,z);
	    }
	    else{
	      x=r[j][0]; y=r[j][1]; z=r[j][2]; j++;
	      *(p.getElementAt(i)->getAtomAt(0)->getR()) = 
		vec(x,y,z);
	    }
	  }
	}

	for(int ii=0; ii<nchain*nchain; ii++)Cont[0][ii]=0;

	double dist;
	for(int icont=0;icont<contact_list.size();icont++){
	  int iaa = contact_list[icont].iaa;
	  int jaa = contact_list[icont].jaa;
	  int ich = contact_list[icont].ich;
	  int jch = contact_list[icont].jch;

	  //cout<<iaa<<" " << ich << " " << jaa << " " << jch << endl;
	  atom* iatom = NULL;
	  if(p.getElementAt(iaa)->getName()!="GLY")
	    iatom = p.getElementAt(iaa)->getAtomAt(1);
	  else
	    iatom = p.getElementAt(iaa)->getAtomAt(0);
	  
	  atom* jatom = NULL;
	  if(p.getElementAt(jaa)->getName()!="GLY")
	    jatom = p.getElementAt(jaa)->getAtomAt(1);
	  else
	    jatom = p.getElementAt(jaa)->getAtomAt(0);
	  
	  dist = iatom->getDist(*jatom);
	  if(dist<7.5){
	    Cont[ich][jch]+=1;
	    Cont[jch][ich]+=1;
	  }
	}

	for(int ich=0; ich<nchain; ich++){
	  for(int jch=ich+1; jch<nchain; jch++){
	    if(NCont[ich][jch]){
	      out<<ich+1<<" "<<jch+1<<" "<<Cont[ich][jch]<<" "<<Cont[ich][jch]/NCont[ich][jch]<<endl;
	      FREQ[ich][jch]+=static_cast<double>(Cont[ich][jch])/NCont[ich][jch];
	      FREQ[jch][ich]+=static_cast<double>(Cont[ich][jch])/NCont[ich][jch];
	    }
	  }
	}
	out << endl;
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
    //for(int k=0; k<dN; k++){
    //  if(m.nextFrame() && iframe<nframes){
    //	cout << "error in reading movie" << endl;
    //	break;
    //  }
    //  else iframe++;
    //}
    if(m.nextFrame() && iframe<nframes){        
      cerr << "error in reading movie" << endl; 
      break;          
    }           
    else iframe++;          
  }
  out.close();

  for(int ich=0;ich<nchain;ich++){
    for(int jch=ich+1;jch<nchain;jch++){
      cout << ich+1 << " " << jch+1 << " " << FREQ[ich][jch]/static_cast<double>(iframe) << endl;
    }
  }

  return 0;
}
