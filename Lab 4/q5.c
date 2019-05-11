#include <mpi.h>
#include <stdio.h>

int main5(int argc,char *argv[]){
	int r,n;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&r);
	MPI_Comm_size(MPI_COMM_WORLD,&n);

	int a[4][4],arr[4],arr2[4];
	if(r==0){
		for(int i=0;i<4;i++) for(int j=0;j<4;j++) scanf("%d",&a[i][j]);
	}

	MPI_Scatter(a,4,MPI_INT,arr,4,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scan(arr,arr2,4,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
	MPI_Gather(arr2,4,MPI_INT,a,4,MPI_INT,0,MPI_COMM_WORLD);
	if(r==0){
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++) printf("%d  ",a[i][j]);
			printf("\n");
		}
	}

	MPI_Finalize();
	return 0;
}
