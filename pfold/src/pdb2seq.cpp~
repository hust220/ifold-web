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

  int first_chain_start;
  int first_chain_length;
  p.getChainInfor(0,first_chain_start,first_chain_length);
  
  
  int naa = first_chain_length;

  ofstream out(argv[2]);
  char buf[1024];
  sprintf(buf, "%ld %lf", naa, size);
  out << buf << endl;
  
  atom* theAtom;
  int index=0;
  for(int i=0; i<naa; i++){
    theAtom = p.getElementAt(i)->getAtomAt(0);
    sprintf(buf, "%ld %lf %lf %lf", 
	    index,
	    theAtom->getR()->getX(),
	    theAtom->getR()->getY(),
	    theAtom->getR()->getZ());
    out << buf << endl;
    if(p.getElementAt(i)->getName()=="GLY"){
      index+=1;
    }
    else{
      index+=2;
    }
  }
  out.close();
}
