#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc,char *argv[]){
	int r;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&r);
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);

	if(r==0){
		printf("The sum is - %d\n",a+b);
	}
	else if(r==1){
		printf("The product is - %d\n",a*b);
	}
	else if(r==2){
		printf("The difference is - %d\n",a-b);
	}
	else if(r==3){
		printf("The division is - %f\n",(float)a/b);
	}else{
		printf("The remainder is - %d\n",a%b);
	}
	
	MPI_Finalize();
	return 0;
}