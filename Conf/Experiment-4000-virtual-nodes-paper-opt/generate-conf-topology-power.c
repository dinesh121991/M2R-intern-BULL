#include<stdio.h>

int main( int argc, char*argv[] )
{
        int i=0,j=0;
	printf("Priority=10\nRoot=switch0\n\n");
printf("#Root or Cluster level Layout configuration\n");


printf("#switch or tree topolgy configuration\n");
	printf("Entity=switch0 Type=Switch IdleSumWattsInLevel2=0 MaxSumWattsInLevel2=0 Enclosed=switch[1-2]\n\n");

//	for( i=1 ; i<4 ; i++ )
	printf("Entity=switch1 Type=Switch IdleSumWattsInLevel1=0 MaxSumWattsInLevel1=0 Enclosed=switch[3-4]\n");
	printf("Entity=switch2 Type=Switch IdleSumWattsInLevel1=0 MaxSumWattsInLevel1=0 Enclosed=switch[5-6]\n");

	printf("Entity=switch3 Type=Switch IdleSumWattsInLevel0=0 MaxSumWattsInLevel0=0  Enclosed=virtual[0-999]\n");

	printf("Entity=switch4 Type=Switch IdleSumWattsInLevel0=0 MaxSumWattsInLevel0=0 Enclosed=virtual[1000-1999]\n");

	printf("Entity=switch5 Type=Switch IdleSumWattsInLevel0=0 MaxSumWattsInLevel0=0 Enclosed=virtual[2000-2999]\n");

	printf("Entity=switch6 Type=Switch IdleSumWattsInLevel0=0 MaxSumWattsInLevel0=0 Enclosed=virtual[3000-3999]\n");


printf("# Compute node layout configuration \n");

                printf("Entity=virtual[0-3999] type=Node IdleWatts=0 MaxWatts=0\n");

	return 0;
}
