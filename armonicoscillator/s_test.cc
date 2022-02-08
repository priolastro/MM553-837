#include<iostream>
#include<vector>
#include<math.h>

using namespace std;

const double a = 1.57079632679;
const int npoint = 1e4;

double simpsons_rule(const vector<double>& f) { 
		double epsilon = a/(double)(f.size()-1);
		double ret=0;
		for (int i = 0 ; i<f.size(); i++) { 
			if ((i==0)||(i==(f.size()-1)))
				ret+=f[i];
			else if ((i%2)==0)
				ret+=2.0*f[i];
			else 
				ret+=4.0*f[i];
		}

		ret *= epsilon/3.0;

		return ret;
	}

int main () { 

	vector<double> v;
	double x=0;
	const double epsilon=a/(double)(npoint-1); 
	cout <<"epsilon = "<<epsilon<<endl;
	for (int n=0; n<npoint; n++) { 
		v.push_back(sin(x));
		cout << "x = "<<x<<", f(x) = "<<sin(x)<<endl;	
		x += epsilon;
	}

	cout << "int = " << simpsons_rule(v) << endl;

	return 0;
}
