#include<stdio.h>

int main( int argc, char*argv[] )
{
	int i=0,j=0;
	for( i=0 ; i< 80 ; i++ ) 
	{
		j= 2*i;
		printf("Entity=socket%d type=socket JobId=0 NumSumCores=0 FreeSumCores=0 AllocatedSumCores=0  ForWhatPurposePriority=0 BitmapPosition=0 Selected=0 AllocatedSocketCount=0 socketcount=1 Enclosed=core[%d-%d] \n",i,j,j+1);
	}
	return 0;
}
