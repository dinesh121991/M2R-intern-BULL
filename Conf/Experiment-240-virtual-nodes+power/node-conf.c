#include <stdio.h>

int main()
{
	int nb_nodes=3000,port=17000,i=0,j=0;
	for(i=0,j=0 ; i < 1000 ; i++,j++ )
	{
		printf("NodeName=virtual%d NodeHostName=mo98 NodeAddr=mo98 Port=%d\n",i,(port+j));
	}
	for(i=1000,j=0 ; i<2000; i++,j++ )
	{
		printf("NodeName=virtual%d NodeHostName=mo67 NodeAddr=mo67 Port=%d\n",i,(port+j));
	}
	for(i=2000,j=0 ; i<3000 ; i++,j++ )
	{
		printf("NodeName=virtual%d NodeHostName=mo68 NodeAddr=mo68 Port=%d\n",i,(port+j));
	}
	for(i=3000,j=0 ; i< 4000 ; i++,j++)
        {
                printf("NodeName=virtual%d NodeHostName=mo99 NodeAddr=mo99 Port=%d\n",i,(port+j));
        }
	return 0;
}
