#ifndef __wave_function__
#define __wave_function__

#include <cmath>
#define _USE_MATH_DEFINES 

using namespace std;

class WaveFunction {
    int nmax;
	const vector<double>& coeffs;
	vector<double> norms;

    double hermite(int n, const double& x) const {
        if (n == 0)
            return 1;
        else if (n==1)
            return 2.0 * x;
        return 2.0 * x * hermite(n-1,x) - 2.0 * (double)(n) * hermite(n-2,x);
    } 

    public:
        WaveFunction(const vector<double>& _coeffs) : coeffs(_coeffs), nmax(_coeffs.size()-1) {
            norms.clear();
            const double pi_to_minus_one_fourth = pow(M_PI,-((double)1/(double)4));
            norms.push_back(pi_to_minus_one_fourth);
            for (int n = 1; n <= nmax; n++){
                // computing phi_n=1/sqrt(2^n*n!*\sqrt(pi))
                norms.push_back(norms[n-1]/sqrt(2.0*n));
            }
        }
        double operator() (const double& x) const {
            double eigen;
            for (int n = 0; n <= nmax; ++n) {
                eigen += coeffs[n] * norms[n] * hermite(n,x);
            }
            eigen *= exp(-0.5*pow(x,2));
            return eigen;
        }
};

#endif