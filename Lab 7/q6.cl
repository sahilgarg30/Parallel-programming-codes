__kernel void diagonal(__global int *A, __global int *B,int col)
{
	int i = get_global_id(0);
	int j = get_global_id(1);
	
	if(i==j){
		B[i*col+j] = 0;
	}else if(i>j){
		int val = 0;
		int x = A[i*col+j];
		while(x>0){
			val += x%10;
			x/=10;
		}
		B[i*col+j] = val;
	}else{
		int fact = 1;
		int x = A[i*col+j];
		while(x>0) {fact*=x;x--;}
		B[i*col+j] = fact;
	}
}