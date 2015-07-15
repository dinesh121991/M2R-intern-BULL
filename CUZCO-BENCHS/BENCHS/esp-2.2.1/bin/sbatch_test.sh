#!/bin/bash

np=$1

if [ $np == 1 -o $np == 2 ]; then
        np=3
fi
echo $np
mpirun -n $np ./pchksum -v -t 20

