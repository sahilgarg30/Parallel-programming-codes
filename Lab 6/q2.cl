// strtoggle.cl
__kernel void str_copy(__global char *A, __global char *B)
{
	int i = get_global_id(0);
	int j,len=0;
	while(A[len]!='\0') len++;
	for(j=0;j<len;j++)
		B[(len*i)+j] = A[j];
}