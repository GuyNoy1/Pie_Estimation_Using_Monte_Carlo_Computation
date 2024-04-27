#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mpi.h"

#define darts 200000000

double distance(double, double);
double ranged_random();

int main(argc, argv)
    int argc;
    char **argv;
{
    int i ,rank, size, shots_hit_per_unit = 0, total_hits = 0;
    double darts_per_unit = 0.0, real_pie = 3.141592653589793, approx_pie = 0;
    double x, y, t_initial = 0.0, t_final = 0.0;

    MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size); //gets the total number of processes in the communicator and puts them into size param
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); //retrieves the rank of the current MPI process in the communicator
    darts_per_unit = darts/size;
    MPI_Bcast(&darts_per_unit, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD); //broadcasts a message from the process with rank 0 to all other processes.

    srand(rank);
    if(rank == 0)
     {
        t_initial = MPI_Wtime(); //start timer
     }
    for(i = 0; i < darts_per_unit; i++)
    {
        x = ranged_random();
        y = ranged_random();
        if(distance(x, y) <= 1)
        {
            shots_hit_per_unit++;
        }

    }
    MPI_Reduce(&shots_hit_per_unit, &total_hits, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD); //sum the values of all proccesess
    if(rank == 0)
    {
        approx_pie = 4 * (double) total_hits / darts;
        printf("pie By Monte Carlo Approx is:%.16f\nThe ERROR is:%.16f\n", approx_pie, fabs(real_pie - approx_pie));
        t_final = MPI_Wtime(); //stop timer
        printf("time=%f\n", t_final - t_initial);
        fflush(stdout);
    }
	 MPI_Finalize(); 
    return 0;
}

double distance(double x, double y)
{
    return (x*x + y*y);
}
double ranged_random()
{
    double x;
    x = (double) rand()/RAND_MAX; // result -->  0 < x < 1
    x = x*2 - 1; // shift x values to -1 < x < 1
    return x;
}
