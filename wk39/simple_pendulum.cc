/****************************************************************************
 * Compares integrators for a single simple pendulum 
 * oscillator: naiveEuler, EulerCromer and Leapfrog.
 * **************************************************************************/
#include<iostream>
#include<sstream>
#include<cmath>
#include<fstream>

const double g=9.807;

#include "Integrators.h"
#ifndef __integrators__
#define __integrators__
#include "systems.h"
#ifndef __systems__
#define __systems__


using namespace std;


int main(int argc, char** argv) {
	if (argc !=3){
		cerr << "usage: " << argv[0] << " <t> <niter> \n";
	}

	double tau; 
	stringstream(argv[1]) >> tau;  //The length of the traj. 
	int niter; 
	stringstream(argv[2]) >> niter;  //The number of steps in a traj.  
	
	double q0=M_PI/4, p0=0; 
	double eps=tau/double(niter);


	double qn_le=q0, pn_le=p0;


	Pendulum dp(1,1,1.5);	
	Leapfrog<Pendulum> LE(dp, eps);

	LE.setInitialConditions(qn_le, pn_le);
	
	
	for (int t=0; t<niter; t++){
		cout << qn_le << " " << pn_le << endl;
		LE(qn_le, pn_le);
		}	
return 0;
}

#endif
#endif
