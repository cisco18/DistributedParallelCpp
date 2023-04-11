#include <iostream>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    printf("Process %d started\n", rank);

    MPI_Barrier(MPI_COMM_WORLD);
    printf("Process %d passed the barrier\n", rank);
	
    MPI_Finalize();
    return 0;
}