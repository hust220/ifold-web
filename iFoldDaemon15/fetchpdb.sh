#!/bin/sh

E_BADARGS=65

if [ -z "$1" ]    # Check for argument to script.
then
echo "Usage: `basename $0` <Four-letter-PDB-code>"
exit $E_BADARGS
fi 

pdbfile=`echo $1 | tr 'A-Z' 'a-z'`
wget -q ftp://ftp.rcsb.org/pub/pdb/data/structures/all/pdb/pdb${pdbfile}.ent.Z
gunzip pdb${pdbfile}.ent.Z
mv pdb${pdbfile}.ent ${pdbfile}.pdb

