#include <stdio.h>
__global__ void trans(int *a, int *c,int n) {
c[blockIdx.x*n + threadIdx.x] = a[threadIdx.x*n + blockIdx.x];
}

int main(void) {
int n;
printf("Enter n:");
scanf("%d",&n);
int a[n*n], b[n*n];
int *d_a, *d_b;
int size = n*n*sizeof(int);
// Allocate space for device copies of a, b, c
cudaMalloc((void **)&d_a, size);
cudaMalloc((void **)&d_b, size);
for(int i=0;i<n*n;i++)
	scanf("%d",&a[i]);
cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
trans<<<n,n>>>(d_a, d_b,n);
cudaMemcpy(b, d_b, size, cudaMemcpyDeviceToHost);
for(int i=0;i<n;i++){
	for(int j=0;j<n;j++)
	printf("%d ",b[i*n+j]);
	printf("\n");
}
cudaFree(d_a);
cudaFree(d_b);
return 0;
}
