#!/bin/sh

i=0
SIZE=10

while [ $i -le $SIZE ];  do
        echo Submitting job $i
        np=$(($RANDOM%3+1))
        sbatch -n $np ./mpi_job.sh $np
        i=`expr $i + 1`
done

