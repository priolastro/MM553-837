/****************************************************************************
 * int_test.cc
 * Compares integrators for a single simple pendulum 
 * oscillator: naiveEuler, EulerCromer and Leapfrog.
 * **************************************************************************/
#include<iostream>
#include<sstream>
#include<cmath>
using namespace std;
const double g=9.807;

class NaiveEuler{
	double epsilon;
	double qn;
	double pn;
	public:
			NaiveEuler(const double& ein):epsilon(ein){}
			void setInitialConditions(const double& q0, const double& p0) {
				qn=q0;
				pn=p0;
			}
			void operator() (double& qnp1, double& pnp1){
				qnp1=qn+epsilon*pn;
				pnp1=pn-epsilon*g*sin(qn);
				
				qn=qnp1;
				pn=pnp1;
			}
};

class EulerCromer{
	double epsilon;
	double qn;
	double pn;
	public:
		EulerCromer(const double& ein):epsilon(ein){}
			void setInitialConditions(const double& q0, const double& p0) {
				qn=q0;
				pn=p0;
			}
			void operator() (double& qnp1, double& pnp1){
				qnp1=qn+epsilon*pn;
				pnp1=pn-epsilon*g*sin(qnp1);

				qn=qnp1;
				pn=pnp1;
			}
};

class Leapfrog{
	double epsilon;
 	double qn;
	double pn;
	public:
		Leapfrog(const double& ein):epsilon(ein){}
			void setInitialConditions(const double& q0, const double& p0) {
				qn=q0;
				pn=p0;
			}
			void operator() (double& qnp1, double& pnp1){
				 double pnp12=pn-0.5*epsilon*g*sin(qn);
				 qnp1=qn+epsilon*pnp12;
				 pnp1=pnp12-0.5*epsilon*g*sin(qnp1);

				qn=qnp1;
				pn=pnp1;
			}
};


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
		
		// double qnp1=qn+eps*pn;
		// double pnp1=pn-eps*9.8*sin(qnp1);
		// qn=qnp1;
		// pn=pnp1;
		}	
return 0;
}
