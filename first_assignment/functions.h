/*
 * Functions
 */
double calc_Potential(int npart, vector<double>& qn){
    double Potential=0;
    for (int n=0; n<npart-1; n++) {
        Potential+=(pow(qn[n+1]-qn[n],2))/2+(pow(qn[n+1]-qn[n],3))/3+(pow(qn[n+1]-qn[n],4))/4;
    }
    return Potential;
}

double calc_Kinetic(int npart, vector<double>& pn){
    double Kinetic=0;
    for (int n=0; n<npart-1; n++) {
        Kinetic+=(pow(pn[n],2))/2;
    }
    return Kinetic;
}

double calc_Average_momentum(int npart, vector<double>& pn){
    double ave_P=0;
    for (int n=0; n<npart-1; n++) {
        ave_P+=pn[n];
    }
    return ave_P/npart;
}