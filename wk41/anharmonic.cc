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

	// Controlla quanto piccoli sono i valori di aspettazione di p e x, se molto piccoli li setta uguale a zero
	if (abs(expec_x < 0.00000001)){
		expec_x =0;
	}
	if (abs(expec_p < 0.00000001)){
		expec_p =0;
	}

	// Calcola incertezze operator p e x
	double Heis_uncert_relat = sqrt(expec_x_sq)*sqrt(expec_p_sq);

	cerr << "Valori di aspettazione dell'operatore posizione\n" << "x = " << expec_x << "\nx^2 = " << expec_x_sq << endl;
	cerr << "Valori di aspettazione dell'operatore momento\n" << "p = " << expec_p << "\np^2 = " << expec_p_sq << endl;
	if (Heis_uncert_relat >= 0.5 ){
		cerr << "Heisenberg’s uncertainty relation satisfied with a value of\n" <<  Heis_uncert_relat << endl;
	};

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
