#include <stdio.h>
__global__ void add3(int *a, int *b, int *c,int r) {
for(int i=0;i<r;i++)
c[i*blockDim.x+ threadIdx.x] = a[i*blockDim.x+ threadIdx.x] + b[threadIdx.x+i*blockDim.x];
}
int main4(void) {
int r,col;
printf("Enter dimensions:");
scanf("%d %d",&r,&col);
int a[r*col], b[r*col], c[r*col];
int *d_a, *d_b, *d_c;
int size = r*col*sizeof(int);
// Allocate space for device copies of a, b, c
cudaMalloc((void **)&d_a, size);
cudaMalloc((void **)&d_b, size);
cudaMalloc((void **)&d_c, size);
for(int i=0;i<r*col;i++)
	scanf("%d",&a[i]);
for(int i=0;i<r*col;i++)
	scanf("%d",&b[i]);
cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);
add3<<<1,col>>>(d_a, d_b, d_c,r);
// Copy result back to host
cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);
//print result
for(int i=0;i<r*col;i++){
	printf("%d ",c[i]);
}
// Cleanup
cudaFree(d_a);
cudaFree(d_b);
cudaFree(d_c);
return 0;
}
