#include <mpi.h>
#include <stdio.h>

int main6(int argc,char *argv[]){
	int r,n;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&r);
	MPI_Comm_size(MPI_COMM_WORLD,&n);

	int a[3][3],a1[3],b[3][3],a2[3];
	if(r==0){
		for(int i=0;i<3;i++) for(int j=0;j<3;j++) scanf("%d",&a[i][j]);
		for(int i=0;i<3;i++) for(int j=0;j<3;j++) scanf("%d",&b[i][j]);
	}

	MPI_Scatter(a,3,MPI_INT,a1,3,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(b,3,MPI_INT,a2,3,MPI_INT,0,MPI_COMM_WORLD);

	for(int i=0;i<3;i++) a1[i]+=a2[i];

	MPI_Gather(a1,3,MPI_INT,a,3,MPI_INT,0,MPI_COMM_WORLD);
	if(r==0){
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++) printf("%d  ",a[i][j]);
			printf("\n");
		}
	}

	MPI_Finalize();
	return 0;
}
