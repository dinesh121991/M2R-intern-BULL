#!/bin/bash

np=$1
ESP=/home_nfs/georgioy/BENCHS/esp-2.2.1/

if [ $np == 1 -o $np == 2 ]; then
        np=3
fi
echo $np
mpirun -n $np $ESP/bin/pchksum -v -t 15
