#include "PDBLib-NChain.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;

int main(int argc, char* argv[]){
  if(argc<3){
    cout << "usage: command PDB seq_f" << endl;
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
  //sprintf(buf, "%ld %lf", naa, size);
  //out << buf << endl;
  
  atom* theAtom;
  int index=0;
  for(int i=0; i<naa; i++){
    out << p.getElementAt(i)->getName() << endl;
  }
  out.close();
}