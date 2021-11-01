/****************************************************************************
 * ising_metro.cc
 * **************************************************************************/

#include<iostream>
#include<random>
#include<time.h>
#include<sstream>
#include<stdio.h>
#include<vector>

using namespace std;

void Correlation_function(double &value, double ip, double im, double jp, double jm){
	value = ip+im+jp+jm;
}

int main(int argc, char** argv) {

	if (argc != 6) {
		cerr << "usage: " << argv[0] <<" <L> <k> <ntherm> <nstep> <nmeas> " << endl;
		exit(1);
	}

	int L ;         stringstream(argv[1]) >> L;
	double kappa;   stringstream(argv[2]) >> kappa;      // J/kT    
	int ntherm; stringstream(argv[3]) >> ntherm;  //Number of thermalization steps
	int nstep;  stringstream(argv[4]) >> nstep;  //The number of steps 
	int nmeas;  stringstream(argv[5]) >> nmeas;  //Freq. of measurement , how many to skip between measurments
	
	//--------------------------------------------------------------------------

	mt19937 gen(time(NULL));
	uniform_real_distribution<double> adist(0,1); 
	uniform_int_distribution<int> sdist(0,L-1); 
  
	vector<vector<int>> sigma(L,vector<int>(L)); // cold start because all sigmas are equal to one
	double acc=0.0;

	// cout << nstep/nmeas << " 1 0 0 1" << endl;


		//to implement an hot start in the lattice
		for (int ip=0; ip<L ; ip++)  
			for (int jp=0; jp<L ; jp++) {
				int ran = sdist(gen);
				sigma.push_back(ran);
			}

	for (int t=0; t<(ntherm+nstep); t++) {

		for (int ip=0; ip<L ; ip++)  
			for (int jp=0; jp<L ; jp++) {
	
				// int i = sdist(gen);
				// int j = sdist(gen);

				int i = ip; 
				int j = jp;

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
					flip=-2.0;
				else
					flip=2.0; 

				//Sum over the nearest nieghbors
				double nn = ip1+im1+jp1+jm1; //can be max 4 min -4

				


				//Calculate the change in energy
				double p = exp(kappa*flip*nn);	//fliip = -2sigma


		//accettare o no
		 
		if (p > 1) { 
			sigma[i][j] *= -1;
			acc++;
		} else if (adist(gen) < p) {
				sigma[i][j] *= -1; 
				acc++;
		}

	}

		if ((t>=ntherm)&&(((t-ntherm) % nmeas)==0)) {
			double m = 0.0; 
			double G;
			for (int i = 0 ; i < L ; i++)
				for (int j = 0 ; j < L ; j++) {
					m+=double(sigma[i][j]);
					// Correlation_function(G, sigma);
					// cerr << G << endl;
				}
		    m /= (double(L)*double(L));
			cout << abs(m) <<endl;  // I can get |m| by doing the square root.
		}
	
	}

	cerr << "acc = "<<(double)acc/(L*L*(nstep+ntherm))<<endl;
	return 0;

}