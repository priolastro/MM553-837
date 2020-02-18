/*
Class of integrators
*/


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
