#include <stdio.h>
__global__ void add1(int *a, int *b, int *c) {
c[blockIdx.x] = a[blockIdx.x] + b[blockIdx.x];
}
int main1(void) {
int n;
printf("Enter n:");
scanf("%d",&n);
int a[n], b[n], c[n];
int *d_a, *d_b, *d_c;
int size =n*sizeof(int);
// Allocate space for device copies of a, b, c
cudaMalloc((void **)&d_a, size);
cudaMalloc((void **)&d_b, size);
cudaMalloc((void **)&d_c, size);
for(int i=0;i<n;i++)
	scanf("%d",&a[i]);
for(int i=0;i<n;i++)
	scanf("%d",&b[i]);
cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);
add1<<<n,1>>>(d_a, d_b, d_c);
// Copy result back to host
cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);
//print result
for(int i=0;i<n;i++)
	printf("%d ",c[i]);
// Cleanup
cudaFree(d_a);
cudaFree(d_b);
cudaFree(d_c);
return 0;
}
