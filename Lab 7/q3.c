#include <stdio.h>
#include <CL/cl.h>
#include<stdlib.h>

#define MAX_SOURCE_SIZE (0x100000)
int main3()
{
unsigned int a,b;
printf("Enter number of rows and columns - ");
scanf("%d %d",&a,&b);
int *A = (int *)malloc(sizeof(int)*a*b);
int *B = (int *)malloc(sizeof(int)*a*b);
for(int i=0;i<a;i++){
	for(int j=0;j<b;j++){
		scanf("%d",&A[i*b+j]);
	}
}

FILE *fp;
char *source_str;
size_t source_size;
fp = fopen("q3.cl", "r");
if (!fp) {
	fprintf(stderr, "Failed to load kernel.\n");
	getchar();
	exit(1);
}
source_str = (char*)malloc(MAX_SOURCE_SIZE);
source_size = fread( source_str, 1, MAX_SOURCE_SIZE, fp);
fclose( fp );
cl_platform_id platform_id = NULL;
cl_device_id device_id = NULL;
cl_uint ret_num_devices;
cl_uint ret_num_platforms;
cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_GPU, 1,&device_id, &ret_num_devices);
cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);
cl_command_queue command_queue = clCreateCommandQueue(context, device_id,NULL,&ret);
cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,a*b*sizeof(int), NULL, &ret);
cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY,a*b* sizeof(int), NULL, &ret);
ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0,a*b*sizeof(int),A, 0, NULL, NULL);
cl_program program = clCreateProgramWithSource(context, 1,(const char**)&source_str, (const size_t *)&source_size, &ret);
ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
cl_kernel kernel = clCreateKernel(program, "transpose", &ret);
ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);
ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&b_mem_obj);
ret = clSetKernelArg(kernel, 2, sizeof(int), (void *)&a);

size_t global_item_size[2] = {a,b};
size_t local_item_size[2] ={1,1};
ret = clEnqueueNDRangeKernel(command_queue, kernel,2, NULL, global_item_size, local_item_size, 0, NULL, NULL);
ret = clEnqueueReadBuffer(command_queue, b_mem_obj, CL_TRUE, 0,a*b*sizeof(int),B, 0, NULL, NULL);

for(int i=0;i<a;i++){
	for(int j=0;j<b;j++){
		printf("%d ",B[i*b+j]);
	}
	printf("\n");
}

ret = clReleaseKernel(kernel);
ret = clReleaseProgram(program);
ret = clReleaseMemObject(a_mem_obj);
ret = clReleaseMemObject(b_mem_obj);
ret = clReleaseCommandQueue(command_queue);
ret = clReleaseContext(context);
getchar();
free(A); free(B);
return 0;
}
