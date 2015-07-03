#include <stdio.h>

int main( int argc, char *argv[] )
{
	int i,j,switch_level_1=10,switch_level_2=20,num_nodes=40;
	int k;

//Root switch( switch level -0 ) config
	printf("SwitchName=switch0 Switches=switch[1-10]\n");

//Switch level 1 config
	for( i=1,j=switch_level_1+1 ; i <= switch_level_1 && j<=switch_level_2 ; i++ )
		printf("SwitchName=switch%d Switches=switch[%d-%d]\n",i,j++,j);

// Switch level-2 config
	for( i=switch_level_1+1,j=0; i<=switch_level_2 && j<= num_nodes; i++ )
	{
		k= j+3;
		printf("SwitchName=switch%d Nodes=virtual[%d-%d]\n",i,j,k);
		j += 4;
	}

	return 0;
}
