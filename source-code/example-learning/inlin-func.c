#include<stdio.h>
#include<stdbool.h>

extern inline int sum(int x, int y );
int main(int argc,char* argv[] ) 
{
	bool a=true;
	register int x=10,y=20,result;
	result = sum(x,y);
	printf("Sum: %d, Bool: %B \n",result, a );

}

inline int sum( int x , int y )
{

	return x+y;
}
