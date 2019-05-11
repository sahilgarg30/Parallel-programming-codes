#include <mpi.h>
#include <stdio.h>
#include <math.h>
int main(int argc,char *argv[]){
	int r,n,m;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&r);
	MPI_Comm_size(MPI_COMM_WORLD,&n);
	int arr[100],larr[10];

	if(r==0){
		scanf("%d",&m);
		for(int i=0;i<n*m;i++) scanf("%d",&arr[i]);
	}
	MPI_Bcast(&m,1,MPI_INT,0,MPI_COMM_WORLD);

	MPI_Scatter(arr,m,MPI_INT,larr,m,MPI_INT,0,MPI_COMM_WORLD);

	for(int i=0;i<m;i++){
		int ele = 1;
		for(int j=2;j<=larr[i];j++) ele+=j;
		larr[i]=ele;
	}


	MPI_Gather(larr,m,MPI_INT,arr,m,MPI_INT,0,MPI_COMM_WORLD);

	if(r==0){
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++) printf("%d ",arr[(i*m)+j]);
			printf("\n");
		}
	}
	MPI_Finalize();
	return 0;
}
