/****************************************************************************
 * rw1.cc
 *
 * A simple program to implement the 1-D random walk. Thermalization is
 * studied by performing many simulations.
 * **************************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <string>
#include <sstream>


using namespace std;

int main(int argc, char **argv)
{
	int N_thermalization_step = 0;
	int nproduction_step = 2;	//The number of steps in a single chain
	int nsim = 1E2; //The number of independent chains (total number of simulations)
	int x0;			//The starting point (in the chain)
	int nmax = 5;	//The maximum allowed distance from the origin.

	int nstep = N_thermalization_step + nproduction_step;
	int nstars = 100;

	if (argc != 3)
	{	cerr << "Chose: normal walls[1], periodic walls[2], bouncing walls[3]" << endl;
		cerr << "Give value of q (r value is automatically set as 1-q) and where you want to start x0, i.e. " << endl;
		cerr << argv[0] << " <walls> <q> <x0>" << endl;
	}
	double q;
	double r;
	int type;
	stringstream(argv[1]) >> type;
	stringstream(argv[2]) >> q;
	stringstream(argv[3]) >> x0;
	r = 1 - q;
	cerr << "type is: " << type << endl;
	cerr << "r value is: " << r << endl;

	//--------------------------------------------------------------------------

	mt19937 gen(time(NULL));
	discrete_distribution<int> dist{r, q};
	ofstream fout("result_" + to_string(nproduction_step) + ".txt");
	
	int step, x = x0;
	
	vector<int> p(2 * nmax + 1);

	for (int i = 0; i < nsim; i++)
	{
		x = x0;
		for (int t = 0; t < nstep; t++)
		{
			step = 2 * (dist(gen)) - 1;

			if (type == 3) //bouncing walls
			{
				if (x + step == nmax + 1)
				{
					step = -2;
				}
				else if (x + step == -nmax - 1)
				{
					step = 2;
				};
			}
			if (type == 2) //periodic walls;
			{
				if (x + step == nmax + 1)
				{
					step = (-2 * nmax );
				}
				else if (x + step == -nmax - 1)
				{
					step = 2 * nmax;
				};
			}
			if (type == 1) // normal walls;
			{
				if (abs(x+step) == nmax+1)
				{
					step=0;
				}
			}
			fout << x << endl;
			x += step;
		}
		p[x + nmax]++;
	}
	cout << "distribution: " << endl;
	for (int i = 0; i < p.size(); ++i)
	{
		cout << setw(2) << i - nmax << ": " << string(p[i] * nstars / nsim, ':') << endl;
	}
	return 0;
}