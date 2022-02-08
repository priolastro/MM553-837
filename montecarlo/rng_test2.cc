/***************************************************************************
 * rng_test.cc
 * Use the C++11 'random' library to generate random numbers. Note that the 
 * compiler flag '-std=c++11' may be required. 
 * *************************************************************************/

#include<iostream>
#include<iomanip>
#include<random>
#include<vector>

using namespace std;

int main(int argc, char** argv) {

	int nnum = 100000;
	int nposs = 4;
  unsigned seed = 3736495;

	mt19937 gen(seed);

	//This distribution gives the integers 1,...,nposs
	uniform_int_distribution<int> dist2(1,nposs);

	vector<int> counts(nposs,0);

	cout <<endl<<"uniformly distributed integers:" << endl;
	for (int n = 0 ; n < nnum ; n++) 
	counts[dist2(gen)-1]++; 

	double chisq=0.0;
	for (int i=0; i<counts.size(); ++i) { 
		cout <<"counts["<<i+1<<"] = "<<counts[i]<<endl;
		chisq += pow((double)(counts[i])-(double)(nnum)/(double)(nposs),2)/
			((double)(nnum)/(double)(nposs));
	}

	cout << "chisq = " << chisq << endl;
	
	return 0;

	}

			

