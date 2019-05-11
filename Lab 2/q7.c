#include <mpi.h>
#include <stdio.h>

int main7(int argc,char *argv[]){
	int r,n;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&r);
	MPI_Comm_size(MPI_COMM_WORLD,&n);
	int arr[100],ele;

	if(r==0){
			for(int i=0;i<n;i++){
				scanf("%d",&arr[i]);
				if(i!=0) MPI_Send(&arr[i],1,MPI_INT,i,0,MPI_COMM_WORLD);
				else ele = arr[i];
			}
	}else{
		MPI_Recv(&ele,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	}

	if(ele == 2){
		printf("%d - 2 is prime\n",r);
	}else{
		int i;
		for(i=2;i<=n/2;i++){
			if(ele % i == 0) break;
		}
		if(i== n/2+1)
			printf("%d - %d is prime\n",r,ele);
		else
			printf("%d - %d is not prime\n",r,ele);
	}
	MPI_Finalize();
	return 0;
}
