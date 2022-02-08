/**********************
Different integrators to apply to one dimensional systems.
Can handle both simple and damped sistems. 
Contains also Leapfrog_damped to treat DampedPendulum.
***********************/

template<class Forces>
class NaiveEuler{
	double epsilon;
	const Forces& F;
	double qn;
	double pn;
	public:
			NaiveEuler(const Forces& Fin, const double& ein):F(Fin), epsilon(ein){}
			void setInitialConditions(const double& q0, const double& p0) {
				qn=q0;
				pn=p0;
			}
			void operator() (double& qnp1, double& pnp1){
				qnp1=qn+epsilon*pn;
				pnp1=pn+epsilon*F(qn,pn);
				
				qn=qnp1;
				pn=pnp1;
			}
};

template<class Forces>
class EulerCromer{
	double epsilon;
	const Forces& F;
	double qn;
	double pn;
	public:
		EulerCromer(const Forces& Fin, const double& ein):F(Fin), epsilon(ein){}
			void setInitialConditions(const double& q0, const double& p0) {
				qn=q0;
				pn=p0;
			}
			void operator() (double& qnp1, double& pnp1){
				qnp1=qn+epsilon*pn;
				pnp1=pn+epsilon*F(qnp1, pnp1);

				qn=qnp1;
				pn=pnp1;
			}
};

template<class Forces>
class Leapfrog{
	double epsilon;
	const Forces& F;
 	double qn;
	double pn;
	public:
		Leapfrog(const Forces& Fin, const double& ein):F(Fin), epsilon(ein){}
			void setInitialConditions(const double& q0, const double& p0) {
				qn=q0;
				pn=p0;
			}
			void operator() (double& qnp1, double& pnp1){
				 double pnp12=pn+0.5*epsilon*F(qn,pn);
				 qnp1=qn+epsilon*pnp12;
				 pnp1=pnp12+0.5*epsilon*F(qnp1, pnp12);

				qn=qnp1;
				pn=pnp1;
			}
};

template<class Forces>
class RK2{
	double epsilon;
	const Forces& F;
 	double qn;
	double pn;
	public:
		RK2(const Forces& Fin, const double& ein):F(Fin), epsilon(ein){}
			void setInitialConditions(const double& q0, const double& p0) {
				qn=q0;
				pn=p0;
			}
			void operator() (double& qnp1, double& pnp1){
				qnp1=qn+epsilon*(pn+0.5*epsilon*F(qn,pn));
				double temp=qn+0.5*epsilon*pn;
				pnp1=pn+epsilon*F(temp, pn);

				qn=qnp1;
				pn=pnp1;
			}
};

template<class Forces>
class RK4{
	double epsilon;
	const Forces& F;
 	double qn;
	double pn;
	public:
		RK4(const Forces& Fin, const double& ein):F(Fin), epsilon(ein){}
			void setInitialConditions(const double& q0, const double& p0) {
				qn=q0;
				pn=p0;
			}
			void operator() (double& qnp1, double& pnp1){
				const double k1q=pn;
				double k2q, k3q, k4q;
				double k1p,k2p,k3p,k4p,temp;

				k1p=F(qn,pn);
				k2q=pn+0.5*epsilon*k1p;
				temp=qn+0.5*epsilon*k1q;
				k2p=F(temp, k1p);
				k3q=pn+0.5*epsilon*k2p;
				temp=qn+0.5*epsilon*k2q;
				k3p=F(temp,k3p);
				k4q=pn+epsilon*k3p;
				temp=qn+epsilon*k3q;
				k4p=F(temp, k3p);
				pnp1=pn+epsilon/6*(k1p+2*k2p+2*k3p+k4p);
				qnp1=qn+epsilon/6*(k1q+2*k2q+2*k3q+k4q);

				qn=qnp1;
				pn=pnp1;
			}
};