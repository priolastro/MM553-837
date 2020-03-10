/**********************
Spring system 
***********************/

#include<vector>
using namespace std;

class SpringSystem{
    //system defined starting from the degrees of freedom vector
    vector<double> q;
public:
    SpringSystem(const vector<double>& qn): q(qn) {}
    //number of degrees of freedom 
    int getNDof(const vector<double>& q) const {
        int dof=q.size();
        return dof;
    }
    //operator to calculate forces 
    double operator ()(int i, vector<double>& q) const{
        double f1, f2, force;
        f1=(q[i]-q[i+1]);
        f2=(q[i-1]-q[i]);
        force=((f1)-(f2))+(pow(f1,2)-pow(f2,2))+(pow(f1,3)-pow(f2,3));
        return force;
    }
};