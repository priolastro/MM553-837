//
// Created by salvatore prioli on 05/02/2020.
// Newron Raphson of function of one variable
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cmath>
using namespace std;

int main(){
    const double rho=15.0;
    const double eps=1.0e-6;
    const int NMAX=10;
    double x0,x1,err,g,gp;
    int i;
    string buf;

    cout << "enter x0:\n";
    cin >> x0; getline(cin,buf);
    err=1.0;
    cout << "iter   x   error \n";
    cout << "−−−−−−−−−−−−−----\n";
    cout << 0 << "      " << x0 << "        "<< err << '\n';
    cout.precision(17);
    for(i=1;i<=NMAX;i++){
        g=x0*tan(x0)-sqrt(rho*rho-x0*x0);
        gp=x0/sqrt(rho*rho-x0*x0)+x0/(cos(x0)*cos(x0))+tan(x0);
        x1=x0-g/gp;
        err=abs(x1-x0);
        cout << i << " " << x1 << " "<< err <<'\n';
        if (err < eps ) break;
        x0=x1;
    }
}