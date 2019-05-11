#include <stdio.h>
#include <string.h>
#include <stdlib.h>
__global__ void add(int *a,int *b,int *c,int n) {
	int x = blockIdx.x;
	int y = blockIdx.y;
	c[x*n+y] = a[x*n+y]+b[x*n+y];
}

__global__ void multiply(int *a,int *b,int *c,int n) {
	int x = blockIdx.x;
	int y = blockIdx.y;
	int val = 0;
	for(int i=0;i<n;i++){
		val += a[x*n+i]*b[i*n+y];
	}
	c[x*n+y] = val;
}

int main(void) {
int a[50],b[50],c[50],d[50];
int *d_a,*d_b,*d_c,*d_d;

int n;
scanf("%d",&n);

for(int i=0;i<n;i++) for(int j=0;j<n;j++) scanf("%d",&a[i*n+j]);
for(int i=0;i<n;i++) for(int j=0;j<n;j++) scanf("%d",&b[i*n+j]);


cudaMalloc((void **)&d_a,sizeof(int)*n*n);
cudaMalloc((void **)&d_b,sizeof(int)*n*n);
cudaMalloc((void **)&d_c,sizeof(int)*n*n);
cudaMalloc((void **)&d_d,sizeof(int)*n*n);

cudaMemcpy(d_a, a, n*n*sizeof(int), cudaMemcpyHostToDevice);
cudaMemcpy(d_b, b, n*n*sizeof(int), cudaMemcpyHostToDevice);
dim3 d1(n,n,1);
dim3 d2(1,1,1);
add<<<d1,d2>>>(d_a,d_b,d_c,n);
cudaMemcpy(c,d_c, sizeof(int)*n*n, cudaMemcpyDeviceToHost);
for(int i=0;i<n;i++){
	for(int j=0;j<n;j++) printf("%d ",c[i*n+j]);
	printf("\n");
}

multiply<<<d1,d2>>>(d_a,d_b,d_d,n);
cudaMemcpy(d,d_d, sizeof(int)*n*n, cudaMemcpyDeviceToHost);
for(int i=0;i<n;i++){
	for(int j=0;j<n;j++) printf("%d ",d[i*n+j]);
	printf("\n");
}
cudaFree(d_a);
cudaFree(d_b);
cudaFree(d_c);
cudaFree(d_d);
return 0;
}
