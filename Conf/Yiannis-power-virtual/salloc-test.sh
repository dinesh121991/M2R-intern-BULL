#!/bin/bash

# single node allocation, sockets=2, cores=2 , threads-per-core=4

salloc -n4 -N1
salloc -n8 -N1
salloc -n4 -N1
salloc -n12 -N1
salloc -n16 -N1

# allocate 2 nodes level

salloc -n4 -N2
salloc -n8 -N2
salloc -n12 -N2
salloc -n16 -N2
salloc -n32 -N2

# allocate 5 nodes level

salloc -n32 -N5
salloc -n16 -N1
salloc -n40 -N5
salloc -n80 -N5

# allocate using other options 
