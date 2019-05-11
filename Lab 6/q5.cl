// strtoggle.cl
__kernel void str_copy(__global char *A, __global char *B, int n)
{
	int i = get_global_id(0);
	int j,len=0;
	while(A[len]!='\0') len++;
	for(j=0;j<n;j++)
		B[(len*j)+i] = A[i];
}