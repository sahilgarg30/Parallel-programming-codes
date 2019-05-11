__kernel void vector_binary(__global int *A, __global int *C)
{
int i = get_global_id(0);
int num = A[i];
int res = 0;
int x = 1;
while (num > 0) {
	int dig = num % 10;
	res = res  + ((dig + 1) % 2)*x;
	num = num / 10;
	x = x*10;
}
C[i] = res;
}