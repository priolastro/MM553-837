/****************************************************************************
 * This program uses a uniform variate to calculate a slightly shifted sine 
 * integral
 * **************************************************************************/

#include<iostream>
#include<random>

using namespace std;

static const double PI = 3.14159265359;
static const double PIOVER2 = 3.14159265359/2.0;
static const double MU = 0.001;

double func ( const double& x) {

	return sin(x-MU);
}

int main(int argc, char** argv) {

	clock_t t;

	int nnum = 1e5; 
	unsigned seed = 458572629;

	mt19937 gen(seed);
  uniform_real_distribution<double> dist(-1.0*PIOVER2,PIOVER2);

	t = clock(); 
	double res=0.0;
	double ressq=0.0;
	double temp;
	for (int n = 0 ; n < nnum ; n++) {
		 temp = func(dist(gen));
	   res += temp;	
		 ressq += temp*temp; 
	}

	t = clock() - t;
	cout << "time = " << ((double)t)/CLOCKS_PER_SEC <<"sec"<< endl;


	double mean =  res/(double)(nnum);
	double var = ressq/(double)(nnum) - mean*mean;
	cout <<"mean = " << mean << endl;
	cout <<"error = " << sqrt(var/(double)(nnum)) << endl;
  cout <<"exact = " << (cos(-1.0*PIOVER2 - MU) - cos(PIOVER2-MU))/PI << endl;
	return 0;

}
