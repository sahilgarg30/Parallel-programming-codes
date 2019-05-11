__kernel void str_rev(__global char *A, __global int *B,__global char *C,int slen)
{
	int i = get_global_id(0);
	int j;
	if(i==0) return;
	int start = B[i-1], end = B[i];

	int len = (end-start-1);
	if(slen==len){
	for(j=0;j<len;j++){
		if(A[j+start+1]!=C[j]) break;		
	}
	if(j==len) printf("Found at index - %d\n",start+1);
	}
}

