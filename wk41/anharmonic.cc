#include <iostream>
#include <iomanip>
#include <fstream>
#include <complex>
#include <cmath>
#include "diag_utils.h"
#include "anharmonic_oscillator.h"
#include "wave_function.h"
#include "expectation_values.h"

using namespace std;

int main(int argc, char** argv) {

	if (argc != 5) {
		cerr << "usage: " << argv[0] <<" <lambda> <nmin> <nmax> <level>" << endl;
		return 1;
	}

	double lambda;
	int nmin; 
	int nmax ;
	int level; 
	
	
	double xmin = -5;
	double xmax = 5;
	int nx=1e3;

	stringstream(argv[1]) >> lambda; 
	stringstream(argv[2]) >> nmin; 
	stringstream(argv[3]) >> nmax;
	stringstream(argv[4]) >> level;

	ofstream eigenvalues("eigenvalues.dat");
	eigenvalues << setprecision(16);


	vector<double> coeffs;

	ofstream fwave("wave_func.dat");
	fwave << setprecision(16);

	//inizializzo valori aspettazione
	double expec_x, expec_p;
	double expec_x_sq, expec_p_sq;

	for (int n = nmin ; n<=nmax ; n++) {
		cerr << "Diagonalizing " << n << " dimensional matrix" << "\r" << endl;
		AnharmonicOscillator ao(lambda, n);
		vector<vector<double>> hmat;
		ao.calc_h(hmat); 
		vector<double> evals;
		vector<vector<double>> evecs;
		diag_symm(hmat,evecs,evals);
		if (n == nmax){
			coeffs = evecs[level];
			calc_expectation_value_x(n, coeffs, expec_x, expec_x_sq);
			calc_expectation_value_p(n, coeffs, expec_p, expec_p_sq);
		}
		eigenvalues << n << "    "<< evals[level] << endl;
	}
	cerr << "I valori di aspettazione dell'operatore x e x^2 sono\n" << expec_x << "\n" << expec_x_sq << endl;
	cerr << "I valori di aspettazione dell'operatore p e p^2 sono\n" << expec_p << "\n" << expec_p_sq << endl;

	cerr << "Computing wave function for N=" << nmax << endl;
	WaveFunction wfun(coeffs);
	double eps = (xmax-xmin)/(nx-1);
	double x = xmin;
	double percent;
	for (int n=0; n<nx; n++){
		percent = (n*100)/double(nx);
		cerr << "Progress " << percent << "%\r";
		fwave << x << "	" << wfun(x) << endl;
		x += eps;
	}
	return 0;
}
