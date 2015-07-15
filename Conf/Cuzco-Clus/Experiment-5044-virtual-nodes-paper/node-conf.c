/*#include <stdio.h>

int main()
{
	int nb_nodes=3000,port=17000,i=0,j=0;
	for(i=0,j=0 ; i < 1000 ; i++,j++ )
	{
		printf("NodeName=virtual%d NodeHostName=mo66 NodeAddr=mo66 Port=%d\n",i,(port+j));
	}
	for(i=1000,j=0 ; i<2000; i++,j++ )
	{
		printf("NodeName=virtual%d NodeHostName=mo67 NodeAddr=mo67 Port=%d\n",i,(port+j));
	}
	for(i=2000,j=0 ; i<3000 ; i++,j++ )
	{
		printf("NodeName=virtual%d NodeHostName=mo68 NodeAddr=mo68 Port=%d\n",i,(port+j));
	}
	return 0;
}*/

#include <stdio.h>

int main()
{
        int nb_nodes=5040,port=17000,i=0,j=0,avail_nodes=16;
	int virtual_per_node = nb_nodes / avail_nodes ; 
	int k=1,start_virtual_per_node=0,upto_virtual_per_node = k* virtual_per_node;
        for(i=0,j=0 ; i < virtual_per_node ; i++,j++ )
        {
                printf("NodeName=virtual%d NodeHostName=cuzco5 NodeAddr=cuzco5 Port=%d\n",i,(port+j));
        }
k++;
start_virtual_per_node = upto_virtual_per_node;
upto_virtual_per_node = k* virtual_per_node;
        for(i=start_virtual_per_node,j=0 ; i< upto_virtual_per_node; i++,j++ )
        {
                printf("NodeName=virtual%d NodeHostName=cuzco7 NodeAddr=cuzco7 Port=%d\n",i,(port+j));
        }
k++;
start_virtual_per_node = upto_virtual_per_node;
upto_virtual_per_node = k* virtual_per_node;
        for(i= start_virtual_per_node ,j=0 ; i< upto_virtual_per_node ; i++,j++ )
        {
                printf("NodeName=virtual%d NodeHostName=cuzco8 NodeAddr=cuzco8 Port=%d\n",i,(port+j));
        }
k++;
start_virtual_per_node = upto_virtual_per_node;
upto_virtual_per_node = k* virtual_per_node;
        for(i= start_virtual_per_node ,j=0 ; i< upto_virtual_per_node ; i++,j++)
        {
                printf("NodeName=virtual%d NodeHostName=cuzco9 NodeAddr=cuzco9 Port=%d\n",i,(port+j));
        }
k++;
start_virtual_per_node = upto_virtual_per_node;
upto_virtual_per_node = k* virtual_per_node;
for(i= start_virtual_per_node ,j=0 ; i < upto_virtual_per_node  ; i++,j++ )
        {
                printf("NodeName=virtual%d NodeHostName=cuzco10 NodeAddr= cuzco10 Port=%d\n",i,(port+j));
        }
k++;
start_virtual_per_node = upto_virtual_per_node;
upto_virtual_per_node = k* virtual_per_node;
        for(i= start_virtual_per_node ,j=0 ; i< upto_virtual_per_node ; i++,j++ )
        {
                printf("NodeName=virtual%d NodeHostName=cuzco11 NodeAddr= cuzco11 Port=%d\n",i,(port+j));
        }
k++;
start_virtual_per_node = upto_virtual_per_node;
upto_virtual_per_node = k* virtual_per_node;
        for(i= start_virtual_per_node ,j=0 ; i< upto_virtual_per_node ; i++,j++ )
        {
                printf("NodeName=virtual%d NodeHostName=cuzco13 NodeAddr= cuzco13 Port=%d\n",i,(port+j));
        }
k++;
start_virtual_per_node = upto_virtual_per_node;
upto_virtual_per_node = k* virtual_per_node;
        for(i= start_virtual_per_node ,j=0 ; i< upto_virtual_per_node ; i++,j++)
        {
                printf("NodeName=virtual%d NodeHostName=cuzco14 NodeAddr= cuzco14 Port=%d\n",i,(port+j));
        }
k++;
start_virtual_per_node = upto_virtual_per_node;
upto_virtual_per_node = k* virtual_per_node;
for(i=start_virtual_per_node ,j=0 ; i < upto_virtual_per_node ; i++,j++ )
        {
                printf("NodeName=virtual%d NodeHostName=cuzco16 NodeAddr= cuzco16 Port=%d\n",i,(port+j));
        }
k++;
start_virtual_per_node = upto_virtual_per_node;
upto_virtual_per_node = k* virtual_per_node;
        for(i= start_virtual_per_node ,j=0 ; i< upto_virtual_per_node ; i++,j++ )
        {
                printf("NodeName=virtual%d NodeHostName=cuzco18 NodeAddr=cuzco18 Port=%d\n",i,(port+j));
        }
k++;
start_virtual_per_node = upto_virtual_per_node;
upto_virtual_per_node = k* virtual_per_node;
        for(i= start_virtual_per_node ,j=0 ; i< upto_virtual_per_node ; i++,j++ )
        {
                printf("NodeName=virtual%d NodeHostName=cuzco19 NodeAddr=cuzco19 Port=%d\n",i,(port+j));
        }
k++;
start_virtual_per_node = upto_virtual_per_node;
upto_virtual_per_node = k* virtual_per_node;
        for(i= start_virtual_per_node ,j=0 ; i< upto_virtual_per_node ; i++,j++)
        {
                printf("NodeName=virtual%d NodeHostName=cuzco20 NodeAddr=cuzco20 Port=%d\n",i,(port+j));
        }
k++;
start_virtual_per_node = upto_virtual_per_node;
upto_virtual_per_node = k* virtual_per_node;
for(i= start_virtual_per_node ,j=0 ; i < upto_virtual_per_node ; i++,j++ )
        {
                printf("NodeName=virtual%d NodeHostName=cuzco21 NodeAddr=cuzco21 Port=%d\n",i,(port+j));
        }
k++;
start_virtual_per_node = upto_virtual_per_node;
upto_virtual_per_node = k* virtual_per_node;
        for(i= start_virtual_per_node ,j=0 ; i< upto_virtual_per_node ; i++,j++ )
        {
                printf("NodeName=virtual%d NodeHostName=cuzco34 NodeAddr=cuzco34 Port=%d\n",i,(port+j));
        }
k++;
start_virtual_per_node = upto_virtual_per_node;
upto_virtual_per_node = k* virtual_per_node;
        for(i= start_virtual_per_node,j=0 ; i< upto_virtual_per_node ; i++,j++ )
        {
                printf("NodeName=virtual%d NodeHostName=cuzco35 NodeAddr=cuzco35 Port=%d\n",i,(port+j));
        }
k++;
start_virtual_per_node = upto_virtual_per_node;
upto_virtual_per_node = k* virtual_per_node;
        for(i= start_virtual_per_node ,j=0 ; i< upto_virtual_per_node  ; i++,j++)
        {
                printf("NodeName=virtual%d NodeHostName=cuzco26 NodeAddr=cuzco26 Port=%d\n",i,(port+j));
        }
        return 0;
}

