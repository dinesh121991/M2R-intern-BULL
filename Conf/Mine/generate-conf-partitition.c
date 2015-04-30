#include<stdio.h>

int main( int argc, char*argv[] )
{
        int i=0,j=0;
	printf("Priority=10\nRoot=switch0\n\n");
printf("#Root or Cluster level Layout configuration\n");

	printf("Entity=Cluster Type=Center NumSumNodes=0 NumSumCoresInCluster=0 NumSumSocketsInCluster=0 SelectedSumNodes=0 SelectedSumCoresInCluster=0 SelectedSumSocketsInCluster=0 AllocatedSumNodes=0 AllocatedSumCoresInCluster=0 AllocatedSumSocketsInCluster=0 AllocatedSumThreadsInCluster=0 SelectedSumThreadsInCluster=0 NumSumThreadsInCluster=0 Enclosed=virtual[0-40]\n\n");

printf("# Compute node layout configuration \n");
        for( i=0 ; i< 41  ; i++ )
        {
                j= 2*i;

                printf("Entity=virtual%d type=Node nodecount=1 SelectedNodeCount=0 AllocatedNodeCount=0 NumSumSockets=0 NumSumCoresInNode=0 SelectedSumSockets=0 SelectedSumCoresInNode=0 AllocatedSumSockets=0 AllocatedSumCoresInNode=0 BitmapPosition=0 SelectedNodeCount=0 SelectedSumThreadsInNode=0 AllocatedSumThreadsInNode=0 NumSumThreadsInNode=0 Enclosed=socket[%d-%d] \n",i,j,j+1);
        }
printf("#Socket Level layout configuration following\n");

	for( i=0 ; i< 82 ; i++ )
        {
                j= 2*i;

                printf("Entity=socket%d type=Socket socketcount=1 NumSumCores=0 SelectedSumCores=0 AllocatedSumCores=0  BitmapPosition=0 SelectedSocketCount=0 AllocatedSocketCount=0 AllocatedSumThreads=0 SelectedSumThreads=0 NumSumThreads=0 Enclosed=core[%d-%d] \n",i,j,j+1);
        }

printf("#Core level Layout configuration following\n");

	printf("Entity=core[0-163] type=Core ThreadsPerCore=4 SelectedThreadsPerCore=0 AllocatedThreadsPerCore=0  BitmapPosition=0 SelectedCoreCount=0 AllocatedCoreCount=0 corecount=1");

	return 0;
}
