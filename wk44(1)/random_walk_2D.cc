/************************************************************************
 * Random walk in 2D 
 * 
 * **********************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>

using namespace std;

int main(int argc, char **argv)
{
    int nsimulation = 1000;
    int nsteps = 1000;
    int x=0,y=0;

    mt19937 gen(29293);
    discrete_distribution<int> dist{0,0};
    for (int i=0; i<10; i++){
        cout << dist(gen) << endl;
    }
}
