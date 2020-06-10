#ifndef __anharmonic_oscillator__
#define __anharmonic_oscillator__


class AnharmonicOscillator {

	typedef std::vector<std::vector<double> > MatType;

	double lambda; 
	int N;

	void calc_x(MatType& x) {
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


	public: 
		AnharmonicOscillator(const double& _lambda, int _N) : lambda(_lambda),
	N(_N) {}

		
		void calc_h(MatType& hmat) {
		
			MatType xmat; 
			calc_x(xmat);

			hmat.resize(N);
			for (int i = 0 ; i<N ; i++)  
				hmat[i].resize(N);

			//To compute potential as lambda*x^4 
			for (int i = 0 ; i<N ; i++)  
				for (int j = i ; j<N ; j++) {
					hmat[i][j]=0.0;	
					for (int k=0; k<N; k++) 
						for (int l=0; l<N; l++) 
							for (int m=0; m<N; m++)  
								hmat[i][j] += xmat[i][k]*xmat[k][l]*xmat[l][m]*xmat[m][j];			
					
					hmat[i][j] *= lambda;	
					
					// This adds to all diagonal elements n+1/2
					if (j==i)

						hmat[i][j]+=0.5 + j;
					else 
						hmat[j][i]=hmat[i][j];
				
				}
			}
};

#endif 
