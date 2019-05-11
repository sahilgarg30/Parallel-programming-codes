#include <mpi.h>
#include <stdio.h>

int main8(int argc,char *argv[]){
	int r,n;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&r);
	MPI_Comm_size(MPI_COMM_WORLD,&n);
	int res = 1,ele;

	if(r==0){
			for(int i=1;i<n;i++){
				MPI_Recv(&ele,1,MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
				res += ele;
			}
			printf("%d \n",res);
	}else{
		if(n%2==0){
			ele = r+1;
		}else{
			if(r%2!=0){
				ele = 0;
				for(int i=1;i<=r+1;i++) ele+=i;
			}else{
				ele = 1;
				for(int i=2;i<=r+1;i++) ele*=i;
			}
		}
		MPI_Send(&ele,1,MPI_INT,0,0,MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}
