#include <stdio.h>
__global__ void mul2(int *a, int *b, int *c,int col) {
int x;
for(int i=0;i<blockDim.x;i++){
	x=0;
	for(int j=0;j<col;j++){
		x+= a[i*col+j] *b[j*col+threadIdx.x];
	}
	c[i*col+ threadIdx.x]=x;
}
}
int main10(void) {
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
printf("Enter the 2 matrices: \n");
for(int i=0;i<r*col;i++)
	scanf("%d",&a[i]);
for(int i=0;i<r*col;i++)
	scanf("%d",&b[i]);
cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);
mul2<<<1,r>>>(d_a, d_b, d_c,col);
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
