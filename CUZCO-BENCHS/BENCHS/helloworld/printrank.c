/*
 * Copyright (c) 2004-2006 The Trustees of Indiana University and Indiana
 *                         University Research and Technology
 *                         Corporation.  All rights reserved.
 * Copyright (c) 2006      Cisco Systems, Inc.  All rights reserved.
 *
 * Sample MPI "hello world" application in C
 */

#include <stdio.h>
#include "mpi.h"

int main(int argc, char* argv[])
{
    int rank, size , sleep_time;

    if (argc != 2){
            printf("*** ERROR - incorrect number of command line arguments \n");
            printf("            usage is 'sleep number_of_seconds'         \n");
            return 1;
    }

    sleep_time = atoi(argv[1]);


    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    printf("Hello, world, I am %d of %d\n", rank, size);
    sleep(sleep_time);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();

    return 0;
}

