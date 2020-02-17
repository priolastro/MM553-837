//
// Created by salvatore prioli on 22/01/2020.
// Bifurcation diagram of the logistic map
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cmath>
using namespace std;

int main(){
    const double rmin=2.5;
    const double rmax=4.0;
    const double NTRANS=500;
    const double NSTEPS=100;
    const double RSTEPS=2000;
    int i;
    double r, dr, x0, x1;

    dr=(rmax-rmin)/RSTEPS;
    ofstream myfile("bif.dat");
    myfile.precision(17);

    r=rmin;
    while(r<=rmax){
        x0=0.5;
        for(i=1; i<=NTRANS; i++){
            x1=r*x0*(1.0-x0);
            x0=x1;
        }
        for(i=1;i<=NSTEPS;i++){
            x1=r*x0*(1.0-x0);
            myfile << r << " " << x1 << '\n';
            x0=x1;
        }
        r+=dr;
    }
    myfile.close();
};

