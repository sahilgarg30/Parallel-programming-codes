#include <mpi.h>
#include <stdio.h>

int main6(int argc,char *argv[]){
	int r,size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&r);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int n=0,arr[10],ele;
	int found = 0;

	if(r==0){
			scanf("%d",&n);
			MPI_Send(&n,1,MPI_INT,1,0,MPI_COMM_WORLD);
			for(int i=0;i<n;i++){
				scanf("%d",&arr[i]);
				MPI_Send(&arr[i],1,MPI_INT,1,i+1,MPI_COMM_WORLD);
			}

			scanf("%d",&ele);
			MPI_Send(&ele,1,MPI_INT,1,0,MPI_COMM_WORLD);

			for(int i=0;i<n/2;i++){
				if(arr[i]==ele){found = 1;break;}
			}

			int add;
			MPI_Recv(&add,1,MPI_INT,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			if(found || add)
			printf("Found.\n");
			else printf("Not found");
	}else{
		MPI_Recv(&n,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		for(int i=0;i<n;i++){
			MPI_Recv(&arr[i],1,MPI_INT,0,i+1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		}
		MPI_Recv(&ele,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		for(int i=n/2;i<n;i++) if(ele == arr[i]){found = 1;break;}
		MPI_Send(&found,1,MPI_INT,0,0,MPI_COMM_WORLD);
	}

	MPI_Finalize();
	return 0;
}
