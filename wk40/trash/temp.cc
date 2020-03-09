#include<vector>
#include<iostream>

using namespace std;

int main(){
vector<double> qn(6);

for (int n=0; n<qn.size(); n++){
	qn[n]=10;
};

for (int i=0; i<(qn.size()/2);i++){
	for (int j=0;j<i;j++){
		cout << i << j << endl;
		//cout << 2*i << " " << 2*j <<  " " << 2*i+1 << " " <<  2*j+1 << " " << endl; 
		}
	}
return 1;
}
