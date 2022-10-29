#!/bin/bash

if [ $# -le 2 ]
then
  echo "Usage: $0 directory $1,.. letters to uppercase"
  exit 1
fi

for i in `ls $1`
do
    if [  
    mv $1/$i $1/`echo $i | tr A-Z a-z`
done
