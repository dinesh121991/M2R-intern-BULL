#include<stdio.h>

int main( int argc, char*argv[] )
{
        int i=0,j=0;
	printf("Priority=10\nRoot=switch0\n\n");
printf("#Root or Cluster level Layout configuration\n");


printf("#switch or tree topolgy configuration\n");
	printf("Entity=switch0 Type=Switch AvailableSumNodesInLevel3=0 SwitchToProcessInLevel3=0 AvailableSumCpusInLevel3=0 Enclosed=switch[1-2]\n\n");

//	for( i=1 ; i<4 ; i++ )
	printf("Entity=switch1 Type=Switch AvailableSumNodesInLevel2=0 AvailableSumCpusInLevel2=0 SwitchToProcessInLevel2=0 Enclosed=switch[4-5]\n");

	printf("Entity=switch2 Type=Switch AvailableSumNodesInLevel0=0 AvailableSumCpusInLevel0=0 SwitchToProcessInLevel0=0 Enclosed=virtual[30-40]\n");

	printf("Entity=switch3 Type=Switch AvailableSumNodesInLevel1=0 SwitchToProcessInLevel1=0 AvailableSumCpusInLevel1=0  Enclosed=switch[6]\n");

	printf("Entity=switch4 Type=Switch AvailableSumNodesInLevel0=0 AvailableSumCpusInLevel0=0 SwitchToProcessInLevel0=0 Enclosed=virtual[10-19]\n");

	printf("Entity=switch5 Type=Switch AvailableSumNodesInLevel0=0 AvailableSumCpusInLevel0=0 SwitchToProcessInLevel0=0 Enclosed=virtual[20-29]\n");

	printf("Entity=switch6 Type=Switch AvailableSumNodesInLevel0=0 AvailableSumCpusInLevel0=0 SwitchToProcessInLevel0=0 Enclosed=virtual[0-9]\n");


printf("# Compute node layout configuration \n");

        for( i=0 ; i< 41  ; i++ )
        {
//                j= 2*i;
                printf("Entity=virtual%d type=Node AvailableNodeCount=0 AvailableCpusCount=0\n",i);
        }

	return 0;
}
