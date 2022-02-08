#ifndef __finite_well__
#define __finite_well__

#include "wave_function.h"
#include <vector>

class FiniteWell {

	typedef vector<vector<double> > MatType;

	double a, b, v0, v1; 
	int N, npoint;
	WaveFunction wf;

	void calc_x(MatType& x) {
		//matrice x che rappresenta il potenziale
		x.resize(N);
		for (int i = 0; i<N; i++) 
			x[i].resize(N);

		for (int i = 0; i<N; i++) 
			for (int j = 0 ; j<N; j++) {
				if (abs(i-j)==1) 
					x[i][j]=0.5*sqrt((double)(i+j+1));
				else 
					x[i][j]=0.0;
			}
	}

	double simpsons_rule(const std::vector<double>& f, double point) { 
		double epsilon = point/(double)(f.size()-1);
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
	
	void calc_v(MatType& v, double point, double potential) { 
		v.resize(N);
		for (int i = 0; i<N; i++)  
			v[i].resize(N);
		MatType bfuncs; //basis functions 
		double epsilon=point/(npoint-1);  // viene diviso per il numero di rettangoli che e' numero di punti-1
		double x=0;
		for(int n=0; n<npoint; n++) {
			vector<double> tmp;
			wf.basis_funcs(tmp,x);
			bfuncs.push_back(tmp);
			x += epsilon;
		}
		for (int i = 0; i<N; i++) 
			for (int j = i ; j<N; j++) {
				// here comparing the parity, if j and i are next to each other or if they differ by an odd number then they have opposite parity and the matirix element is zero 
				if (((j-i)%2)==0) {  
					vector<double> f; 
					for (int n=0; n<npoint; n++) 
						f.push_back(bfuncs[n][i]*bfuncs[n][j]); // multiplication of two basis function
					v[i][j]=-2.0*potential*simpsons_rule(f, point); // final result
				} else 
					v[i][j]=0.0;
				
				v[j][i]=v[i][j];	// the matrix is symmetric so you just do it for j<i
			}
	}

	


	public: 
		FiniteWell(const double& _a, const double& _b, const double& _v0, const double& _v1, int _N, double _npoint) : a(_a), b(_b), v0(_v0), v1(_v1), N(_N), npoint(_npoint), wf(vector<double>(_N,0.0)) {}	

		void calc_h(MatType& hmat) {
			//calcola H per il finite well come Hsho-1/2xnmxnm-V0integral
			MatType xmat, vmat_b, vmat_a, vmat_TOT;
			calc_x(xmat);
			calc_v(vmat_b, b, v0);
			calc_v(vmat_a, a, v1);
			hmat.resize(N);
			vmat_TOT.resize(N);
			for (int i=0; i<N; i++){
				vmat_TOT[i].resize(N);
			}
			for (int i=0; i<N; i++){
				for (int j=0; j<N; j++){
					vmat_TOT[i][j]=vmat_a[i][j]+vmat_b[i][j];
				}
			}
			for (int i = 0 ; i<N ; i++)  
				hmat[i].resize(N);
			for (int i = 0 ; i<N ; i++)  
				for (int j = i ; j<N ; j++) {
					hmat[i][j]=0.0;	
					for (int k=0; k<N; k++)  
						//qui calcola x_nm*x_nm
						hmat[i][j] += xmat[i][k]*xmat[k][j];			
					//qui moltiplica x_nm*x_nm per -1/2
					hmat[i][j] *= -0.5;
					//qui aggiunge il termine dovuto al potenziale
					hmat[i][j] += vmat_TOT[i][j];
					//questo aggiunge a tutti gli elementi diagonali n+1/2 dovuto all Hamiltoniano sho 
					if (j==i)
						hmat[i][j] += 0.5 + j;
					//visto che la matrice e simmetrica e sto calcolando con j<N metto gli elementi ij=ji
					else  
						hmat[j][i] = hmat[i][j];
				
				}
			}

};

#endif 
