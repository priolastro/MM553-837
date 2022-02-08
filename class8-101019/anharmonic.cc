#include <iostream>
#include <iomanip>
#include <fstream>
#include "diag_utils.h"
#include "anharmonic_oscillator.h"

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
	
	stringstream(argv[1]) >> lambda; 
	stringstream(argv[2]) >> nmin; 
	stringstream(argv[3]) >> nmax;
	stringstream(argv[4]) >> level;

	ofstream fout("energy.dat");
	fout<<setprecision(16);
	for (int n = nmin ; n<=nmax ; n++) {
		AnharmonicOscillator ao(lambda, n);
		vector<vector<double> > hmat;
		ao.calc_h(hmat); 

		vector<double> evals;
		vector<vector<double> > evecs;

		diag_symm(hmat,evecs,evals);

		fout << n << "    "<<evals[level]<<endl;
	}
	
	return 0;
}
