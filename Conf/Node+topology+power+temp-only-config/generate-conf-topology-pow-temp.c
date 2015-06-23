#include<stdio.h>

int main( int argc, char*argv[] )
{
        int i=0,j=0;
	printf("Priority=10\nRoot=switch0\n\n");
printf("#Root or Cluster level Layout configuration\n");


printf("#switch or tree topolgy configuration\n");
printf("Entity=switch0 Type=Switch AvailableAvgPowerInLevel2=0 AvailableAvgTemperatureInLevel2=0 Enclosed=switch[1-2]\n\n");

//	for( i=1 ; i<4 ; i++ )
	printf("Entity=switch1 Type=Switch AvailableAvgPowerInLevel1=0 AvailableAvgTemperatureInLevel1=0 Enclosed=switch[3-4]\n");
	printf("Entity=switch2 Type=Switch AvailableAvgPowerInLevel1=0 AvailableAvgTemperatureInLevel1=0 Enclosed=switch[5-6]\n");

	printf("Entity=switch3 Type=Switch AvailableAvgPowerInLevel0=0  AvailableAvgTemperatureInLevel0=0 Enclosed=virtual[0-59]\n");

	printf("Entity=switch4 Type=Switch AvailableAvgPowerInLevel0=0  AvailableAvgTemperatureInLevel0=0 Enclosed=virtual[60-119]\n");

	printf("Entity=switch5 Type=Switch AvailableAvgPowerInLevel0=0  AvailableAvgTemperatureInLevel0=0 Enclosed=virtual[120-179]\n");

	printf("Entity=switch6 Type=Switch AvailableAvgPowerInLevel0=0  AvailableAvgTemperatureInLevel0=0 Enclosed=virtual[180-239]\n");

printf("# Compute node layout configuration \n");

        for( i=0 ; i< 60  ; i++ )
        {
                printf("Entity=virtual%d type=Node AvailablePower=100 AvailableTemperature=30\n",i);
        }
/*        for( i=40 ; i< 80  ; i++ )
        {
                printf("Entity=virtual%d type=Node AvailablePower=80 AvailableTemperature=25\n",i);
        }
*/
        for( i=60 ; i< 120  ; i++ )
        {
                printf("Entity=virtual%d type=Node AvailablePower=120 AvailableTemperature=35\n",i);
        }
        for( i=120 ; i< 180  ; i++ )
        {
                printf("Entity=virtual%d type=Node AvailablePower=110 AvailableTemperature=34\n",i);
        }
  
/*      for( i=160 ; i< 200  ; i++ )
        {
                printf("Entity=virtual%d type=Node AvailablePower=110 AvailableTemperature=34\n",i);
        }
*/
        for( i=180 ; i< 240  ; i++ )
        {
                printf("Entity=virtual%d type=Node AvailablePower=120 AvailableTemperature=35\n",i);
        }
	return 0;
}
