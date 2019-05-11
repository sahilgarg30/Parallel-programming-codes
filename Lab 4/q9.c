#include <mpi.h>
#include <stdio.h>
#include<stdlib.h>
int main9(int argc,char *argv[]){
	int r,n,cur=1;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&r);
	MPI_Comm_size(MPI_COMM_WORLD,&n);

	char s[100],l[100];

	if(r==0){
		gets(s);
	}

	MPI_Scatter(s,1,MPI_CHAR,l,1,MPI_CHAR,0,MPI_COMM_WORLD);
	for(int i=1;i<=r;i++) l[i]=l[0];

	if(r==0){
		for(int i=1;i<n;i++){
			MPI_Recv(&s[cur],i+1,MPI_CHAR,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			cur += i+1;
		}
		s[(n*(n+1))/2]='\0';
		printf("%s",s);
	}else{
		MPI_Send(l,r+1,MPI_CHAR,0,0,MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}
