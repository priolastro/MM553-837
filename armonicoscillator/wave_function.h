#ifndef __wave_function__
#define __wave_function__

//---------------------------------------------------------------

class WaveFunction {

	int nmax;
	const std::vector<double>& coeffs;
	std::vector<double> norms; 

	double hermite(int n, const double& x) const {
		if (n==0)
			return 1;
		else if (n==1)
			return 2.0*x;

		return 2.0*x*hermite(n-1,x) - 2.0*(double)(n)*hermite(n-2,x);
	}

public: 
	WaveFunction(const std::vector<double>& _coeffs) : coeffs(_coeffs), nmax(_coeffs.size()-1) {
		norms.clear();
		const double pi_to_minus_one_fourth=0.75112554446;
		norms.push_back(pi_to_minus_one_fourth);

		for (int n = 1; n <= nmax; n++)
			norms.push_back(norms[n-1] / sqrt(2.0*n));
	} 

	double operator() (const double& x) const {
		double h_nm2=1;
		double h_nm1=2*x; 
		double ret=coeffs[0]*norms[0]*h_nm2;
		if (nmax>0) 
			ret+=coeffs[1]*norms[1]*h_nm1;

		for (int n = 2; n<=nmax; ++n) {
			double h_n = 2.0*x*h_nm1 - 2.0*(double)(n-1)*h_nm2;
			ret+= coeffs[n]*norms[n]*h_n;
			h_nm2=h_nm1;
			h_nm1=h_n; 
		}
		ret *= exp(-0.5*x*x);
		return ret;
	}

	double basis_funcs(int n, const double&x) const { 
		return norms[n]*exp(-0.5*x*x)*hermite(n,x);
	}
	
	void basis_funcs(std::vector<double>& vec, const double&x) const { 
		double h_nm2=1;
		double h_nm1=2*x; 
		vec.clear();	
		vec.push_back(exp(-0.5*x*x)*norms[0]*h_nm2);
		if (nmax>0) 
			vec.push_back(exp(-0.5*x*x)*norms[1]*h_nm1);

		for (int n = 2; n<=nmax; ++n) {
			double h_n = 2.0*x*h_nm1 - 2.0*(double)(n-1)*h_nm2;
			vec.push_back(exp(-0.5*x*x)*norms[n]*h_n);
			h_nm2=h_nm1;
			h_nm1=h_n; 
		}
	}

};

#endif 
