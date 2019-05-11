__kernel void vector_swap(__global int *A, __global int *C, __global int *D)
{
int i = get_global_id(0);
if(i==(*D-1)){
	C[i] = A[i];
}else if(i%2==0){
	C[i] = A[i+1];
	C[i+1] = A[i];
}
}