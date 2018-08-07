#!/bin/bash

#for i in `seq 1 25`; do cp  -rf iFoldDaemon iFoldDaemon$i ; done
 
for i in `seq 1 25`; do cd iFoldDaemon${i}; echo  "#!/bin/bash" > iFoldDaemon.sh ; echo "java -jar ./iFoldDaemon.jar $[i+1338] &" >> iFoldDaemon.sh ; echo "exit 0" >> iFoldDaemon.sh; cd ..; done
