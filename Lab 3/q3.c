#include <mpi.h>
#include <stdio.h>

int main3(int argc,char *argv[]){
	int r,n,m;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&r);
	MPI_Comm_size(MPI_COMM_WORLD,&n);
	int arr[100],larr[10];
	float a[10];

	if(r==0){
		scanf("%d",&m);
		for(int i=0;i<n*m;i++) scanf("%d",&arr[i]);
	}
	MPI_Bcast(&m,1,MPI_INT,0,MPI_COMM_WORLD);

	MPI_Scatter(arr,m,MPI_INT,larr,m,MPI_INT,0,MPI_COMM_WORLD);

	float avg=0.0;

	for(int i=0;i<m;i++) {avg+=larr[i];}
	avg = (float)avg/m;

	MPI_Gather(&avg,1,MPI_FLOAT,a,1,MPI_FLOAT,0,MPI_COMM_WORLD);

	if(r==0){
		avg=0.0;
		for(int i=0;i<n;i++) avg += a[i];
		avg = (float)avg/n;
		printf("%f",avg);
	}
	MPI_Finalize();
	return 0;
}
