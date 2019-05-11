#include <mpi.h>
#include <stdio.h>

int main8(int argc,char *argv[]){
	int r,n;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&r);
	MPI_Comm_size(MPI_COMM_WORLD,&n);

	int a[3][3],cs=-1,fs,arr[3],arr2[3],cm=1000;
	if(r==0){
		for(int i=0;i<3;i++) for(int j=0;j<3;j++) scanf("%d",&a[i][j]);
	}

	MPI_Scatter(a,3,MPI_INT,arr,3,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scan(arr,arr2,3,MPI_INT,MPI_MIN,MPI_COMM_WORLD);

	for(int i=0;i<3;i++) if(arr[i]>cs) cs=arr[i];
	printf("Row %d - Max = %d\n",r,cs);

	if(r==2){
		for(int i=0;i<3;i++) {
			printf("Column %d - Min = %d\n",i,arr2[i]);
			if(arr2[i]<cm) cm = arr2[i];
		}
	}

	MPI_Bcast(&cm,1,MPI_INT,2,MPI_COMM_WORLD);
	MPI_Reduce(&cs,&fs,1,MPI_INT,MPI_MAX,0,MPI_COMM_WORLD);
	if(r==0) {
		printf("Overall Max = %d\n",fs);
		printf("Overall Min = %d\n",cm);
	}

	MPI_Finalize();
	return 0;
}
