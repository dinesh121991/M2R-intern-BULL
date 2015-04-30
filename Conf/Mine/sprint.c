#include<stdio.h>

int main()
{
	char a[][30]= {"-switch-0-1-","-switch-0-1-","-switch-00-01-",
			"-switch-000-001-" } ;
	char s[30],c1,c2,c3,c4;
	int i1,i2;
	int i;
	for (i=0;i<4;i++)
	{
		sscanf(a[i],"%c%s%c%d%c%d%c",&c1,s,&c2,&i1,&c3,&i2,&c4);
		printf("%c%s%c%d%c%d%c \n",c1,s,c2,i1,c3,i2,c4);
	}
	return 0;
}
