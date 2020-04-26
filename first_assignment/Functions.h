/*
Functions to calculate kinetic and potential energy 
*/

double Calc_Kinetic(vector<double> p){
    double K;
    for (int i=0; i<p.size(); i++){
        K+=0.5*pow(p[i],2);
    }
    return K;
}

double Calc_LinearMomentum(vector<double> p){
    double P;
    for (int i=0; i<p.size(); i++){
        P+=p[i];
        }
    return P;
}

double Calc_AverageSpeed(vector<double> p){
    double AvV;
    for (int i=0; i<p.size(); i++){
        AvV+=pow(p[i],2);
    }
    return AvV/p.size();
}

double Calc_sqSpeed(vector<double> p){
    double sqV;
    for (int i=0; i<p.size(); i++){
        sqV+=pow(p[i],2);
    }
    return sqV;
}

double Calc_Potential(vector<double> q){
    double V;
    int DofF=q.size();
    if (DofF==1){ 
        for (int i=0; i<DofF; i++){
            V+=pow(q[i],2);
            }        
    }
    else if (DofF==2){
        for (int i=0; i<DofF; i++){
        if (i==0){
            V+=0.5*pow(q[i]-q[i+1],2)+0.5*pow(q[i],2);
            }
        if (i==1){
            V+=0.5*pow(q[i],2);
            }
        }
    }
    else if (DofF >=3){
        for (int i=0; i<DofF; i++){
            if (i==0){
                V+=0.5*pow(q[i]-q[i+1],2)+0.5*pow(q[i],2);
                }
            else if (i==DofF-1){
                V+=0.5*pow(q[i],2);
            }
            else{
                V+=0.5*pow(q[i]-q[i+1],2);
            }
        }
    }
    return V;
}

double Calc_Potential_hcq(vector<double> q, double alpha, double beta){
    double V;
    int DofF=q.size();
     if (DofF==1){ 
        for (int i=0; i<DofF; i++){
            V+=pow(q[i],2)+(double)(2/3)*alpha*pow(q[i],3)+0.5*beta*pow(q[i],4);
            }        
    }
    else if (DofF==2){
        for (int i=0; i<DofF; i++){
            if (i==0){
                V+=0.5*(pow(q[i]-q[i+1],2)+pow(q[i],2))+(alpha/3)*(pow(q[i]-q[i+1],3)+pow(q[i],3))+(beta/4)*(pow(q[i]-q[i+1],4)+pow(q[i],4));
            }
            if (i==1){
                V+=0.5*pow(q[i],2)+(alpha/3)*pow(q[i],3)+(beta/4)*pow(q[i],4);
            }
        }   
    }
    else if (DofF >=3){
        for (int i=0; i<DofF; i++){
            if (i==0){
                V+=0.5*pow(q[i]-q[i+1],2)+0.5*pow(q[i],2)+(alpha/3)*pow(q[i]-q[i+1],3)+(alpha/3)*pow(q[i],3)+(beta/4)*pow(q[i]-q[i+1],4)+(beta/3)*pow(q[i],4);
                }
            else if (i==DofF-1){
                V+=0.5*pow(q[i],2)+(alpha/3)*pow(q[i],3)+(beta/4)*pow(q[i],4);
            }
            else{
                V+=0.5*pow(q[i]-q[i+1],2)+(alpha/3)*pow(q[i]-q[i+1],3)+(beta/4)*pow(q[i]-q[i+1],4);
            }
        }
    }
    return V;
}