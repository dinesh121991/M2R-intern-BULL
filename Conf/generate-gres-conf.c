#include<stdio.h>

int main( int argc ,  char *argv[] )
{
/*	char *node_name="virtual";
	char *node_host_name= "dinesh-HP-ProDesk-600-G1-TWR";
	char *node_addr = "127.0.0.1"; */
	int port=17000;
	int i;
	for( i=0; i < 20 ;i++ )
	{
		printf("NodeName=virtual%d NodeHostName=dinesh-HP-ProDesk-600-G1-TWR NodeAddr=127.0.0.1 Port=%d Sockets=2 CoresPerSocket=12 ThreadsPerCore=3 RealMemory=12054 State=IDLE\n",i,port+i);
	}

	for( i=20; i<40 ; i++ )
	{
		printf("NodeName=virtual%d NodeHostName=dinesh-HP-ProDesk-600-G1-TWR NodeAddr=127.0.0.1 Port=%d Sockets=3 CoresPerSocket=3 ThreadsPerCore=4 RealMemory=7000 State=IDLE\n",i,(port+i));
	}

	for( i=40; i<60 ; i++ )
	{
		 printf("NodeName=virtual%d NodeHostName=dinesh-HP-ProDesk-600-G1-TWR NodeAddr=127.0.0.1 Port=%d Sockets=4 CoresPerSocket=2 ThreadsPerCore=2 RealMemory=6000 State=IDLE \n",i,(port+i));
	}

	for( i=60 ; i<80 ; i++ )
	{
		 printf("NodeName=virtual%d NodeHostName=dinesh-HP-ProDesk-600-G1-TWR NodeAddr=127.0.0.1 Port=%d Sockets=1 CoresPerSocket=1 ThreadsPerCore=1 RealMemory=3000 State=IDLE\n",i,(port+i));
	}
	return 0;
}
