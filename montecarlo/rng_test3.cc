#include<iostream> 
#include<random> 
#include<ctime>

using namespace std;

int main() {  

  mt19937 gen(time(0)); // use time as seed is bad for debugging
  exponential_distribution<double> cdist(1);
//   cauchy_distribution<double> cdist(0,1.0); //mean and width
 
	int niter = 1000 ; 

	double sum=0; 
	
	for (int j=0; j<niter; j++) {
		sum+=cdist(gen);
		cout << j <<"      "<<sum/((double)(j+1))<<endl;  //sample mean is printed
	}

	return 0;
} 
      