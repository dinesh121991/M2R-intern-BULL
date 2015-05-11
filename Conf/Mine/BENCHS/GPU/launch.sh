#!/bin/sh

source /opt/mpi/bullxmpi/1.2.7.1/bin/mpivars.sh
export LD_LIBRARY_PATH+=":/opt/cuda/6.0/lib64:"
srun --mpi=pmi2 -n2 --gres=gpu:2 --multi-prog multi.conf
#srun --mpi=pmi2 -n2 --gres=gpu:2 ./test_new 300
