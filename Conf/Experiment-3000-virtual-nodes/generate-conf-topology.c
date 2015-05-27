#include<stdio.h>

int main( int argc, char*argv[] )
{
        int i=0,j=0;
	printf("Priority=10\nRoot=switch0\n\n");
printf("#Root or Cluster level Layout configuration\n");


printf("#switch or tree topolgy configuration\n");
	printf("Entity=switch0 Type=Switch AvailableSumNodesInLevel2=0 SwitchToProcessInLevel2=0 AvailableSumCpusInLevel2=0 Enclosed=switch[1-2]\n\n");

//	for( i=1 ; i<4 ; i++ )
	printf("Entity=switch1 Type=Switch AvailableSumNodesInLevel1=0 AvailableSumCpusInLevel1=0 SwitchToProcessInLevel1=0 Enclosed=switch[3-4]\n");
	printf("Entity=switch2 Type=Switch AvailableSumNodesInLevel1=0 AvailableSumCpusInLevel1=0 SwitchToProcessInLevel1=0 Enclosed=switch[5-6]\n");

	printf("Entity=switch3 Type=Switch AvailableSumNodesInLevel0=0 SwitchToProcessInLevel0=0 AvailableSumCpusInLevel0=0  Enclosed=virtual[0-499]\n");

	printf("Entity=switch4 Type=Switch AvailableSumNodesInLevel0=0 AvailableSumCpusInLevel0=0 SwitchToProcessInLevel0=0 Enclosed=virtual[500-999]\n");

	printf("Entity=switch5 Type=Switch AvailableSumNodesInLevel0=0 AvailableSumCpusInLevel0=0 SwitchToProcessInLevel0=0 Enclosed=virtual[1000-1499]\n");

	printf("Entity=switch6 Type=Switch AvailableSumNodesInLevel0=0 AvailableSumCpusInLevel0=0 SwitchToProcessInLevel0=0 Enclosed=virtual[1500-2999]\n");


printf("# Compute node layout configuration \n");

        for( i=0 ; i< 3000  ; i++ )
        {
//                j= 2*i;
                printf("Entity=virtual%d type=Node AvailableNodeCount=0 AvailableCpusCount=0\n",i);
        }

	return 0;
}
