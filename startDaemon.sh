#!/bin/bash

for i in `seq 1 3`; do cd iFoldDaemon${i}; ./iFoldDaemon.sh ; 
cd ..; done
