#include <stdio.h>
#include <string.h>
__global__ void add(char *a, char *b,int size1,int size2) {
	int id = blockIdx.x;
	if(id+size2 > size1) return;
	int i;
	for(i=0;i<size2;i++){
		if(a[id+i]!=b[i]) break;
	}
	if(i==size2) printf("%d ",id);
}
int main1(void) {
char a[50],b[50];
char *d_a, *d_b;
scanf("%s %s",a,b);

int size1 = sizeof(char)*strlen(a);
int size2 = sizeof(char)*strlen(b);

cudaMalloc((void **)&d_a, size1);
cudaMalloc((void **)&d_b, size2);

cudaMemcpy(d_a, a, size1, cudaMemcpyHostToDevice);
cudaMemcpy(d_b, b, size2, cudaMemcpyHostToDevice);
add<<<size1,1>>>(d_a, d_b,size1,size2);
cudaFree(d_a);
cudaFree(d_b);
return 0;
}
