#include <mpi.h>
#include <stdio.h>

int isPrime(int x){
	if(x==2) return 1;
	if(x<2) return 0;
	for(int i=2;i<=x/2;i++) if(x%i==0) return 0;
	return 1;
}
int main7(int argc,char *argv[]){
	int r,n;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&r);
	MPI_Comm_size(MPI_COMM_WORLD,&n);

	int a[3][3],cs=0,fs,arr[3];
	if(r==0){
		for(int i=0;i<3;i++) for(int j=0;j<3;j++) scanf("%d",&a[i][j]);
	}

	MPI_Scatter(a,3,MPI_INT,arr,3,MPI_INT,0,MPI_COMM_WORLD);

	for(int i=0;i<3;i++) if(isPrime(arr[i])) cs+=arr[i];

	MPI_Reduce(&cs,&fs,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	if(r==0) printf("%d\n",fs);

	MPI_Finalize();
	return 0;
}
