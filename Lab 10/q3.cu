#include <stdio.h>
#include <string.h>
__global__ void bin(char *a,int size1) {
	int id = blockIdx.x;
	int val = a[id],res = 0,x = 1;
	while(val>0){
		res += x*(val%2);
		x *=10;
		val /=2;
	}
	printf("%d - %d\n",id,res);
}

int main3(void) {
char a[50];
char *d_a;
scanf("%s",a);

int size1 = sizeof(char)*strlen(a);

cudaMalloc((void **)&d_a, size1);

cudaMemcpy(d_a,a, size1, cudaMemcpyHostToDevice);
bin<<<size1,1>>>(d_a,size1);
cudaFree(d_a);
return 0;
}
