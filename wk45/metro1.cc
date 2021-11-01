/****************************************************************************
 * metro1.cc
 * **************************************************************************/

#include<iostream>
#include<random>
#include<time.h>
#include<sstream>

using namespace std;

int main(int argc, char** argv) {

	if (argc != 4) {
		cerr << "usage: " << argv[0] <<" <nstep> <nmeas> <delta>" << endl;
		exit(1);
	}

	int ntherm = 1000; //Number of thermalization steps
	int nstep; stringstream(argv[1]) >> nstep;  //The number of steps 
	int nmeas; stringstream(argv[2]) >> nmeas;  //Freq. of measurement 
	
	double x0=0,y0=0;        //The starting point of the first chain 
	double a=1e2, b=1e-2;	
	double delta; stringstream(argv[3]) >> delta;   // width of the interval we are going to use in the proposal step 
	//--------------------------------------------------------------------------

	mt19937 gen(time(NULL));
	uniform_real_distribution<double> adist(0,1);  // distribution to sample a new value of x1'
  	
	double x=x0,y=y0;
	double acc=0.0;

	for (int t=0;t<ntherm;t++) {
	
		uniform_real_distribution<double> distx(x-delta/2,x+delta/2);
	
		double xp = distx(gen);

		double p = exp(-a*(y*y+b)*0.5*(xp*xp-x*x));

		if (p > 1) //accetta 
			x=xp;
		else {
			if (adist(gen) < p) 
				x=xp; 
		}

		if (x==xp)
			acc++;

		uniform_real_distribution<double> disty(y-delta/2,y+delta/2);
	
		double yp = disty(gen);

		p = exp(-a*(x*x+b)*0.5*(yp*yp-y*y));

		if (p > 1) 
			y=yp;  //accept the update
		else {
			if (adist(gen) < p) 
				y=yp; 
		}

		if (y==yp)  //proportion of proposal that are or not accepted 
			acc++;
	}

//  cout << (nstep/nmeas) << " 2 0 0 1" << endl;

	for (int t=0;t<nstep;t++) {
	
		uniform_real_distribution<double> distx(x-delta/2,x+delta/2);
	
		double xp = distx(gen);

		double p = exp(-a*(y*y+b)*0.5*(xp*xp-x*x));

		if (p > 1) 
			x=xp;
		else {
			if (adist(gen) < p) 
				x=xp; 
		}

		if (x==xp)
			acc++;

		uniform_real_distribution<double> disty(y-delta/2,y+delta/2);
	
		double yp = disty(gen);

		p = exp(-a*(x*x+b)*0.5*(yp*yp-y*y));

		if (p > 1) 
			y=yp;
		else {
			if (adist(gen) < p) 
				y=yp; 
		}

		if (y==yp)
			acc++;
  
		if ((t % nmeas)==0) {
			cout << x << endl;  
			cout << y << endl;  
		}
	}

	cout << "acc = "<<acc/(2*(nstep+ntherm))<<endl;

	return 0;

}