#include <stdio.h>
#include <CL/cl.h>
#include<string.h>
#include<stdlib.h>

#define MAX_SOURCE_SIZE (0x100000)
#define STR_SIZE 100
int main1(void)
{
char tempstr[STR_SIZE];
int i;

printf("Enter str: ");
gets(tempstr);
tempstr[strlen(tempstr)]='\0';
int len= strlen(tempstr);
char *str = (char*)malloc(sizeof(char)*len);
strcpy(str,tempstr);

FILE *fp;
char *source_str;
size_t source_size;
fp = fopen("q1.cl", "r");
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
cl_command_queue command_queue = clCreateCommandQueue(context, device_id,NULL, &ret);
cl_mem s_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,len*sizeof(char), NULL, &ret);
cl_mem t_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY,len* sizeof(char), NULL, &ret);
ret = clEnqueueWriteBuffer(command_queue, s_mem_obj, CL_TRUE, 0,len *sizeof(char), str, 0, NULL, NULL);
cl_program program = clCreateProgramWithSource(context, 1,(const char**)&source_str, (const size_t *)&source_size, &ret);
ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
cl_kernel kernel = clCreateKernel(program, "sort", &ret);
ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&s_mem_obj);
ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&t_mem_obj);
ret = clSetKernelArg(kernel, 2, sizeof(int), (void *)&len);

size_t global_item_size = len;
size_t local_item_size =1;
ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
char *strres = (char*)malloc(sizeof(char)*len);
ret = clEnqueueReadBuffer(command_queue, t_mem_obj, CL_TRUE, 0,len*sizeof(char), strres, 0, NULL, NULL);
printf("\nDone");
strres[len]='\0';
printf("\nResultant string :%s",strres);
ret = clReleaseKernel(kernel);
ret = clReleaseProgram(program);
ret = clReleaseMemObject(s_mem_obj);
ret = clReleaseMemObject(t_mem_obj);
ret = clReleaseCommandQueue(command_queue);
ret = clReleaseContext(context);
getchar();
free(str);
free(strres);
return 0;
}
