#include "mpi.h"
#include <stdio.h>

#define BUFLEN 512

int main (int argc, char ** argv) {
        int myid, numprocs, next, namelen, prev;
        int num;
        char buffer[BUFLEN], processor_name[MPI_MAX_PROCESSOR_NAME];
        MPI_Status status;

        MPI_Init(&argc,&argv);
        MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
        MPI_Comm_rank(MPI_COMM_WORLD,&myid);
        MPI_Get_processor_name(processor_name,&namelen);

	MPI_Barrier(MPI_COMM_WORLD);
	while (1);
        MPI_Finalize();
        return 0;
}
