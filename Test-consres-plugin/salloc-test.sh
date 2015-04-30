#!/bin/bash 
salloc -v --ntasks-per-node=5 --mincpus=10 --cpus-per-task=3 -n10 -N2

salloc -v --contiguous --cores-per-socket=2 --cpus-per-task=2 --exclusive --distribution=block --mem=2000 --mem-per-cpu=200 --mincpus=13 --ntasks-per-core=3 --ntasks-per-socket=5 --ntasks-per-node=10 --overcommit  --sockets-per-node=2 --switches=2 --threads-per-core=3 -n20 -N4 

salloc --ntasks-per-node=5 --mincpus=10 --cpus-per-task=2 -n10 -N2

salloc --ntasks-per-node=5 --mincpus=10 --cpus-per-task=2 -n20 -N2

salloc --ntasks-per-node=5 --mincpus=10 --cpus-per-task=2 -n15 -N2

salloc --ntasks-per-node=5 --mincpus=15 --cpus-per-task=2 -n10 -N2 # It will not work,contradict

salloc --ntasks-per-socket=2 --mincpus=10 --cpus-per-task=2 -n12 -N2 #  Perfect but not allocatable

salloc --ntasks-per-node=5 --mincpus=10 --cpus-per-task=2 -n16 -N2 # It will not work,contradict. Because --ntasks-per-node=5*--cpus-per-task=2 == -n16 

salloc --ntasks-per-socket=2 --mincpus=10 --cpus-per-task=2 -n12 -N2 # It will not work,contradict

salloc --ntasks-per-node=5 --mincpus=10 --cpus-per-task=2 -n12 -N2 # It will not work,contradict

salloc --ntasks-per-node=8 --mincpus=16 --cpus-per-task=2 -n16 -N2 # It is the perfect allocation

salloc -v --contiguous --cores-per-socket=1 --cpus-per-task=2  --distribution=block --mem=2000 --mem-per-cpu=200 --mincpus=16 --sockets-per-node=1 --threads-per-core=4 -n10 -N2

salloc -v --contiguous --cores-per-socket=2 --cpus-per-task=2  --distribution=block --mem=2000 --mem-per-cpu=200 --mincpus=16 --sockets-per-node=2 --threads-per-core=4 -n10 -N2 # Sockets and Cores are having set affinity and get affinity


salloc --ntasks-per-node=3 --ntasks-per-core=2 --cpus-per-task=2 -n6 -N3

salloc -n100 -N38
