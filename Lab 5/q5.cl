__kernel void vector_prime(__global int *A, __global int *C)
{
int i = get_global_id(0);
int num = A[i];

int isPrime = 1;
int j = 0;

for(j=2 ; j <= num/2 ; j = j+1) if(num%j == 0) isPrime = 0;

if(isPrime == 1) { C[i] = num;}
else { C[i] = num*num; }

}