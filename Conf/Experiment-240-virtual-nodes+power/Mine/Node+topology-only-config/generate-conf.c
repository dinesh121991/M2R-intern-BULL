#include<stdio.h>

int main( int argc, char*argv[] )
{
        int i=0,j=0;
	printf("Priority=10\nRoot=Cluster,switch0\n\n");
printf("#Root or Cluster level Layout configuration\n");

	printf("Entity=Cluster Type=Center NumSumNodes=0 NumSumCoresInCluster=0 NumSumSocketsInCluster=0 SelectedSumNodes=0 SelectedSumCoresInCluster=0 SelectedSumSocketsInCluster=0 AllocatedSumNodes=0 AllocatedSumCoresInCluster=0 AllocatedSumSocketsInCluster=0 Enclosed=virtual[0-40]\n\n");

printf("#switch or tree topolgy configuration\n");
	printf("Entity=switch0 Type=Switch SelectedSumNodesInLevel3=0 SelectedSumCpusInLevel3=0 SwitchToProcessInLevel3=0 Enclosed=switch[1-3]\n\n");

//	for( i=1 ; i<4 ; i++ )
	printf("Entity=switch1 Type=Switch SelectedSumNodesInLevel2=0 SelectedSumCpusInLevel2=0 SwitchToProcessInLevel2=0 Enclosed=switch[4-5]\n");
	printf("Entity=switch2 Type=Switch SelectedSumNodesInLevel1=0 SelectedSumCpusInLevel1=0 SwitchToProcessInLevel1=0 Enclosed=switch[6-7]\n");
	printf("Entity=switch3 Type=Switch SelectedSumNodesInLevel1=0 SelectedSumCpusInLevel1=0 SwitchToProcessInLevel1=0 Enclosed=switch[8-9]\n");
	printf("Entity=switch4 Type=Switch SelectedSumNodesInLevel1=0 SelectedSumCpusInLevel1=0 SwitchToProcessInLevel1=0 Enclosed=switch[10-11]\n");

	printf("Entity=switch5 Type=Switch SelectedSumNodesInLevel0=0 SelectedSumCpusInLevel0=0 SwitchToProcessInLevel0=0 Enclosed=virtual[40-79]\n");
	printf("Entity=switch6 Type=Switch SelectedSumNodesInLevel0=0 SelectedSumCpusInLevel0=0 SwitchToProcessInLevel0=0 Enclosed=virtual[80-119]\n");
	printf("Entity=switch7 Type=Switch SelectedSumNodesInLevel0=0 SelectedSumCpusInLevel0=0 SwitchToProcessInLevel0=0 Enclosed=virtual[120-159]\n");
	printf("Entity=switch8 Type=Switch SelectedSumNodesInLevel0=0 SelectedSumCpusInLevel0=0 SwitchToProcessInLevel0=0 Enclosed=virtual[160-199]\n");
	printf("Entity=switch9 Type=Switch SelectedSumNodesInLevel0=0 SelectedSumCpusInLevel0=0 SwitchToProcessInLevel0=0 Enclosed=virtual[200-229]\n");
	printf("Entity=switch10 Type=Switch SelectedSumNodesInLevel0=0 SelectedSumCpusInLevel0=0 SwitchToProcessInLevel0=0 Enclosed=virtual[0-19]\n");
	printf("Entity=switch11 Type=Switch SelectedSumNodesInLevel0=0 SelectedSumCpusInLevel0=0 SwitchToProcessInLevel0=0 Enclosed=virtual[20-39]\n");


printf("# Compute node layout configuration \n");
        for( i=0 ; i< 229  ; i++ )
        {
                j= 2*i;

                printf("Entity=virtual%d type=Node nodecount=1 SelectedNodeCount=0 AllocatedNodeCount=0 NumSumSockets=0 NumSumCoresInNode=0 SelectedSumSockets=0 SelectedSumCoresInNode=0 AllocatedSumSockets=0 AllocatedSumCoresInNode=0 BitmapPosition=0 SelectedNodeCount=0 SelectedCpuCountInNode=0 Enclosed=socket[%d-%d] \n",i,j,j+1);
        }
printf("#Socket Level layout configuration following\n");

	for( i=0 ; i< 460 ; i++ )
        {
                j= 2*i;

                printf("Entity=socket%d type=Socket NumSumCores=0 SelectedSumCores=0 AllocatedSumCores=0  BitmapPosition=0 SelectedSocketCount=0 AllocatedSocketCount=0 socketcount=1 Enclosed=core[%d-%d] \n",i,j,j+1);
        }

printf("#Core level Layout configuration following\n");

	printf("Entity=core[0-919] type=Core ThreadsPerCore=4   BitmapPosition=0 SelectedCoreCount=0 AllocatedCoreCount=0 corecount=1");
	return 0;
}
