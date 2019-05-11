#include <stdio.h>
#include <mpi.h>
#include <math.h>

double func(double x)
{
    return (1.0 / (1.0 + x*x));
}


int main2(int argc, char *argv[])
{
    int n;
    double PI25DT = 3.141592653589793238462643;
    double mypi, h, pi, i, sum;
    int myid, numprocs;

    MPI_Init(&argc,&argv);

    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);

    if(myid == 0)
    {
       	n = 100000;
        printf("The number of intervals = %d \n", n);
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    sum = 0.0;
    h   = 1.0/n;
    for (i=myid+0.5; i<n; i+=numprocs)
    {
        sum += func(i*h);
    }

    mypi = 4.0*h*sum;
    MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (myid == 0)
    {
        printf("pi is approximately %.16f, Error is %.16f\n",
                pi, fabs(pi - PI25DT));
    }
    MPI_Finalize();
    return 0;
}


