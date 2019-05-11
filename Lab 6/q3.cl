__kernel void str_rev(__global char *A, __global char *B)
{
	int i = get_global_id(0);
	int len=0;
	while(A[len]!='\0') len++;
	B[i] = A[len-i-1];
	B[len-i-1] = A[i];
}