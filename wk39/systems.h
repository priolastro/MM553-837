/* ******************************************
 * Simple and damped pendulum force class. 
 * Use gamma=0 for simple pendulum
 * and gamma!=0 for damped pendulum.
 * ******************************************/


class Pendulum{
	double m, k, gamma;

	public:
		Pendulum (const double& m_in, const double& k_in, const double& gamma_in):m(m_in), k(k_in), gamma(gamma_in) {}
		
		double operator() ( const double& q, const double& p) const {
			double F=-g*sin(q)-gamma*p;
			return F;
		}
};