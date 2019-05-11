__kernel void transpose(__global int *A, __global int *B,int col)
{
	int i = get_global_id(0);
	int j = get_global_id(1);
	
	B[i*col+j] = A[j*col+i];
}