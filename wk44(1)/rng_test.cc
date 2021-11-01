/***************************************************************************
 * rng_test.cc
 * Use the C++11 'random' library to generate random numbers. Note that the 
 * compiler flag '-std=c++11' may be required. 
 * *************************************************************************/

#include<iostream>
#include<iomanip>
#include<random>

using namespace std;

int main(int argc, char** argv) {

	int nnum = 10;
  unsigned seed = 57385349;

	mt19937 gen(seed);

	//This distribution gives doubles uniformly distributed in [0,1] 	
	uniform_real_distribution<double> dist1(0,1);

	//This distribution gives the integers 1,...,6
	uniform_int_distribution<int> dist2(1,6);


	cout <<"unformly distributed doubles:" << endl;
	for (int n = 0 ; n < nnum ; n++) 
	cout << dist1(gen)<<endl; 
	
	cout <<endl<<"uniformly distributed integers:" << endl;
	for (int n = 0 ; n < nnum ; n++) 
	cout << dist2(gen)<<endl; 

		return 0;

	}

			

