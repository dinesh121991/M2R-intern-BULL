
#include <stdio.h> 
#include <stdlib.h>  
#include <string.h>
#include <unistd.h>
#include <mpi.h>
#include <cuda_runtime.h>
#include <cuda.h>


//#define SIZE  31768
#define ITER 10000
int main(int argc,char **argv)
{
  int world_rank,world_size;
  MPI_Init (&argc, &argv);  
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  
  char hostname[255];
  hostname[254]= '\0';
  gethostname(hostname, 250);




  printf(" MPI RANK - %i - , runs on - %s - \n ",world_rank,hostname);
  
 int dev_count;
cudaGetDeviceCount(&dev_count);  	


printf("NUMBER OF CUDA DEVICES visible by the MPI RANK %i, --- %i\n",world_rank,dev_count);


  MPI_Finalize();
  return 0;
}
