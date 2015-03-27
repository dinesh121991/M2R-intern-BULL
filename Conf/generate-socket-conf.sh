#!/bin/bash

for ((i=0;i<80;i++)); do
let j = 2 * $i
  echo "Entity=socket$i type=socket JobId=0 NumSumCores=0 FreeSumCores=0 AllocatedSumCores=0  ForWhatPurposePriority=0 BitmapPosition=0 Selected=0 AllocatedSocketCount=0 socketcount=1 Enclosed=core[$j-${j+1}]"
done

