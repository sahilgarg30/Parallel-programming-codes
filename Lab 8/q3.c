#include <stdio.h>
#include<time.h>
#include <CL/cl.h>
#include<string.h>
#include<stdlib.h>

#define MAX_SOURCE_SIZE (0x100000)
#define STR_SIZE 200
int main3(void)
{
char tempstr[STR_SIZE];
printf("Enter str: ");
gets(tempstr);
tempstr[strlen(tempstr)]='\0';
int len= strlen(tempstr);
len++;
char *str = (char*)malloc(sizeof(char)*len);
strcpy(str,tempstr);

printf("Enter word: ");
gets(tempstr);
tempstr[strlen(tempstr)]='\0';
int len2 = strlen(tempstr);
char *str2 = (char*)malloc(sizeof(char)*len2);
strcpy(str2,tempstr);

int spaces[100],k=1;
spaces[0]=-1;
for(int i=0;i<=len;i++){
	if(str[i]==' ' || str[i]=='\0'){
		spaces[k++]=i;
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
cl_command_queue command_queue = clCreateCommandQueue(context, device_id, CL_QUEUE_PROFILING_ENABLE, &ret);
cl_mem s_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE,len*sizeof(char), NULL, &ret);
cl_mem s2_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,len2*sizeof(char), NULL, &ret);
cl_mem t_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,k*sizeof(int), NULL, &ret);
ret = clEnqueueWriteBuffer(command_queue, s_mem_obj, CL_TRUE, 0,len*sizeof(char), str, 0, NULL, NULL);
ret = clEnqueueWriteBuffer(command_queue, s2_mem_obj, CL_TRUE, 0,len2*sizeof(char), str2, 0, NULL, NULL);
ret = clEnqueueWriteBuffer(command_queue, t_mem_obj, CL_TRUE, 0,k*sizeof(int), spaces, 0, NULL, NULL);

cl_program program = clCreateProgramWithSource(context, 1,(const char**)&source_str, (const size_t *)&source_size, &ret);
ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
cl_kernel kernel = clCreateKernel(program, "str_rev", &ret);
ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&s_mem_obj);
ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&t_mem_obj);
ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&s2_mem_obj);
ret = clSetKernelArg(kernel, 3, sizeof(int), (void *)&len2);

size_t global_item_size = k-1;
size_t local_item_size =1;
cl_event event;
ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, &event);

ret = clReleaseKernel(kernel);
ret = clReleaseProgram(program);
ret = clReleaseMemObject(s_mem_obj);
ret = clReleaseMemObject(t_mem_obj);
ret = clReleaseCommandQueue(command_queue);
ret = clReleaseContext(context);
getchar();
free(str);
return 0;
}
