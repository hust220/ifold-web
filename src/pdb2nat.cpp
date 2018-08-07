#include "pseudoPep.h"
#include "PDBLib-NChain.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;

int main(int argc, char* argv[]){
  if(argc<3){
    cout << "usage: command PDB nat_f" << endl;
    exit(1);
  }

  protein p(argv[1]);
  double size = 10.0*p.getRg();
  cout << size  << endl;
  cout << p.getLength() << endl;
  bool two_bead=false;
  for(int i=0; i<p.getLength(); i++){
    if(!p.getElementAt(i)->getN() ||
       !p.getElementAt(i)->getC()){
      two_bead=true;
      break;
    }
  }
  if(two_bead){
    //cout << "tow bead" << endl;
    ofstream out(argv[2]);
    char buf[1024];
    sprintf(buf, "%ld %lf", p.getLength(), size);
    out << buf << endl;
    int index=0;
    for(int i=0; i<p.getLength(); i++){
      atom* theAtom = p.getElementAt(i)->getAtomAt(0);
      sprintf(buf, "%ld %lf %lf %lf", 
	      index,
	      theAtom->getR()->getX(),
	      theAtom->getR()->getY(),
	      theAtom->getR()->getZ());
      out << buf << endl;
      if(p.getElementAt(i)->getName()=="GLY"){
	index++;
      }
      else{
	index+=2;
      }
    }
    out.close();
    exit(0);
  }



  pseudoPep prot(argv[1], _PDB_BB_);
  prot.constructHydrogen();
  //prot.makeIndex_Backbone();
  prot.makeIndex_CACB();
  int naa = prot.getLength();
  
  
  ofstream out(argv[2]);
  char buf[1024];
  sprintf(buf, "%ld %lf", naa, size);
  out << buf << endl;
  
  atom* theAtom;
  for(int i=0; i<naa; i++){
    theAtom = prot.getResidue(i)->getCA();
    sprintf(buf, "%ld %lf %lf %lf", 
	    theAtom->getIndex()-1,
	    theAtom->getR()->getX(),
	    theAtom->getR()->getY(),
	    theAtom->getR()->getZ());
    out << buf << endl;
  }
  out.close();
}
