#include <iostream>
#include <iomanip>
#include <fstream>
#include "diag_utils.h"
#include "finite_well.h"
#include "wave_function.h"

using namespace std;


int main(int argc, char** argv) {

	if (argc != 6) {
		cerr << "usage: " << argv[0] <<"<a> <v0> <nmin> <nmax> <level>" << endl;
		return 1;
	}

	double a,v0;
	int nmin; 
	int nmax;
	int level; 

	double xmin = -5;
	double xmax = 5;
	int nx=1e3;
	int npoint=1e4;

	stringstream(argv[1]) >> a; 
	stringstream(argv[2]) >> v0; 
	stringstream(argv[3]) >> nmin; 
	stringstream(argv[4]) >> nmax;
	stringstream(argv[5]) >> level;

	ofstream fout("energy.dat");
	fout<<setprecision(16);
	vector<double> coeffs; 

	for (int n = nmin ; n<=nmax ; n++) {
		FiniteWell fw(a, v0, n, npoint);
		vector<vector<double> > hmat;
		
		fw.calc_h(hmat); 
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

	
	return 0;
}
