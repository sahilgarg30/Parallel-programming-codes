#include <stdio.h>
#include "mpi.h"

int main4(int a,char *b[]) {

	int rank, ele=1;
	int error;

	MPI_Init(&a, &b);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	//MPI_Errhandler_set(MPI_COMM_WORLD,MPI_ERRORS_ARE_FATAL);
	MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN);

	error = MPI_Bcast(&ele, 1, MPI_INT, 4, MPI_COMM_WORLD);

	if (error != MPI_SUCCESS) {
		char s[100];
		int len, class1;
		MPI_Error_string(error, s, &len);
		MPI_Error_class(error, &class1);
		printf("Error description is %s", s);
		printf("Error class is %d", class1);
	}

	printf("End of program\n");
	if(rank==0) scanf("%d",&ele);
	MPI_Finalize();
	return 0;
}
