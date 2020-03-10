/*************************
 * Fermi Pasta Ulam Tsingu problem
 * ***********************/

#include<iostream>
#include<sstream>
#include<vector>
#include<cmath>
#include<fstream>
#include<random>
#include<chrono>
#include<math.h>

#include "integrators.h"
#include "systems.h"

#define _USE_MATH_DEFINES
using namespace std;
using namespace std::chrono;

int main(int argc, char** argv) {
    if (argc != 5) {
        cerr << "usage: " << argv[0] << " <t> <niter> <nmeas> <npart> " << endl;
        return 1;
    }

    double tau;
    stringstream(argv[1]) >> tau;
    double niter;
    stringstream(argv[2]) >> niter;
    double nmeas;
    stringstream(argv[3]) >> nmeas;
    double npart;
    stringstream(argv[4]) >> npart;

    double eps = tau / double(niter);

    vector<double> qn(npart);
    vector<double> pn(npart);

    pn[0] = 0, qn[0] = 0;
    pn[npart - 1] = 0, qn[npart - 1] = 0;

    for (int n = 1; n < npart - 1; n++) {
        pn[n] = sin((2*M_PI * (n+0.2) / (double) npart));
    }

    SpringSystem ss(qn);
    LeapfrogIntegrator<SpringSystem> integrator(ss, eps);
    integrator.setInitialConditions(qn,pn);
    for (int t = 0; t < niter; t++) {
        double Potential = calc_Potential(npart, qn);
        double Kinetic = calc_Kinetic(npart, pn);
        double p_tot = calc_Average_momentum(npart, pn);
        cout << Potential << " " << Kinetic << " " << p_tot / npart << endl;
        integrator(qn, pn);
    }
return 0;
}