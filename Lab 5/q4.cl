__kernel void vector_oct(__global int *A, __global int *C)
{
int i = get_global_id(0);
int num = A[i];
int temp = 0;
int x=1;
while (num > 0) {
	int p = (num % 10) * x;
	temp = temp + p;
	num = num / 10;
	x = x * 2;
}
C[i] = temp;
}