/*************************
 * Fermi–Pasta–Ulam–Tsingou problem 
 * ***********************/

#include<iostream>
#include<sstream>
#include<vector>
#include<cmath>
#include<fstream>
#include<random>
#include<chrono>
#include<math.h>
#include "omp.h"

#define _USE_MATH_DEFINES
using namespace std;
using namespace std::chrono;

#include "Forces.h"
#ifndef __Forces__
#define __Forces__
#include "Integrators.h"
#ifndef __Integrators__
#define __Integrators__
#include "functions.h"
#ifndef __functions__
#define __functions__


int main(int argc, char** argv) {
    //start here
    auto start=high_resolution_clock::now();


    //initialize 
    double tau;
    stringstream(argv[1]) >> tau;
    int niter;
    stringstream(argv[2]) >> niter;
    int npart;
    stringstream(argv[3]) >> npart;
    double eps=tau/double(niter);
    double alpha=0;
    double beta=0;
    
    
    //set name output
    ofstream dati("dati.dat");
    ofstream cord("cord.dat");

    

    vector<double> qn(npart),pn(npart);
    for (int n = 0; n < npart; n++) {
        pn[n] = sin((M_PI*(n+0.3))/npart);
        qn[n] = 0;
    };

    SpringsSystem_hcq ss(1,1, alpha, beta);
    Leapfrog<SpringsSystem_hcq> integrator(ss, eps);

    integrator.setInitialCondition(qn,pn);

    for (int t=0; t<niter; t++){
        dati << Calc_Kinetic(pn) << " " << Calc_Potential_hcq(qn, alpha, beta) << " " << Calc_AverageSpeed(pn) << " " << Calc_sqSpeed(pn) <<  endl;
        for (int i = 0; i < qn.size(); i++){
            cord << qn[i] << '\n';
        }
        integrator(qn,pn);
    };
auto stop=high_resolution_clock::now();
auto duration = duration_cast<nanoseconds>(stop-start);
cout << "\n###The algorithm took: " << duration.count() << "\n";
return 1;
}
#endif
#endif
#endif