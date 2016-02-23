#!/bin/bash
for NUMBER in `seq 1 450`
do

  if [ $NUMBER -eq 201 ]
  then
    continue
  fi


  INPUTFILENAME=$NUMBER.txt

  if [ ! -e $INPUTFILENAME ]
  then
    continue
  fi

  LENGTH=`head -1 $INPUTFILENAME | egrep -v "@" | wc -c`

  if [ $LENGTH -gt 0 ]
  then
    echo $INPUTFILENAME
  fi


done