#include <iostream>
#include "diag_utils.h"

using namespace std;

int main() {

	std::vector<std::vector<double> > A(4,std::vector<double>(4,0.0));
	A[0][0]= -7.7; 
	A[1][0]=  2.1;  A[0][1]=A[1][0];
	A[1][1]=  8.3;
	A[2][0]= -3.7;  A[0][2]=A[2][0]; 
	A[2][1]=-16.0;  A[1][2]=A[2][1];
	A[2][2]=-12.0;
	A[3][0]=  4.4;  A[0][3]=A[3][0]; 
	A[3][1]=  4.6;  A[1][3]=A[3][1];
	A[3][2]= -1.04; A[2][3]=A[3][2];
	A[3][3]= -3.7;

	vector<double> evals;
	vector<vector<double> > evecs;

	diag_symm(A,evecs,evals);

	for (int i = 0 ; i<4; i++) {
		cout << "evals["<<i<<"] = "<<evals[i]<<endl;

		cout << "evec "<<i<<" = "<<endl;
		for (int j = 0 ; j<4; j++)  
			cout << evecs[i][j] << endl; 
	}
		return 0;
}
