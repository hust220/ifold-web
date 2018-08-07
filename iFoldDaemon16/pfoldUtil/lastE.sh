#! /bin/bash

tail -n 10 $1 | awk 'BEGIN {sum=0; i=0} {sum+=$3} {i++} END { print sum/i }'
