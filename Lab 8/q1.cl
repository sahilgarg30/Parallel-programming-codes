__kernel void sort(__global char *A, __global char *B,int n)
{
	int id = get_global_id(0);
	int c = 0;
	for(int i=0;i<n;i++){
		if(A[i]<A[id]||(A[i]==A[id] && i<id))
			c++;
	}
	B[c] = A[id];
}