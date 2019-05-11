__kernel void sort(__global int *A, int ph)
{
	int id = get_global_id(0);
	
	if(ph%2 == 0 && id % 2==0){
		if(A[id]>A[id+1]){
		int temp = A[id];
		A[id] = A[id+1];
		A[id+1] = temp;
		}
	}
	else if(ph%2!=0 && id%2!=0){
		if(A[id]>A[id+1]){
		int temp = A[id];
		A[id] = A[id+1];
		A[id+1] = temp;
		}
	}
}