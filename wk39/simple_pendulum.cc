/****************************************************************************
 * int_test.cc
 * Compares integrators for a single simple pendulum 
 * oscillator: naiveEuler, EulerCromer and Leapfrog.
 * **************************************************************************/
#include<iostream>
#include<sstream>
#include<cmath>

const double g=9.807;

#include "Integrators.h"
#ifndef __integrators__
#define __integrators__

using namespace std;

int main(int argc, char** argv) {
	double tau; 
	stringstream(argv[1]) >> tau;  //The length of the traj. 
	int niter; 
	stringstream(argv[2]) >> niter;  //The number of steps in a traj. 
	int nmeas; 
	stringstream(argv[3]) >> nmeas;  //The number of steps in a traj. 
	

	double q0=M_PI/4, p0=0; 
	double eps=tau/double(niter);

	double qn=q0, pn=p0;

	Leapfrog LE(eps);
	LE.setInitialConditions(qn, pn);

	for (int t=0; t<niter; t++){
		cout << qn << " " << pn <<endl;
		LE(qn, pn);
		}	
return 0;
}

#endif