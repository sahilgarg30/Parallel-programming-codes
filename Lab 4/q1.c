#include <mpi.h>
#include <stdio.h>

int main1(int argc,char *argv[]){
	int r,n,fact = 1,factsum=0;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&r);
	MPI_Comm_size(MPI_COMM_WORLD,&n);

	for(int i=1;i<=r+1;i++)
		fact *= i;

	MPI_Scan(&fact,&factsum,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
	printf("%d\t",factsum);
	MPI_Finalize();
	return 0;
}
