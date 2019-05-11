#include <iostream>

using namespace std;

int main(){
	int m,n,p;
	cin >> m >> n >> p;
	cout << "Enter the matrices -\n";
	int a[10][10],b[10][10],c[10][10];
	for(int i=0;i<m;i++) for(int j=0;j<n;j++) cin >> a[i][j];
	for(int i=0;i<n;i++) for(int j=0;j<p;j++) cin >> b[i][j];
	
	cout << "The product is - \n";

	for(int i=0;i<m;i++){
		for(int j=0;j<p;j++){
			c[i][j]=0;
			for(int k=0;k<n;k++){
				c[i][j] += a[i][k]*b[k][j];
			}
		}
	}

	for(int i=0;i<m;i++){
		for(int j=0;j<p;j++) cout << c[i][j] << "  ";
		cout << "\n";
	}

	return 0;
}