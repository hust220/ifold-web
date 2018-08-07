#!/bin/sh
set -e
perl runDMD.pl init.txt 0.6 1.0E-4 0.6 50000.0
 perl runDMD.pl init.txt 0.7 1.0E-4 0.7 50000.0
 perl runDMD.pl init.txt 0.8 1.0E-4 0.8 50000.0
 perl runDMD.pl init.txt 0.9 1.0E-4 0.9 50000.0
 perl runDMD.pl init.txt 1.0 1.0E-4 1.0 50000.0
 perl runDMD.pl init.txt 1.1 1.0E-4 1.1 50000.0
 