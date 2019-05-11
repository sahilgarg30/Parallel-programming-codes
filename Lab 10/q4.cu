#include <stdio.h>
#include <string.h>
#include <stdlib.h>
__global__ void add(char *a, char *b,int size1,int size2,int *c) {
	int id = blockIdx.x;
	if(id+size2 > size1) return;
	int i;
	for(i=0;i<size2;i++){
		if(a[id+i]!=b[i]) break;
	}
	if(i==size2 && (id==0 || a[id-1]==' ') && (id+size2 == size1 || a[id+size2]==' ')){
		c[id] = 1;
		return;
	}
	c[id] = 0;
}
int main4(void) {
char a[50],b[50];
char *d_a, *d_b;
int c[50]; int *d_c;
gets(a);
scanf("%s",b);

int size1 = sizeof(char)*strlen(a);
int size2 = sizeof(char)*strlen(b);

cudaMalloc((void **)&d_a, size1);
cudaMalloc((void **)&d_b, size2);
cudaMalloc((void **)&d_c,sizeof(int)*size1);

cudaMemcpy(d_a, a, size1, cudaMemcpyHostToDevice);
cudaMemcpy(d_b, b, size2, cudaMemcpyHostToDevice);
add<<<size1,1>>>(d_a, d_b,size1,size2,d_c);
cudaMemcpy(c,d_c, sizeof(int)*size1, cudaMemcpyDeviceToHost);
int cs = 0;
for(int i=0;i<size1;i++) if(c[i]==1) cs++;
printf("%d",cs);
cudaFree(d_a);
cudaFree(d_b);
cudaFree(d_c);
return 0;
}
