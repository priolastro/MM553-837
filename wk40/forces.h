#ifndef __Forces__
#define __Forces__

#include<vector>
using namespace std;

class NoForce {
        double k;
        public:
        NoForce(const double& kin): k(kin) {}
        double operator() (const double& r) const {
            return 0.0;
            }
        double pot(const double& r) const {
            return 0.0;
            }
};

class InverseSquareForce {
    double k;
    public:
        InverseSquareForce(const double& kin): k(kin) {}
        
        double operator() (const double& r) const {
            return k/(r*r);
        }
        double pot (const double& r) const {
            return k/r;
        }
};

template <class ForceLaw>
class CentralForce {
    const ForceLaw& f;
    int N;
    public:
        CentralForce (const ForceLaw& fin, int Nin) : f(fin), N(Nin) {}
        int getNDof() const {
            return 2*N;
        }
        double operator() (int i, const vector<double>& q) const {
            int ix=i;
            int iy=i+1;
            if ((i%2)!=0){
                ix=i-1;iy=i;
            };
            double ftot=0.0;
            for (int n=0; n<N; n++){
                if((ix/2)==n){
                    continue;
                    };
                double r=sqrt(pow(q[ix]-q[2*n],2)+pow(q[iy]-q[2*n+1],2));
                if(ix==i){
                    ftot+=(q[i]-q[2*n])*f(r)/r;
                    }
                else
                    ftot+=(q[i]-q[2*n+1])*f(r)/r;
            };
            return ftot;
        }
        double calcPot (const vector<double>& q) {
            double Etot=0.0;
            for (int i=0; i<(q.size()/2);i++){
                for (int j=0;j<i;j++){
                    double r=sqrt(pow(q[2*i]-q[2*j],2)+pow(q[2*i+1]-q[2*j+1],2));
                    Etot+=f.pot(r);
                }
            }
            return Etot;
            }
        
        double calcKin (const vector<double>& p){
            double Etot=0.0;
            for (int i=0; i<p.size();++i){
                Etot+=0.5*pow(p[i],2);
        }
        return Etot;
        }
};
#endif