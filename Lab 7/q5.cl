__kernel void sums(__global int *A, __global int *B,int row,int col)
{
	int i = get_global_id(0);
	int j = get_global_id(1);
	
	int val = 0;
	if(A[i*col+j]%2==0)
		for(int k=0;k<col;k++) val = val+A[i*col+k];
	else for(int k=0;k<row;k++) val = val+A[k*col+j];
	B[i*col+j] = val;
}