#include<stdio.h>

int main( int argc, char*argv[] )
{
	int i=0,j=0;
	int start_port=17000;
/*	int number_of_nodes,number_of_sockets;
	char str[15];
	printf("Enter the name_of_node[upto 15 characters long]: number_of_nodes: number_of_sockets_per_node: ");
	scanf("%s,%d,%d",str,&number_of_nodes,&number_of_sockets); */
	for( i=0 ; i< 1000 ; i++ ) 
	{
		printf("NodeName=virtual%d NodeHostName=mo66 NodeAddr=mo66 Port=%d \n",i,(start_port+i));
	}
	start_port=16000;
        for( i=1000 ; i< 2000 ; i++ ) 
        {
                printf("NodeName=virtual%d NodeHostName=mo67 NodeAddr=mo67 Port=%d \n",i,(start_port+i));
        }
	start_port=15000;
        for( i=2000 ; i< 3000 ; i++ ) 
        {
                printf("NodeName=virtual%d NodeHostName=mo68 NodeAddr=mo68 Port=%d \n",i,(start_port+i));
        }
	return 0;
}
