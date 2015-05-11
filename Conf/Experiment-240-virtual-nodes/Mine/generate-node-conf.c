#include<stdio.h>

int main( int argc, char*argv[] )
{
	int i=0,j=0;
/*	int number_of_nodes,number_of_sockets;
	char str[15];
	printf("Enter the name_of_node[upto 15 characters long]: number_of_nodes: number_of_sockets_per_node: ");
	scanf("%s,%d,%d",str,&number_of_nodes,&number_of_sockets); */
	for( i=0 ; i<= 40 ; i++ ) 
	{
		j= 2*i;
		printf("Entity=virtual%d type=Node nodecount=1 SelectedNodeCount=0 AllocatedNodeCount=0 NumSumSockets=0 NumSumCoresInNode=0 SelectedSumSockets=0 SelectedSumCoresInNode=0 AllocatedSumSockets=0 AllocatedSumCoresInNode=0 BitmapPosition=0 Enclosed=socket[%d-%d] \n",i,j,j+1);
	}
	return 0;
}
