#ifndef __wave_function__
#define __wave_function__

//---------------------------------------------------------------

class WaveFunction {

	typedef std::vector<std::vector<double> > MatType;
	
	int N;
	const std::vector<double>& coeffs;
	std::vector<double> norms; 

	void calc_x(MatType& x) const {
		x.resize(N);
		for (int i = 0; i<N; i++) 
			x[i].resize(N);

		for (int i = 0; i<N; i++) 
			for (int j = i ; j<N; j++) {
				if (abs(i-j)==1) 
					x[i][j]=0.5*sqrt((double)(i+j+1));
				else 
					x[i][j]=0.0;

				x[j][i] = x[i][j];
			}
	}

public: 
	WaveFunction(const std::vector<double>& _coeffs) : coeffs(_coeffs), N(_coeffs.size()) {
		norms.clear();
		const double pi_to_minus_one_fourth=0.75112554446;
		norms.push_back(pi_to_minus_one_fourth);

		for (int n = 1; n < N; n++)
			norms.push_back(norms[n-1] / sqrt(2.0*n));
	} 

	double operator() (const double& x) const {
		double h_nm2=1;
		double h_nm1=2*x; 
		double ret=coeffs[0]*norms[0]*h_nm2;
		if (N>1) 
			ret+=coeffs[1]*norms[1]*h_nm1;

		for (int n = 2; n<N; ++n) {
			double h_n = 2.0*x*h_nm1 - 2.0*(double)(n-1)*h_nm2;
			ret+= coeffs[n]*norms[n]*h_n;
			h_nm2=h_nm1;
			h_nm1=h_n; 
		}
		ret *= exp(-0.5*x*x);
		return ret;
	}

	double average_xsq() const { 
		double ret=0.0;
		MatType xmat; calc_x(xmat);

		for (int i=0; i<N; i++)
			for (int j=0; j<N; j++)
				for (int k=0; k<N; k++)
				ret += coeffs[i]*coeffs[j]*xmat[i][k]*xmat[k][j];

		return ret;
	}

	void basis_funcs(std::vector<double>& vec, const double&x) const { 
		double h_nm2=1;
		double h_nm1=2*x; 
		vec.clear();	
		vec.push_back(exp(-0.5*x*x)*norms[0]*h_nm2);
		if (N>1) 
			vec.push_back(exp(-0.5*x*x)*norms[1]*h_nm1);

		for (int n = 2; n<N; ++n) {
			double h_n = 2.0*x*h_nm1 - 2.0*(double)(n-1)*h_nm2;
			vec.push_back(exp(-0.5*x*x)*norms[n]*h_n);
			h_nm2=h_nm1;
			h_nm1=h_n; 
		}
	}

};

#endif 
