#include <mpi.h>
#include <stdio.h>

int main2(int argc,char *argv[]){
	int r,size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&r);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	if(r==0){
		for(int i=1;i<size;i++)
			MPI_Send(&i,1,MPI_INT,i,0,MPI_COMM_WORLD);
	}else{
		int x=0;
		MPI_Recv(&x,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("%d - %d\n",r,x);
	}
	MPI_Finalize();
	return 0;
}
