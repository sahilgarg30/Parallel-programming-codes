#include <mpi.h>
#include <stdio.h>


int isCircuit(int x){
	int v[4];
	for(int i=0;i<4;i++){
		v[i] = (x>>i)&1;
	}
	if(!(v[0]&v[1]) & (v[2]|v[3])) return 1;
	return 0;
}

int main(int argc,char *argv[]){
	int r;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&r);
	for(int i=0;i<(1<<4);i++){
		if((i%4==r) && isCircuit(i)) printf("%d  ",i);
	}
	MPI_Finalize();
	return 0;
}