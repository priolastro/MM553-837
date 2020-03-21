/*************************
 * Spring 
 * ***********************/

#include<iostream>
#include<sstream>
#include<vector>
#include<cmath>
#include<fstream>
#include<random>
#include<chrono>
#include<math.h>

#define _USE_MATH_DEFINES
using namespace std;
using namespace std::chrono;

class TwoSpringsOneMasses{
    double m,k,gamma;
    public:
        TwoSpringsOneMasses(const double& m_in, const double& k_in, const double& gamma_in):m(m_in), k(k_in), gamma(gamma_in) {}

        double operator() (const double& q) const {
            double F=-2*q*k;
            return F;
        } 
};

class ThreeSpringsTwoMasses{
    double m,k,gamma;
    public:
        ThreeSpringsTwoMasses(const double& m_in, const double& k_in):m(m_in), k(k_in) {}

        int GetDofF(vector<double>& q) const{
            double DofF=q.size();
            return DofF;
        };

        double operator() (int i, const vector<double>& q) const {
            int DofF=q.size();
            double F;
            if (DofF==1){ 
                F=-2*q[i];
            }
            else if (DofF==2){
                if (i==0){
                    F=-2*q[i]+q[i+1];
                }
                else {
                    F=-2*q[i]+q[i-1];
                }
            }
            else if (DofF>=3){
                if (i==0){
                    F=-2*q[i]+q[i+1];
                }
                else if (i==DofF-1) {
                    F=-2*q[i]+q[i-1];
                }
                else{
                    F=-2*q[i]+q[i-1]+q[i+1];
                }
            }
            return F;
        } 
};

template<class Force>
class Leapfrog{
    double epsilon;
    const Force& F;
    vector<double> qn;
    vector<double> pn;
    public:
        Leapfrog(const Force& F_in, const double& e_in): F(F_in), epsilon(e_in){}

        void setInitialCondition(const vector<double>& q0, const vector<double>& p0) {
            qn=q0, pn=p0;
        }
        void operator() (vector<double>& qnp1, vector<double>& pnp1){
            int ndof=F.GetDofF(qn);
            qnp1.resize(ndof);
            pnp1.resize(ndof);
            vector<double> pnp12(ndof);
            
            for (int i=0; i<ndof; i++){
                pnp12[i]=pn[i]+0.5*epsilon*F(i, qn);
                qnp1[i]=qn[i]+epsilon*pnp12[i];
            }
            for (int i=0; i<ndof; i++){
                pnp1[i]=pnp12[i]+0.5*epsilon*F(i,qnp1);
            }
            qn=qnp1, pn=pnp1;
            }
};

int main(int argc, char** argv) {
    double tau;
    stringstream(argv[1]) >> tau;
    int niter;
    stringstream(argv[2]) >> niter;
    int npart;
    stringstream(argv[3]) >> npart;

    double eps=tau/double(niter);

    ofstream dati("dati.out");

    vector<double> qn(npart),pn(npart);
    for (int n = 0; n < npart; n++) {
        pn[n] = sin((2*M_PI * (n+0.2) / npart));
        qn[n] = 0;
    };

    ThreeSpringsTwoMasses ss(1,1);
    Leapfrog<ThreeSpringsTwoMasses> integrator(ss, eps);

    integrator.setInitialCondition(qn,pn);

    for (int t=0; t<niter; t++){
        for (int i=0; i<qn.size();++i){
            dati << qn[i] << " " << pn[i] << endl;
        }
        integrator(qn,pn);
    };
return 1;
}