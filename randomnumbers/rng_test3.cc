#include<iostream> 
#include<random> 

using namespace std;

int main() {

	mt19937 gen(4737361);
   exponential_distribution<double> cdist(1.0);
  //cauchy_distribution<double> cdist(0,1.0);

	int niter = 100000; 

	double sum=0; 
	//cout << niter << " 1 0 0 1" << endl;
	
	for (int j=0; j<niter; j++) {
		sum+=cdist(gen);
		//cout << "0      "<<sum/((double)(j+1))<<endl;
		cout << j << "  " << sum/((double)(j+1))<<endl;
	}	

	return 0;
}
