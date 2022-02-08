/****************************************************************************
 * This program uses a uniform variate to calculate a slightly shifted sine 
 * integral
 * **************************************************************************/

#include<iostream>
#include<random>

using namespace std;

static const double PIOVER2 = 3.14159265359/2.0;
static const double MU = 0.001;

double func ( const double& x) {

	return sin(x-MU);
}

int main(int argc, char** argv) {

	clock_t t;

	int nnum = 5e8; 
	unsigned seed = 458572629;

	mt19937 gen(seed);
  uniform_real_distribution<double> dist1(0,PIOVER2);
  uniform_real_distribution<double> dist2(-PIOVER2,0);

	t = clock(); 
	double res1=0.0,res2=0.0;
	double res1sq=0.0,res2sq=0.0;
	double temp;
	for (int n = 0 ; n < nnum ; n++) {

		 temp = func(dist1(gen));
	   res1 += temp;	
		 res1sq += temp*temp; 
		 
		 temp = func(dist2(gen));
	   res2 += temp;	
		 res2sq += temp*temp; 
	}

	t = clock() - t;
	cout << "time = " << ((double)t)/CLOCKS_PER_SEC <<"sec"<< endl;


	double mean1 =  res1 /(double)(nnum);
	double mean2 =  res2 /(double)(nnum);
	double mean = 0.5*(mean1 + mean2);
	
	double var1 = res1sq/(double)(nnum) - mean1*mean1;
	double var2 = res2sq/(double)(nnum) - mean2*mean2;
  double var = 0.5*0.5*(var1 + var2);	
	cout <<"mean = " << mean << endl;
	cout <<"error = " << sqrt(var/(double)(nnum)) << endl;
  cout <<"exact = " << (cos(-1.0*PIOVER2 - MU) - cos(PIOVER2-MU))/(2.0*PIOVER2) << endl;
	return 0;

}
