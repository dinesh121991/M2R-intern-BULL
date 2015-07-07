
#include <stdio.h>

int main()
{
        int nb_nodes=5040,port=17000,i=0,j=0,avail_nodes=16;
	int virtual_per_node = nb_nodes / avail_nodes ; 
	int k=1,start_virtual_per_node=0,upto_virtual_per_node = k* virtual_per_node;
                printf("for i in {0..%d}; do /usr/local/15-08-crl/sbin/slurmd -N virtual$i; done \n",virtual_per_node -1);

k++;
start_virtual_per_node = upto_virtual_per_node;
upto_virtual_per_node = k* virtual_per_node;
  printf("for i in {%d..%d}; do /usr/local/15-08-crl/sbin/slurmd -N virtual$i; done \n",start_virtual_per_node,upto_virtual_per_node -1 );

k++;
start_virtual_per_node = upto_virtual_per_node;
upto_virtual_per_node = k* virtual_per_node;

printf("for i in {%d..%d}; do /usr/local/15-08-crl/sbin/slurmd -N virtual$i; done \n",start_virtual_per_node,upto_virtual_per_node -1 );

k++;
start_virtual_per_node = upto_virtual_per_node;
upto_virtual_per_node = k* virtual_per_node;

printf("for i in {%d..%d}; do /usr/local/15-08-crl/sbin/slurmd -N virtual$i; done \n",start_virtual_per_node,upto_virtual_per_node -1 );

k++;
start_virtual_per_node = upto_virtual_per_node;
upto_virtual_per_node = k* virtual_per_node;


printf("for i in {%d..%d}; do /usr/local/15-08-crl/sbin/slurmd -N virtual$i; done \n",start_virtual_per_node,upto_virtual_per_node -1);

k++;
start_virtual_per_node = upto_virtual_per_node;
upto_virtual_per_node = k* virtual_per_node;


printf("for i in {%d..%d}; do /usr/local/15-08-crl/sbin/slurmd -N virtual$i; done \n",start_virtual_per_node,upto_virtual_per_node -1 );

k++;
start_virtual_per_node = upto_virtual_per_node;
upto_virtual_per_node = k* virtual_per_node;

printf("for i in {%d..%d}; do /usr/local/15-08-crl/sbin/slurmd -N virtual$i; done \n",start_virtual_per_node,upto_virtual_per_node -1);


k++;
start_virtual_per_node = upto_virtual_per_node;
upto_virtual_per_node = k* virtual_per_node;

printf("for i in {%d..%d}; do /usr/local/15-08-crl/sbin/slurmd -N virtual$i; done \n",start_virtual_per_node,upto_virtual_per_node -1);

k++;
start_virtual_per_node = upto_virtual_per_node;
upto_virtual_per_node = k* virtual_per_node;

printf("for i in {%d..%d}; do /usr/local/15-08-crl/sbin/slurmd -N virtual$i; done \n",start_virtual_per_node,upto_virtual_per_node -1);



k++;
start_virtual_per_node = upto_virtual_per_node;
upto_virtual_per_node = k* virtual_per_node;

printf("for i in {%d..%d}; do /usr/local/15-08-crl/sbin/slurmd -N virtual$i; done \n",start_virtual_per_node,upto_virtual_per_node -1 );


k++;
start_virtual_per_node = upto_virtual_per_node;
upto_virtual_per_node = k* virtual_per_node;

printf("for i in {%d..%d}; do /usr/local/15-08-crl/sbin/slurmd -N virtual$i; done \n",start_virtual_per_node,upto_virtual_per_node -1);

k++;
start_virtual_per_node = upto_virtual_per_node;
upto_virtual_per_node = k* virtual_per_node;

printf("for i in {%d..%d}; do /usr/local/15-08-crl/sbin/slurmd -N virtual$i; done \n",start_virtual_per_node,upto_virtual_per_node -1 );


k++;
start_virtual_per_node = upto_virtual_per_node;
upto_virtual_per_node = k* virtual_per_node;


printf("for i in {%d..%d}; do /usr/local/15-08-crl/sbin/slurmd -N virtual$i; done \n",start_virtual_per_node,upto_virtual_per_node -1 );

k++;
start_virtual_per_node = upto_virtual_per_node;
upto_virtual_per_node = k* virtual_per_node;


printf("for i in {%d..%d}; do /usr/local/15-08-crl/sbin/slurmd -N virtual$i; done \n",start_virtual_per_node,upto_virtual_per_node -1 );

k++;
start_virtual_per_node = upto_virtual_per_node;
upto_virtual_per_node = k* virtual_per_node;


printf("for i in {%d..%d}; do /usr/local/15-08-crl/sbin/slurmd -N virtual$i; done \n",start_virtual_per_node,upto_virtual_per_node -1 );

k++;
start_virtual_per_node = upto_virtual_per_node;
upto_virtual_per_node = k* virtual_per_node;

printf("for i in {%d..%d}; do /usr/local/15-08-crl/sbin/slurmd -N virtual$i; done \n",start_virtual_per_node,upto_virtual_per_node -1 );

        return 0;
}

