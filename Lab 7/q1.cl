__kernel void powers(__global int *A, __global int *B,int col)
{
	int i = get_global_id(0);
	int j = get_global_id(1);
	
	int val = A[i*col+j];
	for(int k=0;k<i;k++) val *= A[i*col+j];
	B[i*col+j] = val;
}