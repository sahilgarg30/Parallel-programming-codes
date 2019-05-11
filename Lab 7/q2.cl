__kernel void change(__global int *A, __global int *B,int row,int col)
{
	int i = get_global_id(0);
	int j = get_global_id(1);
	
	if(i==0 || j==0 || i==row-1 || j==col-1){
		B[i*col+j] = A[i*col+j];
	}else{
		int val = A[i*col+j];
		int x = 1;
		int res = 0;
		while(val>0){
			res = res+(((val%2)+1)%2)*x;
			x *= 10;
			val = val/2;
		}
		B[i*col+j] = res;
	}
}