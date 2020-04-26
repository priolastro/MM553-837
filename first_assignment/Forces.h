/*
System of springs for Fermi–Pasta–Ulam–Tsingou problem
*/

class SpringsSystem{
    double m,k;
    public:
        SpringsSystem(const double& m_in, const double& k_in):m(m_in), k(k_in) {}

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

class SpringsSystem_hcq{
    double m, k, alpha, beta;
    public:
        SpringsSystem_hcq(const double& m_in, const double& k_in, const double& alpha_in, const double& beta_in):m(m_in), k(k_in), alpha(alpha_in), beta(beta_in) {}
        
        int GetDofF(vector<double>& q) const{
            double DofF=q.size();
            return DofF;
        };

        double operator() (int i, const vector<double>& q) const {
            int DofF=q.size();
            double F;
            if (DofF==1){
                if (i==0){
                    F=-2*q[i]-2*alpha*pow(q[i],2)-2*beta*pow(q[i],3);
                }
            }
            else if (DofF==2) {
                if (i==0){
                    F=-2*q[i]+q[i+1]-alpha*pow(q[i]-q[i+1],2)-alpha*pow(q[i],2)-beta*pow(q[i]-q[i+1],3)-beta*pow(q[i],3);
                }
                else {
                    F=-2*q[i]+q[i-1]+alpha*pow(q[i]-q[i-1],2)-alpha*pow(q[i],2)+beta*pow(q[i]-q[i-1],3)-beta*pow(q[i],3);
                }
            }
            else if (DofF>=3){
                if (i==0){
                    F=-2*q[i]+q[i+1]-alpha*pow(q[i]-q[i+1],2)-alpha*pow(q[i],2)-beta*pow(q[i]-q[i+1],3)-beta*pow(q[i],3);
                }
                else if (i==DofF-1){
                    F=-2*q[i]+q[i-1]+alpha*pow(q[i]-q[i+1],2)-alpha*pow(q[i],2)+beta*pow(q[i]-q[i+1],3)-beta*pow(q[i],3);
                }
                else{
                    F=-2*q[i]+q[i-1]+q[i+1]+alpha*pow(q[i-1]-q[i],2)-alpha*pow(q[i]-q[i+1],2)+beta*pow(q[i-1]-q[i],3)-beta*pow(q[i]-q[i+1],3);
                }
            }
        return F;
        }
};