#include <stdio.h>
__global__ void add4(int *a, int *b, int *c) {
c[threadIdx.x] = a[threadIdx.x] + b[threadIdx.x];
}
int main5(void) {
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
add4<<<1,r*col>>>(d_a, d_b, d_c);
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
