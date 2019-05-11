#include <mpi.h>
#include <stdio.h>

int main3(int argc,char *argv[]){
	int r,size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&r);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int n=0,arr[10];
	int sum = 0;

	if(r==0){
			scanf("%d",&n);
			MPI_Send(&n,1,MPI_INT,1,0,MPI_COMM_WORLD);
			for(int i=0;i<n;i++){
				scanf("%d",&arr[i]);
				MPI_Send(&arr[i],1,MPI_INT,1,i+1,MPI_COMM_WORLD);
			}
			for(int i=0;i<n/2;i++){
				sum += arr[i];
			}

			int add;
			MPI_Recv(&add,1,MPI_INT,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			sum += add;
			printf("Sum - %d\n",sum);
	}else{
		MPI_Recv(&n,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		for(int i=0;i<n;i++){
			MPI_Recv(&arr[i],1,MPI_INT,0,i+1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		}
		for(int i=n/2;i<n;i++) sum += arr[i];
		MPI_Send(&sum,1,MPI_INT,0,0,MPI_COMM_WORLD);
	}

	printf("Time %d - %f\n",r,MPI_Wtime());
	MPI_Finalize();
	return 0;
}
