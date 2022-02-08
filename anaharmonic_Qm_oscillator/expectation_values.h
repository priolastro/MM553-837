#ifndef __expectation_values__
#define __expectation_values__

using namespace std;



void calc_expectation_value_x(int N, vector<double>& coeffs, double& expectation_x, double& expectation_x_square){
		typedef vector<vector<double> > MatType;        
        MatType x;
		MatType x_square;
		x.resize(N);
		x_square.resize(N);

		for (int i = 0; i<N; i++){ 	
			x[i].resize(N);
			x_square[i].resize(N);
			}

		//calcola la matrice x 
		for (int i = 0; i<N; i++){
			for (int j = 0 ; j<N; j++) {
				if (abs(i-j)==1){
					x[i][j]=0.5*sqrt((double)(i+j+1));
				}
				else {						
					x[i][j]=0.0;
				}
			}
		}

		//calcola la matrice x^2
		for (int i = 0; i<N; i++) {
			for (int j = 0; j<N; j++){
				for (int k = 0; k<N; k++){
					x_square[i][j] += x[i][k]*x[k][j];
				}
			}
		}
        // calcola expectation value as eq.9.28 Anagnostopoulos
		for (int i=0; i<N-1; i++){
			for (int j=0; j<N-1; j++){
				expectation_x_square += x_square[i][j]*coeffs[i]*coeffs[j];
                expectation_x += x[i][j]*coeffs[i]*coeffs[j];
			}
		}
	}

void calc_expectation_value_p(int N, vector<double>& coeffs, double& expectation_p, double& expectation_p_square){
    typedef vector<vector<double> > MatType;        
    typedef complex<double> dcomp;

        MatType p;
		MatType p_square;
        dcomp im=sqrt(-1);
		p.resize(N);
		p_square.resize(N);

		for (int i = 0; i<N; i++){ 	
			p[i].resize(N);
			p_square[i].resize(N);
		}
		//calcola la matrice p
		for (int i = 0; i<N; i++){
			for (int j = 0 ; j<N; j++) {
                if (i==j+1){
                    p[i][j] +=  (-1/sqrt(2))*sqrt(j+1);
	                    }
                else if (i==j-1){
                    p[i][j] += (1/sqrt(2))*sqrt(j);
                	}
                else {
                    p[i][j] = 0;
                }
            }
        }
        //calcola la matrice p^2
        for (int i = 0; i<N; i++) {
			for (int j = 0; j<N; j++){
				for (int k = 0; k<N; k++){
					p_square[i][j] += p[i][k]*p[k][j];
				}
			}
		}
        // calcola expectation value as eq.9.28 Anagnostopoulos
		// Il segno sbagliato probabilmente dovuto alla mancanza del unita immaginaria i nel calcolo della matrice p e' corretto usando il segno meno nel calcolo che segue
		for (int i=0; i<N-1; i++){
			for (int j=0; j<N-1; j++){
				expectation_p_square += -p_square[i][j]*coeffs[i]*coeffs[j];
                expectation_p += -p[i][j]*coeffs[i]*coeffs[j];
			}
		}
}
#endif 