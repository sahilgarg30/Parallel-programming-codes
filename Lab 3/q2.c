#include <mpi.h>
#include <stdio.h>

int main2(int argc,char *argv[]){
	int r,n;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&r);
	MPI_Comm_size(MPI_COMM_WORLD,&n);
	int ele,arr[10];

	if(r==0)
	for(int i=0;i<n;i++) scanf("%d",&arr[i]);

	MPI_Scatter(arr,1,MPI_INT,&ele,1,MPI_INT,0,MPI_COMM_WORLD);

	int f=1;

	for(int i=2;i<=ele;i++) f*=i;

	MPI_Gather(&f,1,MPI_INT,arr,1,MPI_INT,0,MPI_COMM_WORLD);

	if(r==0){
		f=0;
		for(int i=0;i<n;i++) f+=arr[i];
		printf("%d",f);
	}
	MPI_Finalize();
	return 0;
}
