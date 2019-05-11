#include <stdio.h>
#include <string.h>
__global__ void add(char *a,int size1) {
	int id = blockIdx.x;
	char temp = a[id];
	a[id] = a[size1-id-1];
	a[size1-id-1] = temp;
}

int main2(void) {
char a[50];
char *d_a;
scanf("%s",a);

int size1 = sizeof(char)*strlen(a);

cudaMalloc((void **)&d_a, size1);

cudaMemcpy(d_a,a, size1, cudaMemcpyHostToDevice);
add<<<size1/2,1>>>(d_a,size1);
cudaMemcpy(a,d_a,size1, cudaMemcpyDeviceToHost);
printf("%s",a);
cudaFree(d_a);

return 0;
}
