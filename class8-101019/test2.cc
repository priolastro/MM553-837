#include <iostream>
#include "diag_utils.h"
#include "anharmonic_oscillator.h"

using namespace std;



int main() {

	const int n=10;
	const double lambda=0.2;

	AnharmonicOscillator ao(lambda, n);
	vector<vector<double> > hmat;
	ao.calc_h(hmat); 

	cout << "matrix created"<<endl;

	vector<double> evals;
	vector<vector<double> > evecs;

	diag_symm(hmat,evecs,evals);

	for (int i = 0 ; i<n; i++) {
		cout << "evals["<<i<<"] = "<<evals[i]<<endl;

		cout << "evec "<<i<<" = "<<endl;
		for (int j = 0 ; j<n; j++)  
			cout << evecs[i][j] << endl; 
	}
		return 0;
}
