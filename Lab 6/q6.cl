// strtoggle.cl
__kernel void str_copy(__global char *A, __global char *B)
{
	int i = get_global_id(0);
	int j,len=0;
	for(j=1;j<=i;j++)
		len += j;
		
	for(j=0;j<=i;j++)
		B[len+j] = A[i];
}