#!/bin/bash
ps aux | grep -v grep | grep iFoldManager.jar | awk '{print $2}' | while IFS= read -r line; do kill $line; done
sleep 3
nohup java -jar ./iFoldManager.jar &
