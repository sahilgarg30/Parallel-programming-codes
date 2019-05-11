#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
int nvow(char c){
	switch(c){
		case 'a':
		case 'e':
		case 'i':
		case 'o':
		case 'u': return 0;
	}
	return 1;
}
int main4(int argc,char *argv[]){
	int r,n,m;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&r);
	MPI_Comm_size(MPI_COMM_WORLD,&n);

	char s[100],larr[10];
	int a[10];

	if(r==0){
		gets(s);
		for(m=0;s[m]!='\0';m++);
	}

	MPI_Bcast(&m,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(s,m/n,MPI_CHAR,larr,m/n,MPI_CHAR,0,MPI_COMM_WORLD);

	int c=0;
	for(int i=0;i<m/n;i++) if(nvow(larr[i])) c++;

	MPI_Gather(&c,1,MPI_INT,a,1,MPI_INT,0,MPI_COMM_WORLD);

	if(r==0){
		c=0;
		for(int i=0;i<n;i++){printf("%d  ",a[i]);c+=a[i];}
		printf("\n%d",c);
	}
	MPI_Finalize();
	return 0;
}
