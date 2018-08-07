#!/bin/bash

awk 'BEGIN{nfold=0; nline=0;}{if($2<-85 && $3<5) nfold++; nline++;}END{printf("%f\n", nfold/nline);}' $1
