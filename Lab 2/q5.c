#include <mpi.h>
#include <stdio.h>

int main5(int argc,char *argv[]){
	int r,n;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&r);
	MPI_Comm_size(MPI_COMM_WORLD,&n);
	int ele=0;

	if(r==0){
		ele++;
		MPI_Send(&ele,1,MPI_INT,1,0,MPI_COMM_WORLD);
		printf("Process %d sent %d to 1\n",r,ele);
		MPI_Recv(&ele,1,MPI_INT,n-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("Process 0 recv %d from %d\n",ele,n-1);
	}else{
		MPI_Recv(&ele,1,MPI_INT,r-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("Process %d recv %d from %d\n",r,ele,r-1);
		ele++;
		MPI_Send(&ele,1,MPI_INT,(r+1)%n,0,MPI_COMM_WORLD);
		printf("Process %d sent %d to %d\n",r,ele,(r+1)%n);
	}

	MPI_Finalize();
	return 0;
}
