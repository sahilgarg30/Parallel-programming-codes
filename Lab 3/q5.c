#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
int main5(int argc,char *argv[]){
	int r,n,m;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&r);
	MPI_Comm_size(MPI_COMM_WORLD,&n);

	char s1[100],s2[100],larr1[10],larr2[10],arr[20];

	if(r==0){
		gets(s1); gets(s2);
		for(m=0;s1[m]!='\0';m++);
	}

	MPI_Bcast(&m,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(s1,m/n,MPI_CHAR,larr1,m/n,MPI_CHAR,0,MPI_COMM_WORLD);
	MPI_Scatter(s2,m/n,MPI_CHAR,larr2,m/n,MPI_CHAR,0,MPI_COMM_WORLD);

	int j=0;
	for(int i=0;i<m/n;i++) {arr[j++] = larr1[i]; arr[j++]=larr2[i];}

	MPI_Gather(arr,2*(m/n),MPI_CHAR,s1,2*(m/n),MPI_CHAR,0,MPI_COMM_WORLD);

	if(r==0){
		printf("%s",s1);
	}
	MPI_Finalize();
	return 0;
}
