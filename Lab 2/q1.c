#include <mpi.h>
#include <stdio.h>
#include <ctype.h>

int main1(int argc,char *argv[]){
	int r;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&r);
	char s[6] = "heLlO";
	if(r==0){
		MPI_Ssend(s,6,MPI_CHAR,1,0,MPI_COMM_WORLD);
		MPI_Recv(s,6,MPI_CHAR,1,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("%d - %s",r,s);
	}else{
		MPI_Recv(s,6,MPI_CHAR,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		for(int i= 0;s[i]!='\0';i++){
			if(islower(s[i])) s[i] = toupper(s[i]);
			else s[i] = tolower(s[i]);
		}
		MPI_Ssend(s,6,MPI_CHAR,0,1,MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}
