/****************************************************************************
 * Particles in a box
 * **************************************************************************/

#include<iostream>
#include<sstream>
#include<cmath>
#include<fstream>
#include<random>
#include<chrono>
#include<math.h>


#include "integrators.h"
#include "systems.h"
#include "forces.h"

using namespace std;
using namespace std::chrono;

double somma(vector<double>& vec){
    double sum=0;
    for (int i=0; i<vec.size();i++){
        sum+=vec[i];
    }
    return sum;
}



int main(int argc, char** argv) {
    auto start=high_resolution_clock::now();
	if (argc !=4){
		cerr << "usage: " << argv[0] << " <t> <niter> <nparticles> \n";
	}


    double tau; 
	stringstream(argv[1]) >> tau; 
	int niter; 
	stringstream(argv[2]) >> niter; 
    int particles;
    stringstream(argv[3]) >> particles;

    ofstream EnergiesOut("energies.out");
    EnergiesOut.precision(17);

    double eps=tau/double(niter);
    double psize=0.01;
    double Lmax = 2;

    unsigned seed = 683129629;
    mt19937 gen(seed);
    uniform_real_distribution<double> dist(-Lmax,Lmax);

    vector<double> qn(2*particles), pn(2*particles);

    for (int n=0; n<qn.size(); n++) {
        qn[n]=dist(gen);
        pn[n]=dist(gen)/2;
    }

    SquareBox sb(Lmax, psize, 2);
    NoForce is(1);
    CentralForce<NoForce> cf(is,particles);
    Leapfrog <CentralForce<NoForce>, SquareBox> LE(cf, sb, eps);

    LE.setInitialConditions(qn, pn);

    double Eipot=cf.calcPot(qn);
    double Eikin=cf.calcKin(pn);
    double Ti=(pow(Eikin,2))/particles;

    cerr << "Ei_pot=" << Eipot << endl;
    cerr << "Ei_kin=" << Eikin << endl;
    cerr << "Ei_Tot=" << Eikin+Eipot << endl;
    cerr << "Temp=" << Ti << endl;
    
    
    for (int t=0; t<niter;t++){
        for (int i=0; i<qn.size();++i){
            cout << qn[i] << " " << pn[i] << endl; 
        }
        EnergiesOut << cf.calcPot(qn) << "      " << cf.calcKin(pn) << "    " << cf.calcKin(pn)+cf.calcPot(qn) << endl;
        LE(qn,pn);        
    }


    double Efpot=cf.calcPot(qn);
    double Efkin=cf.calcKin(pn); 

    cerr << "Efpot=" << Efpot << endl;
    cerr << "Efkin=" << Efkin << endl;
    cerr << "Ef_Tot=" << Efkin+Efpot << endl;


    auto stop=high_resolution_clock::now();
    duration<float> duration=stop-start;
    cerr << "##The algorithm took "  << duration.count() << "ns\n";
    return 0;
}