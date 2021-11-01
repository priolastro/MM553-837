#include <iostream>
#include <iomanip>
#include <fstream>
#include "diag_utils.h"
#include "anharmonic_oscillator.h"
#include "wave_function.h"

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

	ofstream fout("energy.dat");
	fout<<setprecision(16);
	vector<double> coeffs; 

	for (int n = nmin ; n<=nmax ; n++) {
		AnharmonicOscillator ao(lambda, n);
		vector<vector<double> > hmat;
		ao.calc_h(hmat); 

		vector<double> evals;
		vector<vector<double> > evecs;

		diag_symm(hmat,evecs,evals);
		if (n==nmax)
			coeffs=evecs[level];

		fout << n << "    "<<evals[level]<<endl;
	
	} 

	for (int n=0; n<coeffs.size();++n)
		cout <<"coefs["<<n<<"] = "<<coeffs[n]<<endl;

	cout << "computing wavefunction" << endl;

	WaveFunction wfun(coeffs);
		
	ofstream fwave("wave_func.dat");
	fwave<<setprecision(16);
	
	double eps=(xmax-xmin)/(nx-1);
	double x=xmin;
	for (int n=0; n<nx; n++) {
		fwave << x<< "   " << wfun(x) <<endl;
		x += eps; 
	}

	cout << "<x^2> = " << wfun.average_xsq() << endl;
	
	return 0;
}
