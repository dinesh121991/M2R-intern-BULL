#include<stdio.h>

int main( int argc, char*argv[] )
{
        int i=0,j=0,soc_end,core_end;
	int sockets_per_node =2,cores_per_socket=8,threads_per_core=1;
	int nb_of_nodes=4000,nb_of_sockets=nb_of_nodes*sockets_per_node,
	nb_of_cores = nb_of_sockets*cores_per_socket,nb_of_threads=nb_of_cores*threads_per_core;
	printf("Priority=10\nRoot=Cluster\n\n");
printf("#Root or Cluster level Layout configuration\n");

	printf("Entity=Cluster Type=Center NumSumNodes=0 NumSumSocketsInCluster=0 NumSumCoresInCluster=0 NumSumThreadsInCluster=0 AllocatedSumNodes=0 AllocatedSumSocketsInCluster=0 AllocatedSumCoresInCluster=0  AllocatedSumThreadsInCluster=0 Enclosed=virtual[0-%d]\n\n",(nb_of_nodes -1));

printf("# Compute node layout configuration \n");
        for( i=0,j=0 ; i < nb_of_nodes  ; i++,j++ )
        {
		soc_end = j+ ( sockets_per_node-1 );

                printf("Entity=virtual%d type=Node BitmapPosition=0 nodecount=1 AllocatedNodeCount=0 AllocatedSumSockets=0 AllocatedSumCoresInNode=0 AllocatedSumThreadsInNode=0 NumSumSockets=0 NumSumCoresInNode=0 NumSumThreadsInNode=0 Enclosed=socket[%d-%d] \n",i,j,soc_end);
		j = soc_end ;
        }
printf("#Socket Level layout configuration following\n");

	for( i=0,j=0 ; i< nb_of_sockets ; i++,j++ )
        {
		core_end = j + ( cores_per_socket - 1 ) ;
                printf("Entity=socket%d type=Socket BitmapPosition=0 socketcount=1 NumSumCores=0 NumSumThreads=0 AllocatedSocketCount=0 AllocatedSumCores=0 AllocatedSumThreads=0 Enclosed=core[%d-%d] \n",i,j,core_end);
		j = core_end ;
        }

printf("#Core level Layout configuration following\n");

	printf("Entity=core[0-%d] type=Core BitmapPosition=0 ThreadsPerCore=1 AllocatedThreadsPerCore=0 AllocatedCoreCount=0 corecount=1 Job=0",nb_of_cores-1);

	return 0;
}
