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
