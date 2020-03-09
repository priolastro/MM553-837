#ifndef __integrators_h__
#define __integrators_h__

#include<vector>
using namespace std;

template<class Forces, class Constraints>
class Leapfrog{
	double epsilon;
	const Forces& F;
    const Constraints& C;
 	vector<double> qn;
	vector<double> pn;
	
    public:
		Leapfrog(const Forces& Fin, const Constraints& Cin, const double& ein):F(Fin), C(Cin), epsilon(ein){}
			
            void setInitialConditions(const vector<double>& q0, const vector<double>& p0) {
                int ndof=F.getNDof();
                qn=q0;
				pn=p0;
                C(qn,pn);
            }
			void operator() (vector<double>& qnp1, vector<double>& pnp1){
				int ndof=F.getNDof();
                qnp1.resize(ndof);
                pnp1.resize(ndof);
                vector<double> pnp12(ndof);
                
                for (int i=0; i<ndof;i++){
                    pnp12[i]=pn[i]+0.5*epsilon*F(i, qn);
				    qnp1[i]=qn[i]+epsilon*pnp12[i];
                }
				for (int i=0; i<ndof;i++){
                pnp1[i]=pnp12[i]+0.5*epsilon*F(i,qnp1);
                }

                C(qnp1, pnp1);
				qn=qnp1;
				pn=pnp1;
			}
};
#endif