#include <iostream>
#include <iomanip>
#include <fstream>
#include "diag_utils.h"
#include "finite_well.h"
#include "wave_function.h"

using namespace std;


int main(int argc, char** argv) {

	if (argc != 8) {
		cerr << "usage: " << argv[0] <<" <well width ([-a,a])> <well depth (V_0)> <nmin> <nmax> <level>" << endl;
		return 1;
	}

	double a;
	double b;
	double v0;
	double v1;
	int nmin; 
	int nmax;
	int level; 

	double xmin = -5;
	double xmax = 5;
	int nx=1e3;

	int npoint=1e4;

	stringstream(argv[1]) >> a; 
	stringstream(argv[2]) >> b;
	stringstream(argv[3]) >> v0; 
	stringstream(argv[4]) >> v1; 
	stringstream(argv[5]) >> nmin; 
	stringstream(argv[6]) >> nmax;
	stringstream(argv[7]) >> level;

	ofstream eigenvalues("eigenvalues.dat");
	eigenvalues << setprecision(16);

	ofstream fwave("wave_func.dat");
	fwave<<setprecision(16);
	// ofstream fout("energy.dat");
	// fout<<setprecision(16);

	vector<double> coeffs; 

	for (int n = nmin ; n<=nmax ; n++) {
		cerr << "Diagonalizing " << n << " dimensional matrix" << "\r" << endl;
		FiniteWell fw(a, b, v0, v1, n, npoint);
		vector<vector<double> > hmat;
		fw.calc_h(hmat); 
		vector<double> evals;
		vector<vector<double> > evecs;
		diag_symm(hmat,evecs,evals);
		if (n==nmax){
			coeffs=evecs[level];
			// calc_expectation_value_x(n, coeffs, expec_x, expec_x_sq);
			// calc_expectation_value_p(n, coeffs, expec_p, expec_p_sq);
		}
		eigenvalues << n << "    "<<evals[level]<<endl;
	
	} 

	cerr << "Do you want to compute the wave function? [y/n] ";
	char answer;
	cin >> answer;
	cout << endl; 
	if (answer == 'n'){
		cerr << "You decided to not compute the wave function!\n";
		return 0;
	}
	cerr << "Computing the wavefunction" << endl;
	WaveFunction wfun(coeffs);
	double eps=(xmax-xmin)/(nx-1);
	double x=xmin;
	double percent;
	for (int n=0; n<nx; n++) {
		percent = (n*100)/double(nx);
		cerr << "Progress " << percent << "%\r";
		fwave << x<< "   " << wfun(x) <<endl;
		x += eps; 
	}
	return 0;
}
