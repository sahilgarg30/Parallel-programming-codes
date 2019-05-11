__kernel void divide(__global int *A, __global int *B,int col)
{
	int i = get_global_id(0);
	int j = get_global_id(1);
	
	if(i < col/2 && j < col/2) B[i*col+j] = A[i*col+j]+1;
	else if(i<col/2) B[i*col+j] = A[i*col+j]+2;
	else if(j<col/2) B[i*col+j] = A[i*col+j]+3;
	else B[i*col+j] = A[i*col+j]+4;
}