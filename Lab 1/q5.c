#include <mpi.h>
#include <stdio.h>

int isPrime(int x){
	if(x==2) return 1;
	for(int i=2;i<=x/2;i++){
		if(x%i==0) return 0;
	}
	return 1;
}

int main(int argc,char *argv[]){
	int r;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&r);
	for(int i=2;i<=100;i++){
		if((r%2==i%2) && isPrime(i)) printf("%d  ",i);
	}
	MPI_Finalize();
	return 0;
}