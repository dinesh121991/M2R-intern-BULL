#!/bin/sh
#SBATCH -J helloworld
#SBATCH -n 16
##SBATCH -t 20
##SBATCH -p all
#SBATCH -o /home_nfs/georgioy/BENCHS/helloworld/hello.out
source /opt/mpi/bullxmpi/1.1.11.1/bin/mpivars.sh
source /opt/intel/Compiler/11.1/072/bin/intel64/iccvars_intel64.sh

NPB=/home_nfs/georgioy/BENCHS/helloworld

 mpirun -np 16 $NPB/helloworld


exit
