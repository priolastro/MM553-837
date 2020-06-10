#include <iostream>
#include <iomanip>
#include <fstream>
#include "diag_utils.h"
#include "anharmonic_oscillator.h"
#include "wave_function.h"

using namespace std;

typedef vector<vector<double> > MatType;

double calc_expectation_value_x_square(int N, vector<double> coeffs){

		MatType x;
		MatType x_square;
		x.resize(N);
		x_square.resize(N);

		for (int i = 0; i<N; i++){ 	
			x[i].resize(N);
			x_square[i].resize(N);
			}

		//calcola la matrice x 
		for (int i = 0; i<N; i++){
			for (int j = 0 ; j<N; j++) {
				if (abs(i-j)==1){
					x[i][j]=0.5*sqrt((double)(i+j+1));
				}
				else {						
					x[i][j]=0.0;
				}
			}
		}

		//calcola la matrice x^2
		for (int i = 0; i<N; i++) {
			for (int j = 0; j<N; j++){
				for (int k = 0; k<N; k++){
					x_square[i][j] += x[i][k]*x[k][j];
				}
			}
		}

		double expectation;
		for (int i=0; i<N-1; i++){
			for (int j=0; j<N-1; j++){
				expectation += x_square[i][j]*coeffs[i]*coeffs[j];
			}
		}

	return expectation;
	}



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
			cerr << calc_expectation_value_x_square(n, coeffs);
		}
		eigenvalues << n << "    "<< evals[level] << endl;
	}


	// cerr << "Computing wave function for N=" << nmax << endl;
	// WaveFunction wfun(coeffs);
	// double eps = (xmax-xmin)/(nx-1);
	// double x = xmin;
	// double percent;
	// for (int n=0; n<nx; n++){
	// 	percent = (n*100)/double(nx);
	// 	cerr << "Progress " << percent << "%\r";
	// 	fwave << x << "	" << wfun(x) << endl;
	// 	x += eps;
	// }
	
	return 0;
}
