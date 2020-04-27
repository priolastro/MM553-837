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
#include "Functions.h"
#ifndef __functions__
#define __functions__


int main(int argc, char** argv) {
    //start here
    auto start=high_resolution_clock::now();
    if (argc !=4){
                cerr << "usage: " << argv[0] << " <t> <eps> <nparticles> \n ### t is the total time of simulation \n ### eps is the time step \n ### nparticles is the number of particles mooving" << endl;
        }
 

    //initialize
    double percent; // to see progress 
    double tau;
    stringstream(argv[1]) >> tau;
    double eps;
    stringstream(argv[2]) >> eps;
    int npart;
    stringstream(argv[3]) >> npart;
    int niter=tau/double(eps);
    double alpha=0.25;
    double beta=0.025;
    //to have only linear term set alpha=0 and beta=0
    
    
    //set name output files
    ofstream dati("dati.dat");
    ofstream cord("cord.dat");

    

    vector<double> qn(npart),pn(npart);
    for (int n = 0; n < npart; n++) {
        pn[n] = sin((2*M_PI*(n+0.3))/npart);
        qn[n] = 0;
    };

    SpringsSystem ss(1,1, alpha, beta);
    Leapfrog<SpringsSystem> integrator(ss, eps);

    integrator.setInitialCondition(qn,pn);

    for (int t=0; t<niter; t++){
        dati << Calc_Kinetic(pn) << " " << Calc_Potential(qn, alpha, beta) << " " << Calc_AverageSpeed(pn) << " " << Calc_sqSpeed(pn) <<  endl;
        for (int i = 0; i < qn.size(); i++){
            cord << qn[i] << '\n';
        }
        /// Progress bar section
	    percent = (t*100)/niter;
	    cout << t << " di " << niter << " iterazioni ## completamento: " << percent << "%\r";
        /// Progress bar section

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
