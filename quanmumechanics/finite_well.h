#ifndef __finite_well__
#define __finite_well__

#include "wave_function.h"
#include <vector>

class FiniteWell {

	typedef std::vector<std::vector<double> > MatType;

	double a, v0; 
	int N, npoint;
	WaveFunction wf;

	void calc_x(MatType& x) {
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

	double simpsons_rule(const std::vector<double>& f) { 
		double epsilon = a/(double)(f.size()-1);
		double ret=0;
		for (int i = 0 ; i<f.size(); i++) { 
			if ((i==0)||(i==(f.size()-1)))
				ret+=f[i];
			else if ((i%2)==0)
				ret+=2.0*f[i];
			else 
				ret+=4.0*f[i];
		}

		ret *= epsilon/3.0;

		return ret;
	}

	void calc_v(MatType& v) { 
		v.resize(N);
		for (int i = 0; i<N; i++)  
			v[i].resize(N);
		
		std::vector<std::vector<double> > bfuncs;
		double epsilon=a/(double)(npoint-1);
		double x=0;
		for(int n=0; n<npoint; n++) {
			std::vector<double> tmp;
			wf.basis_funcs(tmp,x);
			bfuncs.push_back(tmp);
			x += epsilon;
		}

		for (int i = 0; i<N; i++) 
			for (int j = i ; j<N; j++) {
				if (((j-i)%2)==0) {
					std::vector<double> f; 
					for (int n=0; n<npoint; n++) 
						f.push_back(bfuncs[n][i]*bfuncs[n][j]);
					
					v[i][j]=-2.0*v0*simpsons_rule(f);
				} else 
					v[i][j]=0.0;
				
				v[j][i]=v[i][j];	
			}
	}

	public: 
		FiniteWell(const double& _a, const double& _v0, int _N, int _npoint) : a(_a),
		v0(_v0), N(_N), npoint(_npoint), wf(std::vector<double>(_N,0.0)) {}
		
		void calc_h(MatType& hmat) {
		
			MatType xmat,vmat;
			calc_x(xmat);
			calc_v(vmat);

			hmat.resize(N);
			for (int i = 0 ; i<N ; i++)  
				hmat[i].resize(N);

			for (int i = 0 ; i<N ; i++)  
				for (int j = i ; j<N ; j++) {
					hmat[i][j]=0.0;	
					for (int k=0; k<N; k++) 
						hmat[i][j] += xmat[i][k]*xmat[k][j];			
					
					hmat[i][j] *= -0.5;
					hmat[i][j] += vmat[i][j];	
					
					if (j==i)
						hmat[i][j]+=0.5 + j;
					else  
						hmat[j][i]=hmat[i][j];
				
				}
			}

};

#endif 
