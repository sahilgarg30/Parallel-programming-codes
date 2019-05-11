#include <mpi.h>
#include <stdio.h>

int main(int argc,char *argv[]){
	int r;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&r);
	if(r%2==0) printf("Hello\n");
	else printf("World\n");
	MPI_Finalize();
	return 0;
}