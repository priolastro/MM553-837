/****************************************************************************
 * gibbs1.cc
 * **************************************************************************/

#include<iostream>
#include<random>
#include<time.h>
#include<sstream>

using namespace std;

int main(int argc, char** argv) {

	if (argc != 2) {
		cerr << "usage: " << argv[0] <<" <nstep> " << endl;
		exit(1);
	}


	int ntherm = 1000; // steps of thermalization
	int nstep; 
	stringstream(argv[1]) >> nstep; //The number of steps for measurment
	double x0=0, y0=0;        //The starting point of the first chain 
	double a=1e2, b=1e-2;     // random constants

	//--------------------------------------------------------------------------

	mt19937 gen(time(NULL));
	  
	double x=x0,y=y0;  //fix starting point of the chain

	for (int t=0;t<ntherm;t++) {
	 
		double sig=sqrt(1.0/(a*(y*y + b)));  // define the sigma
		normal_distribution<double> dist1(0,sig);  // normal distribution to sample from with sigma depending on x2
	
		x=dist1(gen);  // draw x1

		sig=sqrt(1.0/(a*(x*x + b))); //update sigma
		normal_distribution<double> dist2(0,sig); //normal distribution with sigma depending on x1

		y=dist2(gen); //draw x2

	}

	for (int t=0;t<nstep;t++) {
	
		double sig=sqrt(1.0/(a*(y*y + b)));
		normal_distribution<double> dist1(0,sig);
	
		x=dist1(gen);

		sig=sqrt(1.0/(a*(x*x + b)));
		normal_distribution<double> dist2(0,sig);

		y=dist2(gen);

	cout << x << endl;  
	cout << y << endl;  
	}


	return 0;

}