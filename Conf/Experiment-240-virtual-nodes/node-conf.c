#include <stdio.h>

int main()
{
	int nb_nodes=240,port=17000,i=0;
	for(i=0 ; i < 80 ; i++ )
	{
		printf("NodeName=virtual%d NodeHostName=mo66 NodeAddr=mo66 Port=%d\n",i,(port+i));
	}
	for(i=80; i<160; i++ )
	{
		printf("NodeName=virtual%d NodeHostName=mo67 NodeAddr=mo67 Port=%d\n",i,(port+i));
	}
	for(i=160 ; i<240 ; i++ )
	{
		printf("NodeName=virtual%d NodeHostName=mo68 NodeAddr=mo68 Port=%d\n",i,(port+i));
	}
	return 0;
}
