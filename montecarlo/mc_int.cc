/***************************************************************************
 * mc_test.cc
 * Use the C++11 'random' library to generate random numbers. Note that the 
 * compiler flag '-std=c++11' may be required. 
 * *************************************************************************/

#include<iostream>
#include<iomanip>
#include<random>
#include<fstream>
#include<vector>

using namespace std;

int main(int argc, char** argv) {
    int nnum = 1e6; // how many random samples 
    unsigned seed = 4857573;

	mt19937 gen(seed); 

	uniform_real_distribution<double> dist_un(0,3);
    exponential_distribution<double> dist_exp(1); 


	double x_sum_un=0.0; 
	double dev_sq_un;
	vector<double> x_vec_un(nnum);

	for (int n = 0 ; n < nnum ; n++) { 
		double u = dist_un(gen); 
		double x = 3.0*exp(-u)/(1.0+u/9.0); //uniform
		x_vec_un[n] = x;  
		x_sum_un += x;
	}

	double mean_un = x_sum_un/nnum;

	for (int n = 0 ; n < nnum ; n++) {
		dev_sq_un+=pow(x_vec_un[n]-mean_un,2);
	}

	double std_dev_un=dev_sq_un/((double)nnum-1);
	double std_err_un=std_dev_un/pow((double)nnum,0.5);

	double x_sum_exp=0.0; 
	double dev_sq_exp;
	vector<double> x_vec_exp(nnum);

	for (int n = 0 ; n < nnum ; n++) { 
		double u = dist_exp(gen);
		while (u >= 3 ) {
			u = dist_exp(gen); 
		}
		double x = (1.0-exp(-3))/(1.0+u/9.0); //exponential
		x_vec_exp[n]=x;  
		x_sum_exp += x;
	}
	
	double mean_exp = x_sum_exp/nnum;

	for (int n = 0 ; n < nnum ; n++) {
		dev_sq_exp+=pow(x_vec_exp[n]-mean_exp,2);
	}

	double std_dev_exp=dev_sq_exp/((double)nnum-1);
	double std_err_exp=std_dev_exp/pow((double)nnum,0.5);

	cout << "I = " << mean_un << " +/- "<< std_err_un << endl; 
	cout << "I = " << mean_exp << " +/- "<< std_err_exp << endl; 

	return 0;

	}

			
 