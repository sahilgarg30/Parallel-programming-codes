#include <mpi.h>
#include <stdio.h>

int main3(int argc,char *argv[]){
	int r,n;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&r);
	MPI_Comm_size(MPI_COMM_WORLD,&n);

	int a[3][3],ele,cs=0,fs,arr[3];
	if(r==0){
		for(int i=0;i<3;i++) for(int j=0;j<3;j++) scanf("%d",&a[i][j]);
		scanf("%d",&ele);
	}

	MPI_Scatter(a,3,MPI_INT,arr,3,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(&ele,1,MPI_INT,0,MPI_COMM_WORLD);

	for(int i=0;i<3;i++) if(ele==arr[i]) cs++;

	MPI_Reduce(&cs,&fs,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	if(r==0) printf("%d\n",fs);

	MPI_Finalize();
	return 0;
}
