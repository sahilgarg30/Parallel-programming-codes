#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int main6(int argc,char *argv[]){
	int r,n,m;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&r);
	MPI_Comm_size(MPI_COMM_WORLD,&n);

	char s[100],larr[10];
	int a[100],la[10];

	if(r==0){
		gets(s);
		for(m=0;s[m]!='\0';m++);
	}

	MPI_Bcast(&m,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(s,m/n,MPI_CHAR,larr,m/n,MPI_CHAR,0,MPI_COMM_WORLD);

	for(int i=0;i<m/n;i++){
		if(isupper(larr[i])) larr[i] = tolower(larr[i]);
		else larr[i] = toupper(larr[i]);
		la[i] = larr[i];
	}

	MPI_Gather(&larr,m/n,MPI_CHAR,s,m/n,MPI_CHAR,0,MPI_COMM_WORLD);
	MPI_Gather(&la,m/n,MPI_INT,a,m/n,MPI_INT,0,MPI_COMM_WORLD);

	if(r==0){
		printf("%s\n",s);
		for(int i=0;i<m;i++){
			printf("%d ",a[i]);
		}
	}
	MPI_Finalize();
	return 0;
}
