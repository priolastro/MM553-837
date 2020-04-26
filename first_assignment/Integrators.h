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

template<class Forces>
class RK2{
        double epsilon;
        const Forces& F;
        vector<double> qn;
        vector<double> pn;
        public:
            RK2(const Forces& Fin, const double& ein):F(Fin), epsilon(ein){}
            void setInitialCondition(const vector<double>& q0, const vector<double>& p0) {
                qn=q0,pn=p0;
            }
            void operator() (vector<double>& qnp1, vector<double>& pnp1){
                int ndof=F.GetDofF(qn);
                qnp1.resize(ndof);
                pnp1.resize(ndof);
                vector<double> temp(ndof);

                for (int i=0; i<ndof; i++){
                    qnp1[i]=qn[i]+epsilon*(pn[i]+0.5*epsilon*F(i,qn));
                    temp[i]=qn[i]+0.5*epsilon*pn[i];
                }
                for (int i=0; i<ndof; i++){
                    pnp1[i]=pn[i]+epsilon*F(i,temp);
                }
                qn=qnp1, pn=pnp1;
            }
};

template<class Forces>
class RK4{
        double epsilon;
        const Forces& F;
        vector<double> qn;
        vector<double> pn;
        public:
            RK4(const Forces& Fin, const double& ein):F(Fin), epsilon(ein){}
            void setInitialCondition(const vector<double>& q0, const vector<double>& p0) {
                qn=q0; pn=p0;
            }
            void operator() (vector<double>& qnp1, vector<double>& pnp1) {
                int ndof = F.GetDofF(qn);
                qnp1.resize(ndof); 
                pnp1.resize(ndof);
                vector<double>& k1q=pn;
                vector<double> k2q(ndof),k3q(ndof),k4q(ndof);
                vector<double> k1p(ndof),k2p(ndof),k3p(ndof),k4p(ndof),temp(ndof);
                
                for (int i = 0 ; i<ndof ; i++) {
                        k1p[i] = F(i,qn);
                        k2q[i] = pn[i]+0.5*epsilon*k1p[i];
                        temp[i] = qn[i] + 0.5*epsilon*k1q[i];
                }
                for (int i = 0 ; i<ndof ; i++) {
                        k2p[i] = F(i, temp);
                        k3q[i] = pn[i]+0.5*epsilon*k2p[i];
                }
                for (int i = 0 ; i<ndof ; i++){
                        temp[i] = qn[i] + 0.5*epsilon*k2q[i];
                }
                for (int i = 0 ; i<ndof ; i++) {
                        k3p[i] = F(i,temp);
                        k4q[i] = pn[i] + epsilon*k3p[i];
                }
                for (int i = 0 ; i<ndof ; i++){
                        temp[i] = qn[i] + epsilon*k3q[i];
                }

                for (int i = 0 ; i<ndof ; i++){
                        k4p[i] = F(i,temp);
                }
                for (int i=0; i<ndof; i++) {
                        pnp1[i] = pn[i] + epsilon/6.0*(k1p[i] + 2.0*k2p[i] + 2.0*k3p[i] + k4p[i]);
                        qnp1[i] = qn[i] + epsilon/6.0*(k1q[i] + 2.0*k2q[i] + 2.0*k3q[i] + k4q[i]);
                }
                qn=qnp1; pn=pnp1;
        }
};