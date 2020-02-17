//
// Created by salvatore prioli on 17/01/2020.
// Calculating the logistic map
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cmath>
using namespace std;

int main(){
    int NSTEPS, i;
    double r, x0, x1;
    string buf, FILE_NAME;

    cout << "# Enter NSTEPS, r, x0: \n";
    cin >> NSTEPS >> r >> x0; getline(cin, buf);
    cout << "# NSTEPS = " << NSTEPS << endl;
    cout << " r       = " << r      << endl;
    cout << " x0      = " << x0     << endl;
    cout << "# Enter file name: \n";
    cin >> FILE_NAME; getline(cin, buf);

    ofstream myfile(FILE_NAME);
    myfile.precision(17);

    myfile << 0 << " " << x0 << endl ;
    for(i=1; i<NSTEPS;i++){
        x1=r*x0*(1.0-x0);
        myfile << i << " "<< x1 << "\n";
        x0=x1;
    }
    myfile.close();
}
