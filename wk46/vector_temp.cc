#include <vector>
#include <iostream>


using namespace std;


int main(){
    vector<int> v = {0,1,2};
    cout << v.size() << endl;
    for (int i=0; i < v.size(); i++)
        cout << v[i] << endl;
        
}