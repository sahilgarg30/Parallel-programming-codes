// strtoggle.cl
__kernel void str_chgcase (__global char *A, __global char *B)
{
	int i = get_global_id(0);
	char c = A[i];
	if(c=='a'||c=='e'||c=='i'||c=='o'||c=='u') B[i] = A[i]-32;
	else if(c=='A'||c=='E'||c=='I'||c=='O'||c=='U') B[i] = A[i];
	else if(c>=65 && c<=90) B[i] = A[i]+32;
	else B[i] = A[i];
}