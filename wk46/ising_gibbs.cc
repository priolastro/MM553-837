/****************************************************************************
 * ising_gibbs.cc
 * **************************************************************************/

#include<iostream>
#include<random>
#include<time.h>
#include<sstream>
#include<cmath>

using namespace std;

int main(int argc, char** argv) {

	if (argc != 6) {
		cerr << "usage: " << argv[0] <<" <L> <j> <ntherm> <nstep> <nmeas> " << endl;
		exit(1);
	}

	int L ;         stringstream(argv[1]) >> L;
	double kappa;   stringstream(argv[2]) >> kappa;      // J/kT 
	int ntherm; stringstream(argv[3]) >> ntherm;  //Number of thermalization steps
	int nstep;  stringstream(argv[4]) >> nstep;  //The number of steps 
	int nmeas;  stringstream(argv[5]) >> nmeas;  //Freq. of measurement 
	
	//--------------------------------------------------------------------------

	mt19937 gen(time(NULL));
	uniform_real_distribution<double> adist(0,1); 
  
	vector<vector<int> > sigma(L,vector<int>(L,1));
	double acc=0.0;

	// cout << nstep/nmeas << " 1 0 0 1" << endl;

	for (int t=0;t<(ntherm+nstep);t++) {

		for (int i=0; i<L ; i++)  
			for (int j=0; j<L ; j++) {
	
				//First correctly handle the boundaries
				double im1; 
				if (i==0) 
					im1=sigma[L-1][j];
				else
					im1=sigma[i-1][j]; 

				double ip1; 
				if (i==(L-1)) 
					ip1=sigma[0][j];
				else
					ip1=sigma[i+1][j]; 

				double jm1; 
				if (j==0) 
					jm1=sigma[i][L-1];
				else
					jm1=sigma[i][j-1]; 

				double jp1; 
				if (j==(L-1)) 
					jp1=sigma[i][0];
				else
					jp1=sigma[i][j+1];

				//Now the sign of the proposed spin flip
				double flip; 
				if (sigma[i][j] == 1)
					flip=2.0;
				else
					flip=-2.0; 

				//Sum over the nearest nieghbors
				double nn = ip1+im1+jp1+jm1;

				//Calculate the probability of a change 
				double p = 1.0/(1.0 + exp(kappa*flip*nn));	


		 if (adist(gen) < p) {
				sigma[i][j] *= -1; 
				acc++;
		}

	}

		if ((t>=ntherm)&&(((t-ntherm) % nmeas)==0)) {
			double m = 0.0; 
			for (int i = 0 ; i < L ; i++)
				for (int j = 0 ; j < L ; j++) {
					m+=double(sigma[i][j]);
				}
			m /= (double(L)*double(L));
			cout << abs(m) << endl;
		}
	
	}

	cerr << "acc = "<<acc/(L*L*(nstep+ntherm))<<endl;

	return 0;

}
