__kernel void str_rev(__global char *A, __global int *B)
{
	int i = get_global_id(0);
	
	if(i==0) return;
	int start = B[i-1], end = B[i];
	
	printf("%d ",B[i]);
	int len = (end-start-1)/2;
	for(int j=0;j<len;j++){
		char temp = A[j+start+1];
		A[j+start+1] = A[end-j-1];
		A[end-j-1] = temp;
	}
}