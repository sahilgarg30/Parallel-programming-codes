#include <mpi.h>
#include <stdio.h>

int main(int argc,char *argv[]){
	int r,n;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&r);
	MPI_Comm_size(MPI_COMM_WORLD,&n);
	int arr[100];
	int ele,size=500;

	MPI_Buffer_attach(arr,size);
	if(r==0){
			for(int i=0;i<n;i++){
				scanf("%d",&arr[i]);
				if(i!=0) MPI_Bsend(&arr[i],1,MPI_INT,i,0,MPI_COMM_WORLD);
				else ele = arr[i];
			}
	}else{
		MPI_Recv(&ele,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	}

	if(r%2==0){
		printf("%d - square %d\n",r,ele*ele);
	}else{
		printf("%d - cube %d\n",r,ele*ele*ele);
	}
	MPI_Buffer_detach(arr,&size);
	MPI_Finalize();
	return 0;
}
