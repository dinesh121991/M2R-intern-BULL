#include<stdio.h>

int main( int argc, char*argv[] )
{
        int i=0,j=0;
	printf("Priority=10\nRoot=Cluster\n\n");
	printf("Priority=10\nRoot=switch0\n\n");
printf("#Root or Cluster level Layout configuration\n");

	printf("Entity=Cluster Type=Center NumSumNodesInCluster=0 NumSumCoresInCluster=0 NumSumSocketsInCluster=0 SelectedSumNodesInCluster=0 SelectedSumCoresInCluster=0 SelectedSumSocketsInCluster=0 AllocatedSumNodesInCluster=0 AllocatedSumCoresInCluster=0 AllocatedSumSocketsInCluster=0 AllocatedSumThreadsInCluster=0 SelectedSumThreadsInCluster=0 NumSumThreadsInCluster=0 Enclosed=virtual[0-40]\n\n");

printf("#switch or tree topolgy configuration\n");
	printf("Entity=switch0 Type=Switch NumSumNodesInLevel3=0 NumSumCoresInLevel3=0 NumSumSocketsInLevel3=0 SelectedSumNodesInLevel3=0 SelectedSumCoresInLevel3=0 SelectedSumSocketsInLevel3=0 AllocatedSumNodesInLevel3=0 AllocatedSumCoresInLevel3=0 AllocatedSumSocketsInLevel3=0 SelectedSumThreadsInLevel3=0 SwitchToProcessInLevel3=0 AllocatedSumThreadsInLevel3=0 SelectedSumThreadsInLevel3=0 NumSumThreadsInLevel3=0 Enclosed=switch[1-2]\n\n");

//	for( i=1 ; i<4 ; i++ )
	printf("Entity=switch1 Type=Switch NumSumNodesInLevel2=0 NumSumCoresInLevel2=0 NumSumSocketsInLevel2=0 SelectedSumNodesInLevel2=0 SelectedSumCoresInLevel2=0 SelectedSumSocketsInLevel2=0 AllocatedSumNodesInLevel2=0 AllocatedSumCoresInLevel2=0 AllocatedSumSocketsInLevel2=0 SelectedSumThreadsInLevel2=0 SwitchToProcessInLevel2=0 AllocatedSumThreadsInLevel2=0 SelectedSumThreadsInLevel2=0 NumSumThreadsInLevel2=0 Enclosed=switch[4-5]\n");

	printf("Entity=switch2 Type=Switch NumSumNodesInLevel0=0 NumSumCoresInLevel0=0 NumSumSocketsInLevel0=0 SelectedSumNodesInLevel0=0 SelectedSumCoresInLevel0=0 SelectedSumSocketsInLevel0=0 AllocatedSumNodesInLevel0=0 AllocatedSumCoresInLevel0=0 AllocatedSumSocketsInLevel0=0 SelectedSumThreadsInLevel0=0 SwitchToProcessInLevel0=0 AllocatedSumThreadsInLevel0=0 SelectedSumThreadsInLevel0=0 NumSumThreadsInLevel0=0 Enclosed=virtual[30-40]\n");

	printf("Entity=switch3 Type=Switch NumSumNodesInLevel1=0 NumSumCoresInLevel1=0 NumSumSocketsInLevel1=0 SelectedSumNodesInLevel1=0 SelectedSumCoresInLevel1=0 SelectedSumSocketsInLevel1=0 AllocatedSumNodesInLevel1=0 AllocatedSumCoresInLevel1=0 AllocatedSumSocketsInLevel1=0 SelectedSumThreadsInLevel1=0 SwitchToProcessInLevel1=0 AllocatedSumThreadsInLevel1=0 SelectedSumThreadsInLevel1=0 NumSumThreadsInLevel1=0 Enclosed=switch[6]\n");

	printf("Entity=switch4 Type=Switch NumSumNodesInLevel0=0 NumSumCoresInLevel0=0 NumSumSocketsInLevel0=0 SelectedSumNodesInLevel0=0 SelectedSumCoresInLevel0=0 SelectedSumSocketsInLevel0=0 AllocatedSumNodesInLevel0=0 AllocatedSumCoresInLevel0=0 AllocatedSumSocketsInLevel0=0 SelectedSumThreadsInLevel0=0 SwitchToProcessInLevel0=0 AllocatedSumThreadsInLevel0=0 SelectedSumThreadsInLevel0=0 NumSumThreadsInLevel0=0 Enclosed=virtual[10-19]\n");

	printf("Entity=switch5 Type=Switch NumSumNodesInLevel0=0 NumSumCoresInLevel0=0 NumSumSocketsInLevel0=0 SelectedSumNodesInLevel0=0 SelectedSumCoresInLevel0=0 SelectedSumSocketsInLevel0=0 AllocatedSumNodesInLevel0=0 AllocatedSumCoresInLevel0=0 AllocatedSumSocketsInLevel0=0 SelectedSumThreadsInLevel0=0 SwitchToProcessInLevel0=0 AllocatedSumThreadsInLevel0=0 SelectedSumThreadsInLevel0=0 NumSumThreadsInLevel0=0 Enclosed=virtual[20-29]\n");

	printf("Entity=switch6 Type=Switch NumSumNodesInLevel0=0 NumSumCoresInLevel0=0 NumSumSocketsInLevel0=0 SelectedSumNodesInLevel0=0 SelectedSumCoresInLevel0=0 SelectedSumSocketsInLevel0=0 AllocatedSumNodesInLevel0=0 AllocatedSumCoresInLevel0=0 AllocatedSumSocketsInLevel0=0 SelectedSumThreadsInLevel0=0 SwitchToProcessInLevel0=0 AllocatedSumThreadsInLevel0=0 SelectedSumThreadsInLevel0=0 NumSumThreadsInLevel0=0 Enclosed=virtual[0-9]\n");


printf("# Compute node layout configuration \n");
        for( i=0 ; i< 41  ; i++ )
        {
                j= 2*i;

                printf("Entity=virtual%d type=Node nodecount=1 SelectedNodeCount=0 AllocatedNodeCount=0 NumSumSocketsInNode=0 NumSumCoresInNode=0 SelectedSumSocketsInNode=0 SelectedSumCoresInNode=0 AllocatedSumSocketsInNode=0 AllocatedSumCoresInNode=0 BitmapPosition=0 SelectedNodeCount=0 SelectedSumThreadsInNode=0 AllocatedSumThreadsInNode=0 SelectedSumThreadsInNode=0 NumSumThreadsInNode=0 Enclosed=socket[%d-%d] \n",i,j,j+1);
        }
printf("#Socket Level layout configuration following\n");

	for( i=0 ; i< 82 ; i++ )
        {
                j= 2*i;

                printf("Entity=socket%d type=Socket socketcount=1 NumSumCoresInSocket=0 SelectedSumCoresInSocket=0 AllocatedSumCoresInSocket=0  BitmapPosition=0 SelectedSocketCount=0 AllocatedSocketCount=0 AllocatedSumThreadsInSocket=0 SelectedSumThreadsInSocket=0 NumSumThreadsInSocket=0 Enclosed=core[%d-%d] \n",i,j,j+1);
        }

printf("#Core level Layout configuration following\n");

	printf("Entity=core[0-163] type=Core threadcount=4 SelectedThreadCount=0 AllocatedThreadCount=0  BitmapPosition=0 SelectedCoreCount=0 AllocatedCoreCount=0 corecount=1");

	return 0;
}
