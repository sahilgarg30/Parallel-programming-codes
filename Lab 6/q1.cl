// strtoggle.cl
__kernel void str_chgcase (__global char *A, __global char *B)
{
	int i = get_global_id(0);
	if (A[i] != '\0') {
		int temp = (int)A[i];
		int val = 0;
		while (temp > 0) {
			val = val * 10 + (temp % 10);
			temp = temp / 10;
		}
		printf("%c: %d -> %c: %d\n", A[i], A[i], val, val);
		B[i] = (char)val;
	} else {
		B[i] = A[i];
	}
}